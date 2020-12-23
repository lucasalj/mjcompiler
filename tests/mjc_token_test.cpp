#include <catch.hpp>
#include <mjc_token.h>

TEST_CASE("Token", "[token]") {
  using namespace mjc;
  auto strTable = std::make_unique<mjc::StringTable>();
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
    Token kindAndValueConstructed{Token::Kind::e_INTEGER_LITERAL, 127};
    REQUIRE(kindAndValueConstructed.kind() == Token::Kind::e_INTEGER_LITERAL);
    REQUIRE(kindAndValueConstructed.hasValue());
    REQUIRE(kindAndValueConstructed.matchValue(
                [](int value) -> int { return value; },
                [](auto &&) -> int { return -1; }) == 127);
  }
  SECTION("kind and value constructor: identifier") {
    Token kindAndValueConstructed{Token::Kind::e_IDENTIFIER,
                                  strTable->insert("x")};
    REQUIRE(kindAndValueConstructed.kind() == Token::Kind::e_IDENTIFIER);
    REQUIRE(kindAndValueConstructed.hasValue());
    REQUIRE(
        kindAndValueConstructed.matchValue(
            [](std::string_view value) -> std::string_view { return value; },
            [](int) -> std::string_view { return "error"; }) == "x");
  }
  SECTION("Formatter: simple") {
    Token lparen{Token::Kind::e_LPAREN};
    REQUIRE(fmt::format("{}", lparen) ==
            std::string_view("Token(Token::Kind::e_LPAREN)"));
  }
  SECTION("Formatter: integer literal") {
    Token intLit{Token::Kind::e_INTEGER_LITERAL, 65535};
    REQUIRE(fmt::format("{}", intLit) ==
            std::string_view("Token(Token::Kind::e_INTEGER_LITERAL, 65535)"));
  }
  SECTION("Formatter: identifier") {
    Token id{Token::Kind::e_IDENTIFIER, strTable->insert("i")};
    REQUIRE(fmt::format("{}", id) ==
            std::string_view("Token(Token::Kind::e_IDENTIFIER, \"i\")"));
  }
}