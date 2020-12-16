#ifndef MJAST_PROGRAM_INCLUDED
#define MJAST_PROGRAM_INCLUDED

#include <memory>

namespace mjast {

struct MainClass;
struct ClassDeclList;

struct Program {
  std::unique_ptr<MainClass> main;
  std::unique_ptr<ClassDeclList> classes;
};

} // namespace mjast

#endif // MJAST_PROGRAM_INCLUDED