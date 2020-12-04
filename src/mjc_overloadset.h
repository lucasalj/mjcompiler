#ifndef MJC_OVERLOADSET_INCLUDED
#define MJC_OVERLOADSET_INCLUDED

#include <type_traits>

namespace mjc {

template <typename... Funcs> struct OverloadSet : Funcs... {
  using Funcs::operator()...;
};
template <typename... Funcs>
OverloadSet(Funcs &&...) -> OverloadSet<std::decay_t<Funcs>...>;

} // namespace mjc

#endif // MJC_OVERLOADSET_INCLUDED
