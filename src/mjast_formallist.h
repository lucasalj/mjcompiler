#ifndef MJAST_FORMALLIST_INCLUDED
#define MJAST_FORMALLIST_INCLUDED

#include <memory>
#include <vector>

namespace mjast {

struct Formal;

struct FormalList {
  std::vector<std::unique_ptr<Formal>> formals;
};

} // namespace mjast

#endif // MJAST_FORMALLIST_INCLUDED