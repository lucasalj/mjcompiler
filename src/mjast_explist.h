#ifndef MJAST_EXPLIST_INCLUDED
#define MJAST_EXPLIST_INCLUDED

#include <memory>
#include <vector>

namespace mjast {

struct Exp;

struct ExpList {
  std::vector<std::unique_ptr<Exp>> exps;
};

} // namespace mjast

#endif // MJAST_EXPLIST_INCLUDED