#ifndef MJC_TOKEN_INCLUDED
#define MJC_TOKEN_INCLUDED

#include <fmt/format.h>
#include <iostream>
#include <magic_enum.hpp>
#include <mjc_loggingassertionhandler.h>
#include <mjc_overloadset.h>
#include <mjc_traits.h>
#include <optional>
#include <string>
#include <variant>

namespace mjc {

class Token {
public:
  using ValueType = std::optional<std::variant<int, std::string>>;
  enum Kind {
    e_CLASS,            // "class"
    e_IDENTIFIER,       // identifier
    e_LBRACE,           // {
    e_RBRACE,           // }
    e_PUBLIC,           // "public"
    e_STATIC,           // "static"
    e_VOID,             // "void"
    e_MAIN,             // "main"
    e_LPAREN,           // (
    e_RPAREN,           // )
    e_STRING,           // "String"
    e_LBRACKET,         // [
    e_RBRACKET,         // ]
    e_EXTENDS,          // "extends"
    e_SEMI,             // ;
    e_RETURN,           // "return"
    e_COMMA,            // ,
    e_INT,              // "int"
    e_BOOLEAN,          // "boolean"
    e_EQUAL,            // =
    e_IF,               // "if"
    e_ELSE,             // "else"
    e_WHILE,            // "while"
    e_PRINTLN,          // "System.out.println"
    e_DOUBLE_AMPERSAND, // "&&"
    e_LESSTHAN,         // <
    e_PLUS,             // +
    e_MINUS,            // -
    e_STAR,             // *
    e_DOT,              // .
    e_LENGTH,           // "length"
    e_INTEGER_LITERAL,  // integer literal
    e_TRUE,             // "true"
    e_FALSE,            // "false"
    e_THIS,             // "this"
    e_NEW,              // "new"
    e_BANG,             // !
    e_EOF               // EOF
  };

  Token() noexcept = default;

  explicit constexpr Token(Kind kind) noexcept;

  template <typename Arg,
            Requires<Any<std::is_constructible<ValueType, Arg &&>,
                         std::is_convertible<Arg &&, ValueType>>> = nullptr>
  constexpr Token(Kind kind, Arg &&value) noexcept;

  constexpr auto kind() const;

  constexpr bool hasValue() const;

  template <
      typename... Funcs,
      Requires<All<
          std::is_void<
              std::invoke_result_t<OverloadSet<std::decay_t<Funcs>...>, int>>,
          std::is_void<std::invoke_result_t<
              OverloadSet<std::decay_t<Funcs>...>,
              std::add_lvalue_reference_t<std::add_const_t<std::string>>>>>> =
          nullptr>
  constexpr void matchValue(Funcs &&... funcs) const;

  template <
      typename... Funcs,
      Requires<All<
          std::negation<std::is_void<
              std::invoke_result_t<OverloadSet<std::decay_t<Funcs>...>, int>>>,
          std::negation<std::is_void<std::invoke_result_t<
              OverloadSet<std::decay_t<Funcs>...>,
              std::add_lvalue_reference_t<std::add_const_t<std::string>>>>>>> =
          nullptr>
  constexpr auto matchValue(Funcs &&... funcs) const;

  friend constexpr bool operator==(Token const &lhs, Token const &rhs) noexcept;

private:
  Kind d_kind{e_EOF};
  ValueType d_value;
};

constexpr Token::Token(Kind kind) noexcept : d_kind{kind} {}

template <typename Arg,
          Requires<Any<std::is_constructible<Token::ValueType, Arg &&>,
                       std::is_convertible<Arg &&, Token::ValueType>>>>
constexpr Token::Token(Kind kind, Arg &&value) noexcept
    : d_kind{kind}, d_value{std::forward<Arg>(value)} {
  MJC_ASSERT_ALWAYS(
      (d_value && std::visit(OverloadSet{[&](int) -> bool {
                                           return d_kind == e_INTEGER_LITERAL;
                                         },
                                         [&](std::string const &) -> bool {
                                           return d_kind == e_IDENTIFIER;
                                         }},
                             *d_value)),
      mjc::LoggingAssertionHandler{},
      "Token kind is not compatible with its value type {}", *this);
}

constexpr auto Token::kind() const { return d_kind; }
constexpr bool Token::hasValue() const { return d_value.has_value(); }

template <
    typename... Funcs,
    Requires<
        All<std::is_void<
                std::invoke_result_t<OverloadSet<std::decay_t<Funcs>...>, int>>,
            std::is_void<std::invoke_result_t<
                OverloadSet<std::decay_t<Funcs>...>,
                std::add_lvalue_reference_t<std::add_const_t<std::string>>>>>>>
constexpr void Token::matchValue(Funcs &&... funcs) const {
  MJC_ASSERT_ALWAYS(d_value.has_value(), mjc::LoggingAssertionHandler{},
                    "Token {} has no value\n", *this);
  std::visit(OverloadSet{std::forward<Funcs>(funcs)...}, *d_value);
}

template <
    typename... Funcs,
    Requires<
        All<std::negation<std::is_void<std::invoke_result_t<
                OverloadSet<std::decay_t<Funcs>...>, int>>>,
            std::negation<std::is_void<std::invoke_result_t<
                OverloadSet<std::decay_t<Funcs>...>,
                std::add_lvalue_reference_t<std::add_const_t<std::string>>>>>>>>
constexpr auto Token::matchValue(Funcs &&... funcs) const {
  MJC_ASSERT_ALWAYS(d_value.has_value(), mjc::LoggingAssertionHandler{},
                    "Token {} has no value\n", *this);
  return std::visit(OverloadSet{std::forward<Funcs>(funcs)...}, *d_value);
}

constexpr bool operator==(Token const &lhs, Token const &rhs) noexcept {
  return (lhs.kind() == rhs.kind()) && (lhs.hasValue() == rhs.hasValue()) &&
         (lhs.d_value == rhs.d_value);
}

constexpr bool operator!=(Token const &lhs, Token const &rhs) noexcept {
  return !(lhs == rhs);
}

inline std::ostream &operator<<(std::ostream &os, Token const &tok) {
  os << fmt::format("{}", tok);
  return os;
}

} // namespace mjc

template <> struct fmt::formatter<mjc::Token> : formatter<std::string_view> {
  template <typename FormatContext>
  auto format(mjc::Token const &token, FormatContext &ctx);
};

template <typename FormatContext>
auto fmt::formatter<mjc::Token>::format(mjc::Token const &token,
                                        FormatContext &ctx) {
  return format_to(ctx.out(), "Token(Token::Kind::{}{})",
                   magic_enum::enum_name(token.kind()),
                   (token.hasValue()
                        ? token.matchValue(
                              [](int value) -> std::string {
                                return fmt::format(", {}", value);
                              },
                              [](std::string const &value) -> std::string {
                                return fmt::format(", \"{}\"", value);
                              })
                        : std::string()));
}

#endif // MJC_TOKEN_INCLUDED