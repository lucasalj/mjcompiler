#ifndef MJAST_BLOCK_INCLUDED
#define MJAST_BLOCK_INCLUDED

#include <memory>

namespace mjast {

struct StatementList;

struct Block {
  std::unique_ptr<StatementList> stmts;
};

} // namespace mjast

#endif // MJAST_BLOCK_INCLUDED