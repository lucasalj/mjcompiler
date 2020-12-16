#include <catch.hpp>
#include <filesystem>
#include <mjc_lexer.h>

TEST_CASE("Lexical analysis", "[lexer]") {
  using namespace mjc;
  auto filePath =
      (std::filesystem::current_path() / std::filesystem::path{"files"} /
       std::filesystem::path{"factorial.java"})
          .generic_string();
  auto lexer = Lexer::create(filePath);
  REQUIRE(lexer);
  auto const expectedTokens =
      std::array{Token(Token::Kind::e_CLASS),
                 Token(Token::Kind::e_IDENTIFIER, "Factorial"),
                 Token(Token::Kind::e_LBRACE),
                 Token(Token::Kind::e_PUBLIC),
                 Token(Token::Kind::e_STATIC),
                 Token(Token::Kind::e_VOID),
                 Token(Token::Kind::e_MAIN),
                 Token(Token::Kind::e_LPAREN),
                 Token(Token::Kind::e_STRING),
                 Token(Token::Kind::e_LBRACKET),
                 Token(Token::Kind::e_RBRACKET),
                 Token(Token::Kind::e_IDENTIFIER, "a"),
                 Token(Token::Kind::e_RPAREN),
                 Token(Token::Kind::e_LBRACE),
                 Token(Token::Kind::e_PRINTLN),
                 Token(Token::Kind::e_LPAREN),
                 Token(Token::Kind::e_NEW),
                 Token(Token::Kind::e_IDENTIFIER, "Fac"),
                 Token(Token::Kind::e_LPAREN),
                 Token(Token::Kind::e_RPAREN),
                 Token(Token::Kind::e_DOT),
                 Token(Token::Kind::e_IDENTIFIER, "ComputeFac"),
                 Token(Token::Kind::e_LPAREN),
                 Token(Token::Kind::e_INTEGER_LITERAL, 10),
                 Token(Token::Kind::e_RPAREN),
                 Token(Token::Kind::e_RPAREN),
                 Token(Token::Kind::e_SEMI),
                 Token(Token::Kind::e_RBRACE),
                 Token(Token::Kind::e_RBRACE),
                 Token(Token::Kind::e_CLASS),
                 Token(Token::Kind::e_IDENTIFIER, "Fac"),
                 Token(Token::Kind::e_LBRACE),
                 Token(Token::Kind::e_PUBLIC),
                 Token(Token::Kind::e_INT),
                 Token(Token::Kind::e_IDENTIFIER, "ComputeFac"),
                 Token(Token::Kind::e_LPAREN),
                 Token(Token::Kind::e_INT),
                 Token(Token::Kind::e_IDENTIFIER, "num"),
                 Token(Token::Kind::e_RPAREN),
                 Token(Token::Kind::e_LBRACE),
                 Token(Token::Kind::e_INT),
                 Token(Token::Kind::e_IDENTIFIER, "num_aux"),
                 Token(Token::Kind::e_SEMI),
                 Token(Token::Kind::e_IF),
                 Token(Token::Kind::e_LPAREN),
                 Token(Token::Kind::e_IDENTIFIER, "num"),
                 Token(Token::Kind::e_LESSTHAN),
                 Token(Token::Kind::e_INTEGER_LITERAL, 1),
                 Token(Token::Kind::e_RPAREN),
                 Token(Token::Kind::e_IDENTIFIER, "num_aux"),
                 Token(Token::Kind::e_EQUAL),
                 Token(Token::Kind::e_INTEGER_LITERAL, 1),
                 Token(Token::Kind::e_SEMI),
                 Token(Token::Kind::e_ELSE),
                 Token(Token::Kind::e_IDENTIFIER, "num_aux"),
                 Token(Token::Kind::e_EQUAL),
                 Token(Token::Kind::e_IDENTIFIER, "num"),
                 Token(Token::Kind::e_STAR),
                 Token(Token::Kind::e_LPAREN),
                 Token(Token::Kind::e_THIS),
                 Token(Token::Kind::e_DOT),
                 Token(Token::Kind::e_IDENTIFIER, "ComputeFac"),
                 Token(Token::Kind::e_LPAREN),
                 Token(Token::Kind::e_IDENTIFIER, "num"),
                 Token(Token::Kind::e_MINUS),
                 Token(Token::Kind::e_INTEGER_LITERAL, 1),
                 Token(Token::Kind::e_RPAREN),
                 Token(Token::Kind::e_RPAREN),
                 Token(Token::Kind::e_SEMI),
                 Token(Token::Kind::e_RETURN),
                 Token(Token::Kind::e_IDENTIFIER, "num_aux"),
                 Token(Token::Kind::e_SEMI),
                 Token(Token::Kind::e_RBRACE),
                 Token(Token::Kind::e_RBRACE),
                 Token(Token::Kind::e_EOF)};
  for (auto &&expectedToken : expectedTokens) {
    REQUIRE(expectedToken == lexer->nextToken());
  }
}