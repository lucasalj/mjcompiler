#ifndef MJAST_MAINCLASS_INCLUDED
#define MJAST_MAINCLASS_INCLUDED

#include <memory>

namespace mjast {

struct Identifier;
struct Statement;

struct MainClass {
  std::unique_ptr<Identifier> className, mainArgsParamName;
  std::unique_ptr<Statement> stmt;
};

} // namespace mjast

#endif // MJAST_MAINCLASS_INCLUDED