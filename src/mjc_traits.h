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

namespace detail {
template <typename L> struct Any : std::false_type {};
template <typename Head, typename... Tail>
struct Any<List<Head, Tail...>>
    : std::conditional_t<Head::value, std::true_type, All<List<Tail...>>> {};

template <> struct Any<List<>> : std::false_type {};
} // namespace detail

template <typename... Cond>
constexpr bool Any = detail::Any<List<Cond...>>::value;

template <bool Cond> using Requires = std::enable_if_t<Cond> *;

} // namespace mjc

#endif // MJC_TRATIS_INCLUDED