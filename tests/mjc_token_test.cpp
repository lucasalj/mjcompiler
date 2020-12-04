#include <catch.hpp>
#include <mjc_token.h>

TEST_CASE("Token", "[token]") {
  using namespace mjc;
  SECTION("default constructor") {
    Token defaultConstructed;
    REQUIRE(defaultConstructed.kind() == Token::Kind::e_EOF);
    REQUIRE(!defaultConstructed.hasValue());
  }
  SECTION("single argument constructor") {
    Token singleArgumentConstructed{Token::Kind::e_IF};
    REQUIRE(singleArgumentConstructed.kind() == Token::Kind::e_IF);
    REQUIRE(!singleArgumentConstructed.hasValue());
  }
  SECTION("kind and value constructor: integer literal") {
    Token kindAndValueConstructed{Token::Kind::e_INT_LIT, 127};
    REQUIRE(kindAndValueConstructed.kind() == Token::Kind::e_INT_LIT);
    REQUIRE(kindAndValueConstructed.hasValue());
    REQUIRE(kindAndValueConstructed.matchValue(
                [](int value) -> int { return value; },
                [](auto &&) -> int { return -1; }) == 127);
  }
  SECTION("kind and value constructor: identifier") {
    Token kindAndValueConstructed{Token::Kind::e_IDENTIFIER, "x"};
    REQUIRE(kindAndValueConstructed.kind() == Token::Kind::e_IDENTIFIER);
    REQUIRE(kindAndValueConstructed.hasValue());
    REQUIRE(
        kindAndValueConstructed.matchValue(
            [](std::string const &value) -> std::string_view { return value; },
            [](auto &&) -> std::string_view { return "error"; }) == "x");
  }
  SECTION("Formatter: simple") {
    Token lparen{Token::Kind::e_LPAREN};
    REQUIRE(fmt::format("{}", lparen) ==
            std::string_view("Token(Token::Kind::e_LPAREN)"));
  }
  SECTION("Formatter: integer literal") {
    Token intLit{Token::Kind::e_INT_LIT, 65535};
    REQUIRE(fmt::format("{}", intLit) ==
            std::string_view("Token(Token::Kind::e_INT_LIT, 65535)"));
  }
  SECTION("Formatter: identifier") {
    Token id{Token::Kind::e_IDENTIFIER, "i"};
    REQUIRE(fmt::format("{}", id) ==
            std::string_view("Token(Token::Kind::e_IDENTIFIER, \"i\")"));
  }
}