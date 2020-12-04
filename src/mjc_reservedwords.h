#ifndef MJC_RESERVEDWORDS_INCLUDED
#define MJC_RESERVEDWORDS_INCLUDED

#include <array>
#include <mjc_token.h>
#include <optional>
#include <string_view>

namespace mjc {

using std::operator""sv;

class ReservedWords {
public:
  constexpr bool contains(std::string_view key) const;
  constexpr std::optional<Token::Kind> tokenKind(std::string_view key) const;

private:
  constexpr std::size_t dekHash(std::size_t x, std::string_view s) const;
  constexpr std::size_t perfectHash(std::string_view key) const;
  static constexpr auto G =
      std::array{0, 0,  0,  24, 0,  1,  4,  12, 22, 3, 19, 14, 0,
                 0, 21, 20, 4,  23, 13, 14, 0,  22, 5, 17, 3,  12};
  static constexpr auto words = std::array{"class"sv,   "public"sv,
                                           "static"sv,  "void"sv,
                                           "main"sv,    "String"sv,
                                           "extends"sv, "return"sv,
                                           "int"sv,     "boolean"sv,
                                           "if"sv,      "else"sv,
                                           "while"sv,   "System.out.println"sv,
                                           "length"sv,  "true"sv,
                                           "false"sv,   "this"sv,
                                           "new"sv};
  static constexpr auto tokenKinds = std::array{
      Token::Kind::e_CLASS,   Token::Kind::e_PUBLIC,  Token::Kind::e_STATIC,
      Token::Kind::e_VOID,    Token::Kind::e_MAIN,    Token::Kind::e_STRING,
      Token::Kind::e_EXTENDS, Token::Kind::e_RETURN,  Token::Kind::e_INT,
      Token::Kind::e_BOOLEAN, Token::Kind::e_IF,      Token::Kind::e_ELSE,
      Token::Kind::e_WHILE,   Token::Kind::e_PRINTLN, Token::Kind::e_LENGTH,
      Token::Kind::e_TRUE,    Token::Kind::e_FALSE,   Token::Kind::e_THIS,
      Token::Kind::e_NEW};
};

constexpr std::size_t ReservedWords::dekHash(std::size_t x,
                                             std::string_view s) const {
  for (char c : s) {
    x = ((x << 5) ^ (x >> 27) ^ std::size_t(c)) % (std::size_t(1) << 31);
  }
  return x % 26;
}

constexpr std::size_t ReservedWords::perfectHash(std::string_view key) const {
  return (G[dekHash(1963033211, key)] + G[dekHash(15597902, key)]) % 26;
}

constexpr bool ReservedWords::contains(std::string_view key) const {
  auto index = perfectHash(key);
  return (index < words.size()) && (key == words[index]);
}

constexpr std::optional<Token::Kind>
ReservedWords::tokenKind(std::string_view key) const {
  auto index = perfectHash(key);
  if ((index >= tokenKinds.size()) || (key != words[index])) {
    return std::nullopt;
  }
  return tokenKinds[index];
}

} // namespace mjc

#endif // MJC_RESERVEDWORDS_INCLUDED