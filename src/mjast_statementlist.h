#ifndef MJAST_STATEMENTLIST_INCLUDED
#define MJAST_STATEMENTLIST_INCLUDED

#include <memory>
#include <vector>

namespace mjast {

struct Statement;

struct StatementList {
  std::vector<std::unique_ptr<Statement>> stmts;
};

} // namespace mjast

#endif // MJAST_STATEMENTLIST_INCLUDED