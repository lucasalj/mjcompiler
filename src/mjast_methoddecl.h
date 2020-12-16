#ifndef MJAST_METHODDECL_INCLUDED
#define MJAST_METHODDECL_INCLUDED

#include <memory>

namespace mjast {

struct Type;
struct Identifier;
struct FormalList;
struct VarDeclList;
struct StatementList;
struct Exp;

struct MethodDecl {
  std::unique_ptr<Type> returnTyp;
  std::unique_ptr<Identifier> name;
  std::unique_ptr<FormalList> formals;
  std::unique_ptr<VarDeclList> vars;
  std::unique_ptr<StatementList> stmts;
  std::unique_ptr<Exp> returnValueExp;
};

} // namespace mjast

#endif // MJAST_METHODDECL_INCLUDED