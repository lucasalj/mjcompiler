#ifndef MJC_ASTDOTPRINTER_INCLUDED
#define MJC_ASTDOTPRINTER_INCLUDED

#include <sstream>
#include <string>

namespace mjast {
struct Program;
struct MainClass;
struct ClassDecl;
struct ClassDeclList;
struct VarDecl;
struct VarDeclList;
struct MethodDecl;
struct MethodDeclList;
struct Formal;
struct FormalList;
struct Type;
struct IntArrayType;
struct BooleanType;
struct IntegerType;
struct IdentifierType;
struct Statement;
struct StatementList;
struct Exp;
struct ExpList;
struct Identifier;
} // namespace mjast

namespace mjc {

class AstDotPrinter {
public:
  void print(std::string &out, mjast::Program *prog);

private:
  std::pair<std::string, std::string> visit(mjast::Program const &prog);
  std::pair<std::string, std::string> visit(mjast::MainClass const &mainClass);
  std::pair<std::string, std::string>
  visit(mjast::ClassDeclList const &classes);
  std::pair<std::string, std::string>
  visit(mjast::ClassDecl const &classDeclaration);
  std::pair<std::string, std::string>
  visit(mjast::VarDeclList const &variables);
  std::pair<std::string, std::string>
  visit(mjast::VarDecl const &variableDeclaration);
  std::pair<std::string, std::string>
  visit(mjast::MethodDeclList const &methods);
  std::pair<std::string, std::string>
  visit(mjast::MethodDecl const &methodDeclaration);
  std::pair<std::string, std::string> visit(mjast::FormalList const &formals);
  std::pair<std::string, std::string> visit(mjast::Formal const &formal);
  std::pair<std::string, std::string> visit(mjast::Type const &typ);
  std::pair<std::string, std::string>
  visit(mjast::StatementList const &statements);
  std::pair<std::string, std::string> visit(mjast::Statement const &statement);
  std::pair<std::string, std::string> visit(mjast::ExpList const &expressions);
  std::pair<std::string, std::string> visit(mjast::Exp const &expression);
  std::pair<std::string, std::string>
  visit(mjast::Identifier const &identifier);
  std::pair<std::string, std::string> visit(std::string const &str);
  std::pair<std::string, std::string> visit(int const &i);

  [[nodiscard]] int nextId();

  int d_id{0};
};

} // namespace mjc

#endif // MJC_ASTDOTPRINTER_INCLUDED