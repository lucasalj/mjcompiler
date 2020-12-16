#ifndef MJC_PARSER_INCLUDED
#define MJC_PARSER_INCLUDED

// -----------------------------------------------------------------------
// MiniJava Grammar
// -----------------------------------------------------------------------
// goal
//     : mainClass ( classDeclaration )* EOF
//     ;
//
// mainClass
//     : CLASS identifier LBRACE PUBLIC STATIC VOID MAIN LPAREN STRING LBRACKET
//         RBRACKET identifier RPAREN LBRACE statement RBRACE RBRACE
//     ;
//
// classDeclaration
//     : CLASS identifier ( EXTENDS identifier )? LBRACE ( varDeclaration )* (
//         methodDeclaration )* RBRACE
//     ;
//
// varDeclaration
//     : type identifier SEMI
//     ;
//
// methodDeclaration
//     : PUBLIC type identifier LPAREN ( type identifier (COMMA type
//         identifier)* )? RPAREN LBRACE ( varDeclaration )* ( statement )*
//         RETURN expression SEMI RBRACE
//     ;
//
// type
//     : INT ( LBRACKET RBRACKET )?
//     | BOOLEAN
//     | identifier
//     ;
//
// statement
//     : LBRACE ( statement )* RBRACE
//     | IF LPAREN expression RPAREN statement ELSE statement
//     | WHILE LPAREN expression RPAREN statement
//     | PRINTLN LPAREN expression RPAREN SEMI
//     | identifier ( EQUAL expression SEMI | LBRACKET expression RBRACKET EQUAL
//         expression SEMI )
//     ;
//
// expression[pri=0]
//     : ( INTEGER_LITERAL
//         | TRUE
//         | FALSE
//         | identifier
//         | THIS
//         | NEW ( INT LBRACKET expression RBRACKET | identifier LPAREN
//             RPAREN )
//         | BANG expression
//         | LPAREN expression RPAREN
//       )
//       (
//         {pri <= 4}? STAR expression[5]
//         | {pri <= 3}? ( PLUS | MINUS ) expression[4]
//         | {pri <= 2}? LESSTHAN expression[3]
//         | {pri <= 1}? AND expression[2]
//         | {pri <= 5}? ( LBRACKET expression RBRACKET | DOT ( LENGTH |
//             identifier LPAREN ( expression ( COMMA expression )*
//             )? RPAREN ) )
//       )*
//     ;
//
//
// identifier
//     : IDENTIFIER
//     ;

#include <memory>
#include <mjast_and.h>
#include <mjast_arrayassign.h>
#include <mjast_arraylength.h>
#include <mjast_arraylookup.h>
#include <mjast_assign.h>
#include <mjast_block.h>
#include <mjast_booleantype.h>
#include <mjast_call.h>
#include <mjast_classdecl.h>
#include <mjast_classdeclextends.h>
#include <mjast_classdecllist.h>
#include <mjast_classdeclsimple.h>
#include <mjast_exp.h>
#include <mjast_explist.h>
#include <mjast_false.h>
#include <mjast_formal.h>
#include <mjast_formallist.h>
#include <mjast_identifier.h>
#include <mjast_identifierexp.h>
#include <mjast_identifiertype.h>
#include <mjast_if.h>
#include <mjast_intarraytype.h>
#include <mjast_integerliteral.h>
#include <mjast_integertype.h>
#include <mjast_lessthan.h>
#include <mjast_mainclass.h>
#include <mjast_methoddecl.h>
#include <mjast_methoddecllist.h>
#include <mjast_minus.h>
#include <mjast_newarray.h>
#include <mjast_newobject.h>
#include <mjast_not.h>
#include <mjast_plus.h>
#include <mjast_print.h>
#include <mjast_program.h>
#include <mjast_statement.h>
#include <mjast_statementlist.h>
#include <mjast_this.h>
#include <mjast_times.h>
#include <mjast_true.h>
#include <mjast_type.h>
#include <mjast_vardecl.h>
#include <mjast_vardecllist.h>
#include <mjast_while.h>
#include <mjc_lexerprotocol.h>

namespace mjast {
struct Program;
struct MainClass;
struct ClassDecl;
struct VarDecl;
struct MethodDecl;
struct Type;
struct Statement;
struct Exp;
struct Identifier;
} // namespace mjast

namespace mjc {

class Parser {
public:
  Parser(std::unique_ptr<LexerProtocol> lex);
  std::unique_ptr<mjast::Program> parse();
  bool success() const;

private:
  std::unique_ptr<mjast::Program> goal();
  std::unique_ptr<mjast::MainClass> mainClass();
  std::unique_ptr<mjast::ClassDecl> classDeclaration();
  std::unique_ptr<mjast::VarDecl> varDeclaration();
  std::unique_ptr<mjast::MethodDecl> methodDeclaration();
  std::unique_ptr<mjast::Type> type();
  std::unique_ptr<mjast::Statement> statement();
  std::unique_ptr<mjast::Exp> expression(int pri = 0);
  std::unique_ptr<mjast::Identifier> identifier();

  void advance() noexcept;
  void eat(Token::Kind expected) noexcept;
  void error() noexcept;

  bool d_success{true};
  Token d_tok{Token::Kind::e_EOF};
  std::unique_ptr<LexerProtocol> d_lexer;
};
} // namespace mjc

#endif // MJC_PARSER_INCLUDED