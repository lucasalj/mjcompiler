#ifndef MJAST_CALL_INCLUDED
#define MJAST_CALL_INCLUDED

#include <memory>

namespace mjast {

struct Exp;
struct Identifier;
struct ExpList;

struct Call {
  std::unique_ptr<Exp> obj;
  std::unique_ptr<Identifier> methodName;
  std::unique_ptr<ExpList> args;
};

} // namespace mjast

#endif // MJAST_CALL_INCLUDED