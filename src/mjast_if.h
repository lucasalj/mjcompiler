#ifndef MJAST_IF_INCLUDED
#define MJAST_IF_INCLUDED

#include <memory>

namespace mjast {

struct Exp;
struct Statement;

struct If {
  std::unique_ptr<Exp> cond;
  std::unique_ptr<Statement> truePathStmt;
  std::unique_ptr<Statement> falsePathStmt;
};

} // namespace mjast

#endif // MJAST_IF_INCLUDED