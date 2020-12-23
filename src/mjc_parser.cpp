#include <functional>
#include <mjc_parser.h>

namespace mjc {

Parser::Parser(std::unique_ptr<LexerProtocol> lex, StringTable *stringtable)
    : d_lexer{std::move(lex)}, d_stringtable_p{stringtable} {}

std::unique_ptr<mjast::Program> Parser::parse() {
  advance();
  return goal();
}

bool Parser::success() const { return d_success; }

void Parser::advance() noexcept { d_tok = d_lexer->nextToken(); }

void Parser::eat(Token::Kind expected) noexcept {
  if (d_tok.kind() == expected) {
    advance();
  } else {
    error();
    while (d_tok.kind() != expected && d_tok.kind() != Token::Kind::e_EOF) {
      advance();
    }
  }
}

void Parser::error() noexcept {
  auto pos = d_lexer->currentPosition();
  std::cerr << fmt::format("Syntax error at or near token {} at {}:{}.\n",
                           d_tok, pos.fileName, pos.lineNumber);
  d_success = false;
}

std::unique_ptr<mjast::Program> Parser::goal() {
  // goal : mainClass ( classDeclaration )* EOF

  auto mainClassNode = mainClass();
  auto classes = std::make_unique<mjast::ClassDeclList>();
  while (d_tok.kind() == Token::Kind::e_CLASS) {
    classes->list.push_back(classDeclaration());
  }
  if (d_tok.kind() != Token::Kind::e_EOF) {
    error();
  }
  return std::make_unique<mjast::Program>(
      mjast::Program{std::move(mainClassNode), std::move(classes)});
}

std::unique_ptr<mjast::MainClass> Parser::mainClass() {
  // mainClass : CLASS identifier LBRACE PUBLIC STATIC VOID MAIN LPAREN STRING
  //   LBRACKET RBRACKET identifier RPAREN LBRACE statement RBRACE RBRACE

  eat(Token::Kind::e_CLASS);
  auto className = identifier();
  eat(Token::Kind::e_LBRACE);
  eat(Token::Kind::e_PUBLIC);
  eat(Token::Kind::e_STATIC);
  eat(Token::Kind::e_VOID);
  eat(Token::Kind::e_MAIN);
  eat(Token::Kind::e_LPAREN);
  eat(Token::Kind::e_STRING);
  eat(Token::Kind::e_LBRACKET);
  eat(Token::Kind::e_RBRACKET);
  auto paramName = identifier();
  eat(Token::Kind::e_RPAREN);
  eat(Token::Kind::e_LBRACE);
  auto stmt = statement();
  eat(Token::Kind::e_RBRACE);
  eat(Token::Kind::e_RBRACE);
  return std::make_unique<mjast::MainClass>(mjast::MainClass{
      std::move(className), std::move(paramName), std::move(stmt)});
}

std::unique_ptr<mjast::ClassDecl> Parser::classDeclaration() {
  // classDeclaration : : CLASS identifier ( EXTENDS identifier )? LBRACE (
  //   varDeclaration )* ( methodDeclaration )* RBRACE

  static constexpr auto varDeclarationFirstSet = std::array{
      Token::Kind::e_INT, Token::Kind::e_BOOLEAN, Token::Kind::e_IDENTIFIER};

  eat(Token::Kind::e_CLASS);
  auto className = identifier();
  std::unique_ptr<mjast::Identifier> parentClassName;
  if (d_tok.kind() == Token::Kind::e_EXTENDS) {
    eat(Token::Kind::e_EXTENDS);
    parentClassName = identifier();
  }
  eat(Token::Kind::e_LBRACE);
  auto varList = std::make_unique<mjast::VarDeclList>();
  while (std::any_of(varDeclarationFirstSet.begin(),
                     varDeclarationFirstSet.end(),
                     [&](Token::Kind k) { return k == d_tok.kind(); })) {
    varList->varDecls.push_back(varDeclaration());
  }
  auto methodList = std::make_unique<mjast::MethodDeclList>();
  while (d_tok.kind() == Token::Kind::e_PUBLIC) {
    methodList->methods.push_back(methodDeclaration());
  }
  eat(Token::Kind::e_RBRACE);
  if (parentClassName) {
    return std::make_unique<mjast::ClassDecl>(mjast::ClassDeclExtends{
        std::move(className), std::move(parentClassName), std::move(varList),
        std::move(methodList)});
  } else {
    return std::make_unique<mjast::ClassDecl>(mjast::ClassDeclSimple{
        std::move(className), std::move(varList), std::move(methodList)});
  }
}

std::unique_ptr<mjast::VarDecl> Parser::varDeclaration() {
  // varDeclaration : type identifier SEMI

  auto typ = type();
  auto name = identifier();
  eat(Token::Kind::e_SEMI);
  return std::make_unique<mjast::VarDecl>(
      mjast::VarDecl{std::move(typ), std::move(name)});
}

std::unique_ptr<mjast::MethodDecl> Parser::methodDeclaration() {
  // methodDeclaration : PUBLIC type identifier LPAREN ( type identifier ( COMMA
  //   type identifier)* )? RPAREN LBRACE ( varDeclaration )* ( statement )*
  //   RETURN expression SEMI RBRACE

  static constexpr auto typeFirstSet = std::array{
      Token::Kind::e_INT, Token::Kind::e_BOOLEAN, Token::Kind::e_IDENTIFIER};

  static constexpr auto statementFirstSet =
      std::array{Token::Kind::e_LBRACE, Token::Kind::e_IF, Token::Kind::e_WHILE,
                 Token::Kind::e_PRINTLN, Token::Kind::e_IDENTIFIER};

  eat(Token::Kind::e_PUBLIC);
  auto returnTyp = type();
  auto name = identifier();
  eat(Token::Kind::e_LPAREN);
  auto formalList = std::make_unique<mjast::FormalList>();
  if (std::any_of(typeFirstSet.begin(), typeFirstSet.end(),
                  [&](Token::Kind k) { return k == d_tok.kind(); })) {
    auto formalTyp = type();
    auto formalName = identifier();
    formalList->formals.push_back(std::make_unique<mjast::Formal>(
        mjast::Formal{std::move(formalTyp), std::move(formalName)}));

    while (d_tok.kind() == Token::Kind::e_COMMA) {
      eat(Token::Kind::e_COMMA);
      formalTyp = type();
      formalName = identifier();
      formalList->formals.push_back(std::make_unique<mjast::Formal>(
          mjast::Formal{std::move(formalTyp), std::move(formalName)}));
    }
  }
  eat(Token::Kind::e_RPAREN);
  eat(Token::Kind::e_LBRACE);
  auto varDeclList = std::make_unique<mjast::VarDeclList>();
  auto statementList = std::make_unique<mjast::StatementList>();

  while (std::any_of(typeFirstSet.begin(), typeFirstSet.end(),
                     [&](Token::Kind k) { return k == d_tok.kind(); })) {

    if (d_tok.kind() == Token::Kind::e_IDENTIFIER) {
      auto id = d_tok.matchValue(
          [](StringIndex const &id) -> StringIndex { return id; },
          [&](auto &&) -> StringIndex { return d_stringtable_p->insert(""); });
      eat(Token::Kind::e_IDENTIFIER);

      // Disambiguate beetween another var and the first statement
      if (d_tok.kind() == Token::Kind::e_EQUAL) {
        auto name = std::make_unique<mjast::Identifier>(
            mjast::Identifier{std::move(id)});

        // First statement, assign
        eat(Token::Kind::e_EQUAL);
        auto expr = expression();
        eat(Token::Kind::e_SEMI);
        statementList->stmts.push_back(std::make_unique<mjast::Statement>(
            mjast::Assign{std::move(name), std::move(expr)}));
        break;

      } else if (d_tok.kind() == Token::Kind::e_LBRACKET) {
        auto name = std::make_unique<mjast::Identifier>(
            mjast::Identifier{std::move(id)});

        // First statement, array assign
        eat(Token::Kind::e_LBRACKET);
        auto indexExpr = expression();
        eat(Token::Kind::e_RBRACKET);
        eat(Token::Kind::e_EQUAL);
        auto valueExpr = expression();
        eat(Token::Kind::e_SEMI);
        statementList->stmts.push_back(
            std::make_unique<mjast::Statement>(mjast::ArrayAssign{
                std::move(name), std::move(indexExpr), std::move(valueExpr)}));
        break;
      } else {
        auto varTyp =
            std::make_unique<mjast::Type>(mjast::IdentifierType{std::move(id)});
        auto varName = identifier();
        eat(Token::Kind::e_SEMI);
        varDeclList->varDecls.push_back(std::make_unique<mjast::VarDecl>(
            mjast::VarDecl{std::move(varTyp), std::move(varName)}));
      }
    } else {
      auto varTyp = type();
      auto varName = identifier();
      eat(Token::Kind::e_SEMI);
      varDeclList->varDecls.push_back(std::make_unique<mjast::VarDecl>(
          mjast::VarDecl{std::move(varTyp), std::move(varName)}));
    }
  }

  while (std::any_of(statementFirstSet.begin(), statementFirstSet.end(),
                     [&](Token::Kind k) { return k == d_tok.kind(); })) {
    statementList->stmts.push_back(statement());
  }

  eat(Token::Kind::e_RETURN);
  auto returnValueExp = expression();
  eat(Token::Kind::e_SEMI);
  eat(Token::Kind::e_RBRACE);

  return std::make_unique<mjast::MethodDecl>(
      mjast::MethodDecl{std::move(returnTyp), std::move(name),
                        std::move(formalList), std::move(varDeclList),
                        std::move(statementList), std::move(returnValueExp)});
}

std::unique_ptr<mjast::Type> Parser::type() {
  auto first = true;
  while (true) {
    switch (d_tok.kind()) {

    case Token::Kind::e_INT: {
      // type : INT ( LBRACKET RBRACKET )?
      eat(Token::Kind::e_INT);
      if (d_tok.kind() == Token::Kind::e_LBRACKET) {
        eat(Token::Kind::e_LBRACKET);
        eat(Token::Kind::e_RBRACKET);
        return std::make_unique<mjast::Type>(mjast::IntArrayType{});
      } else {
        return std::make_unique<mjast::Type>(mjast::IntegerType{});
      }
    } break;

    case Token::Kind::e_BOOLEAN: {
      // type : BOOLEAN
      eat(Token::Kind::e_BOOLEAN);
      return std::make_unique<mjast::Type>(mjast::BooleanType{});
    } break;

    case Token::Kind::e_IDENTIFIER: {
      // type : identifier
      auto typName = mjast::IdentifierType{d_tok.matchValue(
          [&](StringIndex const &id) -> StringIndex { return id; },
          [&](auto const &) -> StringIndex {
            return d_stringtable_p->insert("");
          })};
      eat(Token::Kind::e_IDENTIFIER);
      return std::make_unique<mjast::Type>(std::move(typName));
    } break;

    case Token::Kind::e_EOF: {
      return std::make_unique<mjast::Type>();
    } break;

    default: {
      if (first) {
        first = false;
        error();
      }
      advance();
    } break;
    }
  }
}

std::unique_ptr<mjast::Statement> Parser::statement() {

  auto first = true;
  while (true) {
    switch (d_tok.kind()) {
    case Token::Kind::e_LBRACE: {
      // statement : LBRACE ( statement )* RBRACE
      eat(Token::Kind::e_LBRACE);
      auto stmtList = std::make_unique<mjast::StatementList>();
      while (d_tok.kind() != Token::Kind::e_RBRACE) {
        stmtList->stmts.push_back(statement());
      }
      eat(Token::Kind::e_RBRACE);
      return std::make_unique<mjast::Statement>(
          mjast::Block{std::move(stmtList)});
    } break;

    case Token::Kind::e_IF: {
      // statement : IF LPAREN expression RPAREN statement ELSE statement
      eat(Token::Kind::e_IF);
      eat(Token::Kind::e_LPAREN);
      auto cond = expression();
      eat(Token::Kind::e_RPAREN);
      auto truePathStmt = statement();
      eat(Token::Kind::e_ELSE);
      auto falsePathStmt = statement();
      return std::make_unique<mjast::Statement>(mjast::If{
          std::move(cond), std::move(truePathStmt), std::move(falsePathStmt)});
    } break;

    case Token::Kind::e_WHILE: {
      // statement : WHILE LPAREN expression RPAREN statement
      eat(Token::Kind::e_WHILE);
      eat(Token::Kind::e_LPAREN);
      auto cond = expression();
      eat(Token::Kind::e_RPAREN);
      auto loopStmt = statement();
      return std::make_unique<mjast::Statement>(
          mjast::While{std::move(cond), std::move(loopStmt)});
    } break;

    case Token::Kind::e_PRINTLN: {
      // statement : PRINTLN LPAREN expression RPAREN SEMI
      eat(Token::Kind::e_PRINTLN);
      eat(Token::Kind::e_LPAREN);
      auto expr = expression();
      eat(Token::Kind::e_RPAREN);
      eat(Token::Kind::e_SEMI);
      return std::make_unique<mjast::Statement>(mjast::Print{std::move(expr)});
    } break;

    case Token::Kind::e_IDENTIFIER: {
      // statement : identifier ( EQUAL expression SEMI | LBRACKET expression
      //   RBRACKET EQUAL expression SEMI )
      auto name = identifier();
      auto firstAssign = true;
      while (true) {
        switch (d_tok.kind()) {

        case Token::Kind::e_EQUAL: {
          eat(Token::Kind::e_EQUAL);
          auto valueExpr = expression();
          eat(Token::Kind::e_SEMI);
          return std::make_unique<mjast::Statement>(
              mjast::Assign{std::move(name), std::move(valueExpr)});
        } break;

        case Token::Kind::e_LBRACKET: {
          eat(Token::Kind::e_LBRACKET);
          auto indexExp = expression();
          eat(Token::Kind::e_RBRACKET);
          eat(Token::Kind::e_EQUAL);
          auto valueExpr = expression();
          eat(Token::Kind::e_SEMI);
          return std::make_unique<mjast::Statement>(mjast::ArrayAssign{
              std::move(name), std::move(indexExp), std::move(valueExpr)});
        } break;

        case Token::Kind::e_EOF: {
          return std::make_unique<mjast::Statement>();
        } break;

        default: {
          if (firstAssign) {
            firstAssign = false;
            error();
          }
          advance();
        } break;
        }
      }
    } break;

    case Token::Kind::e_EOF: {
      std::make_unique<mjast::Statement>();
    } break;

    default: {
      if (first) {
        first = false;
        error();
      }
      advance();
    } break;
    }
  }
}

std::unique_ptr<mjast::Exp> Parser::expression(int pri) {
  auto first = true;
  std::unique_ptr<mjast::Exp> leftExp;
  auto leftExpFilled = false;
  while (!leftExpFilled) {
    switch (d_tok.kind()) {

    case Token::Kind::e_INTEGER_LITERAL: {
      leftExpFilled = true;
      auto value = d_tok.matchValue([](int x) -> int { return x; },
                                    [](auto const &) -> int { return 0; });
      eat(Token::Kind::e_INTEGER_LITERAL);
      leftExp = std::make_unique<mjast::Exp>(mjast::IntegerLiteral{value});
    } break;

    case Token::Kind::e_TRUE: {
      leftExpFilled = true;
      eat(Token::Kind::e_TRUE);
      leftExp = std::make_unique<mjast::Exp>(mjast::True{});
    } break;

    case Token::Kind::e_FALSE: {
      leftExpFilled = true;
      eat(Token::Kind::e_FALSE);
      leftExp = std::make_unique<mjast::Exp>(mjast::False{});
    } break;

    case Token::Kind::e_IDENTIFIER: {
      leftExpFilled = true;
      auto name = d_tok.matchValue(
          [](StringIndex const &x) -> StringIndex { return x; },
          [&](auto const &) -> StringIndex {
            return d_stringtable_p->insert("");
          });
      eat(Token::Kind::e_IDENTIFIER);
      leftExp =
          std::make_unique<mjast::Exp>(mjast::IdentifierExp{std::move(name)});
    } break;

    case Token::Kind::e_THIS: {
      leftExpFilled = true;
      eat(Token::Kind::e_THIS);
      leftExp = std::make_unique<mjast::Exp>(mjast::This{});
    } break;

    case Token::Kind::e_NEW: {
      eat(Token::Kind::e_NEW);
      auto firstNew = true;
      while (!leftExpFilled) {
        switch (d_tok.kind()) {
        case Token::Kind::e_INT: {
          leftExpFilled = true;
          eat(Token::Kind::e_INT);
          eat(Token::Kind::e_LBRACKET);
          auto sizeExpr = expression();
          eat(Token::Kind::e_RBRACKET);
          leftExp = std::make_unique<mjast::Exp>(
              mjast::NewArray{std::move(sizeExpr)});
        } break;

        case Token::Kind::e_IDENTIFIER: {
          leftExpFilled = true;
          auto name = identifier();
          eat(Token::Kind::e_LPAREN);
          eat(Token::Kind::e_RPAREN);
          leftExp =
              std::make_unique<mjast::Exp>(mjast::NewObject{std::move(name)});
        } break;

        case Token::Kind::e_EOF: {
          return std::make_unique<mjast::Exp>();
        } break;

        default: {
          if (firstNew) {
            firstNew = false;
            error();
          }
          advance();
        } break;
        }
      }
    } break;

    case Token::Kind::e_BANG: {
      leftExpFilled = true;
      eat(Token::Kind::e_BANG);
      leftExp = std::make_unique<mjast::Exp>(mjast::Not{expression()});
    } break;

    case Token::Kind::e_LPAREN: {
      leftExpFilled = true;
      eat(Token::Kind::e_LPAREN);
      leftExp = expression();
      eat(Token::Kind::e_RPAREN);
    } break;

    case Token::Kind::e_EOF: {
      return std::make_unique<mjast::Exp>();
    } break;

    default: {
      if (first) {
        first = false;
        error();
      }
      advance();
    } break;
    }
  }

  while (true) {
    if (auto nextTokenKind = d_tok.kind();
        pri <= 4 && nextTokenKind == Token::Kind::e_STAR) {

      eat(Token::Kind::e_STAR);
      auto rightExp = expression(5);
      leftExp = std::make_unique<mjast::Exp>(
          mjast::Times{std::move(leftExp), std::move(rightExp)});

    } else if (pri <= 3 && (nextTokenKind == Token::Kind::e_PLUS ||
                            nextTokenKind == Token::Kind::e_MINUS)) {

      if (nextTokenKind == Token::Kind::e_PLUS) {
        eat(Token::Kind::e_PLUS);
        auto rightExp = expression(4);
        leftExp = std::make_unique<mjast::Exp>(
            mjast::Plus{std::move(leftExp), std::move(rightExp)});
      } else {
        eat(Token::Kind::e_MINUS);
        auto rightExp = expression(4);
        leftExp = std::make_unique<mjast::Exp>(
            mjast::Minus{std::move(leftExp), std::move(rightExp)});
      }

    } else if (pri <= 2 && nextTokenKind == Token::Kind::e_LESSTHAN) {

      eat(Token::Kind::e_LESSTHAN);
      auto rightExp = expression(3);
      leftExp = std::make_unique<mjast::Exp>(
          mjast::LessThan{std::move(leftExp), std::move(rightExp)});

    } else if (pri <= 1 && nextTokenKind == Token::Kind::e_DOUBLE_AMPERSAND) {

      eat(Token::Kind::e_DOUBLE_AMPERSAND);
      auto rightExp = expression(2);
      leftExp = std::make_unique<mjast::Exp>(
          mjast::And{std::move(leftExp), std::move(rightExp)});

    } else if (pri <= 5 && (nextTokenKind == Token::Kind::e_LBRACKET ||
                            nextTokenKind == Token::Kind::e_DOT)) {

      if (nextTokenKind == Token::Kind::e_LBRACKET) {
        eat(Token::Kind::e_LBRACKET);
        auto rightExp = expression();
        eat(Token::Kind::e_RBRACKET);
        leftExp = std::make_unique<mjast::Exp>(
            mjast::ArrayLookup{std::move(leftExp), std::move(rightExp)});
      } else {
        eat(Token::Kind::e_DOT);
        auto firstMethErr = true;
        while (true) {
          if (nextTokenKind = d_tok.kind();
              nextTokenKind == Token::Kind::e_LENGTH) {

            eat(Token::Kind::e_LENGTH);
            leftExp = std::make_unique<mjast::Exp>(
                mjast::ArrayLength{std::move(leftExp)});
            break;

          } else if (nextTokenKind == Token::Kind::e_IDENTIFIER) {

            auto methodName = identifier();
            eat(Token::Kind::e_LPAREN);
            auto args = std::make_unique<mjast::ExpList>();

            static constexpr auto expressionFirstSet =
                std::array{Token::Kind::e_INTEGER_LITERAL,
                           Token::Kind::e_TRUE,
                           Token::Kind::e_FALSE,
                           Token::Kind::e_IDENTIFIER,
                           Token::Kind::e_THIS,
                           Token::Kind::e_NEW,
                           Token::Kind::e_BANG,
                           Token::Kind::e_LPAREN};

            if (std::any_of(expressionFirstSet.begin(),
                            expressionFirstSet.end(),
                            [&](auto k) { return k == d_tok.kind(); })) {
              args->exps.push_back(expression());
              while (d_tok.kind() == Token::Kind::e_COMMA) {
                eat(Token::Kind::e_COMMA);
                args->exps.push_back(expression());
              }
            }

            eat(Token::Kind::e_RPAREN);
            leftExp = std::make_unique<mjast::Exp>(mjast::Call{
                std::move(leftExp), std::move(methodName), std::move(args)});
            break;

          } else if (nextTokenKind == Token::Kind::e_EOF) {

            return std::move(leftExp);

          } else {

            if (firstMethErr) {
              firstMethErr = false;
              error();
            }
            advance();
          }
        }
      }

    } else {
      return std::move(leftExp);
    }
  }
}

std::unique_ptr<mjast::Identifier> Parser::identifier() {
  // identifier : IDENTIFIER
  auto name = std::make_unique<mjast::Identifier>(mjast::Identifier{
      d_tok.matchValue([](StringIndex const &x) -> StringIndex { return x; },
                       [&](auto const &) -> StringIndex {
                         return d_stringtable_p->insert("");
                       })});
  eat(Token::Kind::e_IDENTIFIER);
  return std::move(name);
}

} // namespace mjc