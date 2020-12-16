#ifndef MJC_VARIANT_INCLUDED
#define MJC_VARIANT_INCLUDED

#include <mjc_overloadset.h>
#include <mjc_traits.h>
#include <variant>

namespace mjc {

template <typename... Types> class Variant {

public:
  using ValueType = std::variant<Types...>;

  constexpr Variant() noexcept = default;

  template <
      typename Arg,
      mjc::Requires<mjc::Any<std::is_constructible<ValueType, Arg &&>,
                             std::is_convertible<Arg &&, ValueType>>> = nullptr>
  constexpr explicit Variant(Arg &&value) noexcept
      : d_value{std::forward<Arg>(value)} {}

  template <
      typename... Funcs,
      mjc::Requires<mjc::AllFromList<mjc::TransformFromList<
          std::is_void,
          mjc::TransformApplyFromList<
              mjc::Bind<std::invoke_result,
                        mjc::OverloadSet<std::decay_t<Funcs>...>>,
              mjc::TransformFromList<
                  std::add_lvalue_reference,
                  mjc::TransformFromList<std::add_const,
                                         mjc::ToList<ValueType>>>>>>> = nullptr>
  constexpr void match(Funcs &&... funcs) const {
    mjc::OverloadSet visitor{std::forward<Funcs>(funcs)...};
    std::visit(visitor, d_value);
  }

  template <typename... Funcs,
            mjc::Requires<mjc::AllFromList<mjc::TransformFromList<
                std::negation,
                mjc::TransformFromList<
                    std::is_void,
                    mjc::TransformApplyFromList<
                        mjc::Bind<std::invoke_result,
                                  mjc::OverloadSet<std::decay_t<Funcs>...>>,
                        mjc::TransformFromList<
                            std::add_lvalue_reference,
                            mjc::TransformFromList<
                                std::add_const, mjc::ToList<ValueType>>>>>>>> =
                nullptr>
  constexpr auto match(Funcs &&... funcs) const {
    static_assert(
        mjc::AllSameFromList<mjc::TransformApplyFromList<
            mjc::Bind<std::invoke_result,
                      mjc::OverloadSet<std::decay_t<Funcs>...>>,
            mjc::TransformFromList<
                std::add_lvalue_reference,
                mjc::TransformFromList<std::add_const,
                                       mjc::ToList<ValueType>>>>>,
        "match function object parameters must all return the same type");
    mjc::OverloadSet visitor{std::forward<Funcs>(funcs)...};
    return std::visit(visitor, d_value);
  }

  template <
      typename... Funcs,
      mjc::Requires<mjc::AllFromList<mjc::TransformFromList<
          std::is_void, mjc::TransformApplyFromList<
                            mjc::Bind<std::invoke_result,
                                      mjc::OverloadSet<std::decay_t<Funcs>...>>,
                            mjc::TransformFromList<std::add_lvalue_reference,
                                                   mjc::ToList<ValueType>>>>>> =
          nullptr>
  constexpr void match(Funcs &&... funcs) {
    mjc::OverloadSet visitor{std::forward<Funcs>(funcs)...};
    std::visit(visitor, d_value);
  }

  template <
      typename... Funcs,
      mjc::Requires<mjc::AllFromList<mjc::TransformFromList<
          std::negation,
          mjc::TransformFromList<
              std::is_void,
              mjc::TransformApplyFromList<
                  mjc::Bind<std::invoke_result,
                            mjc::OverloadSet<std::decay_t<Funcs>...>>,
                  mjc::TransformFromList<std::add_lvalue_reference,
                                         mjc::ToList<ValueType>>>>>>> = nullptr>
  constexpr auto match(Funcs &&... funcs) {
    static_assert(
        mjc::AllSameFromList<mjc::TransformApplyFromList<
            mjc::Bind<std::invoke_result,
                      mjc::OverloadSet<std::decay_t<Funcs>...>>,
            mjc::TransformFromList<std::add_lvalue_reference,
                                   mjc::ToList<ValueType>>>>,
        "match function object parameters must all return the same type");
    mjc::OverloadSet visitor{std::forward<Funcs>(funcs)...};
    return std::visit(visitor, d_value);
  }

private:
  ValueType d_value;
};

} // namespace mjc

#endif // MJC_VARIANT_INCLUDED