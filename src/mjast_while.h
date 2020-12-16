#ifndef MJAST_WHILE_INCLUDED
#define MJAST_WHILE_INCLUDED

#include <memory>

namespace mjast {

struct Exp;
struct Statement;

struct While {
  std::unique_ptr<Exp> cond;
  std::unique_ptr<Statement> loopStmt;
};

} // namespace mjast

#endif // MJAST_WHILE_INCLUDED