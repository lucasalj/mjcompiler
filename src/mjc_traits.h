#ifndef MJC_TRATIS_INCLUDED
#define MJC_TRATIS_INCLUDED

#include <type_traits>

namespace mjc {

template <typename... T> struct List {};

namespace detail {
template <typename L> struct ToList;

template <template <class...> class ListType, typename... T>
struct ToList<ListType<T...>> {
  using type = List<T...>;
};
} // namespace detail

template <typename L> using ToList = typename detail::ToList<L>::type;

namespace detail {
template <typename L> struct All : std::false_type {};
template <typename Head, typename... Tail>
struct All<List<Head, Tail...>>
    : std::conditional_t<Head::value, All<List<Tail...>>, std::false_type> {};

template <> struct All<List<>> : std::true_type {};
} // namespace detail

template <typename... Cond>
constexpr bool All = detail::All<List<Cond...>>::value;

template <typename L> constexpr bool AllFromList = detail::All<L>::value;

namespace detail {
template <typename L> struct Any : std::false_type {};
template <typename Head, typename... Tail>
struct Any<List<Head, Tail...>>
    : std::conditional_t<Head::value, std::true_type, All<List<Tail...>>> {};

template <> struct Any<List<>> : std::false_type {};
} // namespace detail

template <typename... Cond>
constexpr bool Any = detail::Any<List<Cond...>>::value;

template <typename L> constexpr bool AnyFromList = detail::Any<L>::value;

template <bool Cond> using Requires = std::enable_if_t<Cond> *;

template <template <class...> class F, typename... T> struct Bind {};

namespace detail {

template <typename Lambda, typename... Args> struct Apply;

template <template <class...> class F, typename... T, typename... Args>
struct Apply<Bind<F, T...>, Args...> {
  using type = typename F<T..., Args...>::type;
};

} // namespace detail

template <typename Lambda, typename... Args>
using Apply = typename detail::Apply<Lambda, Args...>::type;

namespace detail {

template <template <class...> class F, typename L> struct Transform;

template <template <class...> class F, typename... T>
struct Transform<F, List<T...>> {
  using type = List<typename F<T>::type...>;
};

template <typename Lambda, typename L> struct TransformApply;

template <template <class...> class F, typename... T, typename... Args>
struct TransformApply<Bind<F, T...>, List<Args...>> {
  using type = List<typename F<T..., Args>::type...>;
};

} // namespace detail

template <template <class...> class F, typename... T>
using Transform = typename detail::Transform<F, List<T...>>::type;

template <template <class...> class F, typename L>
using TransformFromList = typename detail::Transform<F, L>::type;

template <typename Lambda, typename... T>
using TransformApply =
    typename detail::TransformApply<Lambda, List<T...>>::type;

template <typename Lambda, typename L>
using TransformApplyFromList = typename detail::TransformApply<Lambda, L>::type;

namespace detail {

template <typename L> struct AllSame : std::false_type {};

template <typename First, typename Second, typename... Tail>
struct AllSame<List<First, Second, Tail...>>
    : std::conditional_t<std::is_same_v<First, Second>,
                         AllSame<List<First, Tail...>>, std::false_type> {};

template <typename First> struct AllSame<List<First>> : std::true_type {};

template <> struct AllSame<List<>> : std::true_type {};

} // namespace detail

template <typename... T>
constexpr bool AllSame = detail::AllSame<List<T...>>::value;

template <typename L>
constexpr bool AllSameFromList = detail::AllSame<L>::value;

} // namespace mjc

#endif // MJC_TRATIS_INCLUDED