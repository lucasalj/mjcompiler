#include <fmt/format.h>
#include <mjast_and.h>
#include <mjast_arrayassign.h>
#include <mjast_arraylength.h>
#include <mjast_arraylookup.h>
#include <mjast_assign.h>
#include <mjast_block.h>
#include <mjast_booleantype.h>
#include <mjast_call.h>
#include <mjast_classdecl.h>
#include <mjast_classdeclextends.h>
#include <mjast_classdecllist.h>
#include <mjast_classdeclsimple.h>
#include <mjast_exp.h>
#include <mjast_explist.h>
#include <mjast_false.h>
#include <mjast_formal.h>
#include <mjast_formallist.h>
#include <mjast_identifier.h>
#include <mjast_identifierexp.h>
#include <mjast_identifiertype.h>
#include <mjast_if.h>
#include <mjast_intarraytype.h>
#include <mjast_integerliteral.h>
#include <mjast_integertype.h>
#include <mjast_lessthan.h>
#include <mjast_mainclass.h>
#include <mjast_methoddecl.h>
#include <mjast_methoddecllist.h>
#include <mjast_minus.h>
#include <mjast_newarray.h>
#include <mjast_newobject.h>
#include <mjast_not.h>
#include <mjast_plus.h>
#include <mjast_print.h>
#include <mjast_program.h>
#include <mjast_statement.h>
#include <mjast_statementlist.h>
#include <mjast_this.h>
#include <mjast_times.h>
#include <mjast_true.h>
#include <mjast_type.h>
#include <mjast_vardecl.h>
#include <mjast_vardecllist.h>
#include <mjast_while.h>
#include <mjc_astdotprinter.h>

namespace mjc {

void AstDotPrinter::print(std::string &out, mjast::Program *prog) {
  out = "digraph MiniJavaProgram {\n";
  if (prog) {
    auto [_, data] = visit(*prog);
    out += std::move(data);
  }
  out += "}\n";
}

std::pair<std::string, std::string>
AstDotPrinter::visit(mjast::Program const &prog) {
  auto id = nextId();
  auto node = std::string("Program");
  auto name = fmt::format("{}_{}", node, id);
  std::string data;

  if (prog.main) {
    auto [x, y] = visit(*prog.main);
    data += fmt::format("{} -> {} [label=\"main\"];\n", name, x) + y;
  }
  if (prog.classes) {
    auto [x, y] = visit(*prog.classes);
    data += fmt::format("{} -> {} [label=\"classes\"];\n", name, x) + y;
  }
  data += fmt::format("{} [label=\"Node: {}\"];\n", name, node);
  return {std::move(name), std::move(data)};
}

std::pair<std::string, std::string>
AstDotPrinter::visit(mjast::ClassDeclList const &classes) {
  auto id = nextId();
  auto node = std::string("ClassDeclList");
  auto name = fmt::format("{}_{}", node, id);
  std::string data;

  for (auto const &cl : classes.list) {
    if (cl) {
      auto [x, y] = visit(*cl);
      data += fmt::format("{} -> {} [label=\"class\"];\n", name, x) + y;
    }
  }

  data += fmt::format("{} [label=\"Node: {}\"];\n", name, node);
  return {std::move(name), std::move(data)};
}

std::pair<std::string, std::string>
AstDotPrinter::visit(mjast::MainClass const &mainClass) {
  auto id = nextId();
  auto node = std::string("MainClass");
  auto name = fmt::format("{}_{}", node, id);
  std::string data;

  if (mainClass.className) {
    auto [x, y] = visit(*mainClass.className);
    data += fmt::format("{} -> {} [label=\"className\"];\n", name, x) + y;
  }
  if (mainClass.mainArgsParamName) {
    auto [x, y] = visit(*mainClass.mainArgsParamName);
    data +=
        fmt::format("{} -> {} [label=\"mainArgsParamName\"];\n", name, x) + y;
  }
  if (mainClass.stmt) {
    auto [x, y] = visit(*mainClass.stmt);
    data += fmt::format("{} -> {} [label=\"stmt\"];\n", name, x) + y;
  }

  data += fmt::format("{} [label=\"Node: {}\"];\n", name, node);
  return {std::move(name), std::move(data)};
}

std::pair<std::string, std::string>
AstDotPrinter::visit(mjast::ClassDecl const &classDeclaration) {
  auto id = nextId();
  std::string node;
  std::string name;
  std::string data;

  classDeclaration.match(
      [&](mjast::ClassDeclExtends const &cl) {
        node = std::string("ClassDeclExtends");
        name = fmt::format("{}_{}", node, id);

        if (cl.name) {
          auto [x, y] = visit(*cl.name);
          data += fmt::format("{} -> {} [label=\"name\"];\n", name, x) + y;
        }
        if (cl.parentName) {
          auto [x, y] = visit(*cl.parentName);
          data +=
              fmt::format("{} -> {} [label=\"parentName\"];\n", name, x) + y;
        }
        if (cl.vars) {
          auto [x, y] = visit(*cl.vars);
          data += fmt::format("{} -> {} [label=\"vars\"];\n", name, x) + y;
        }
        if (cl.methods) {
          auto [x, y] = visit(*cl.methods);
          data += fmt::format("{} -> {} [label=\"methods\"];\n", name, x) + y;
        }
      },
      [&](mjast::ClassDeclSimple const &cl) {
        node = std::string("ClassDeclSimple");
        name = fmt::format("{}_{}", node, id);

        if (cl.name) {
          auto [x, y] = visit(*cl.name);
          data += fmt::format("{} -> {};\n", name, x) + y;
        }
        if (cl.vars) {
          auto [x, y] = visit(*cl.vars);
          data += fmt::format("{} -> {} [label=\"vars\"];\n", name, x) + y;
        }
        if (cl.methods) {
          auto [x, y] = visit(*cl.methods);
          data += fmt::format("{} -> {} [label=\"methods\"];\n", name, x) + y;
        }
      });

  data += fmt::format("{} [label=\"Node: {}\"];\n", name, node);
  return {std::move(name), std::move(data)};
}

std::pair<std::string, std::string>
AstDotPrinter::visit(mjast::VarDeclList const &variables) {
  auto id = nextId();
  auto node = std::string("VarDeclList");
  auto name = fmt::format("{}_{}", node, id);
  std::string data;

  for (auto const &var : variables.varDecls) {
    if (var) {
      auto [x, y] = visit(*var);
      data += fmt::format("{} -> {} [label=\"var\"];\n", name, x) + y;
    }
  }

  data += fmt::format("{} [label=\"Node: {}\"];\n", name, node);
  return {std::move(name), std::move(data)};
}

std::pair<std::string, std::string>
AstDotPrinter::visit(mjast::MethodDeclList const &methods) {
  auto id = nextId();
  auto node = std::string("MethodDeclList");
  auto name = fmt::format("{}_{}", node, id);
  std::string data;

  for (auto const &meth : methods.methods) {
    if (meth) {
      auto [x, y] = visit(*meth);
      data += fmt::format("{} -> {} [label=\"method\"];\n", name, x) + y;
    }
  }

  data += fmt::format("{} [label=\"Node: {}\"];\n", name, node);
  return {std::move(name), std::move(data)};
}

std::pair<std::string, std::string>
AstDotPrinter::visit(mjast::VarDecl const &variableDeclaration) {
  auto id = nextId();
  auto node = std::string("VarDecl");
  auto name = fmt::format("{}_{}", node, id);
  std::string data;

  if (variableDeclaration.typ) {
    auto [x, y] = visit(*variableDeclaration.typ);
    data += fmt::format("{} -> {} [label=\"typ\"];\n", name, x) + y;
  }
  if (variableDeclaration.name) {
    auto [x, y] = visit(*variableDeclaration.name);
    data += fmt::format("{} -> {} [label=\"name\"];\n", name, x) + y;
  }

  data += fmt::format("{} [label=\"Node: {}\"];\n", name, node);
  return {std::move(name), std::move(data)};
}

std::pair<std::string, std::string>
AstDotPrinter::visit(mjast::MethodDecl const &methodDeclaration) {
  auto id = nextId();
  auto node = std::string("MethodDecl");
  auto name = fmt::format("{}_{}", node, id);
  std::string data;

  if (methodDeclaration.returnTyp) {
    auto [x, y] = visit(*methodDeclaration.returnTyp);
    data += fmt::format("{} -> {} [label=\"returnTyp\"];\n", name, x) + y;
  }
  if (methodDeclaration.name) {
    auto [x, y] = visit(*methodDeclaration.name);
    data += fmt::format("{} -> {} [label=\"name\"];\n", name, x) + y;
  }
  if (methodDeclaration.formals) {
    auto [x, y] = visit(*methodDeclaration.formals);
    data += fmt::format("{} -> {} [label=\"formals\"];\n", name, x) + y;
  }
  if (methodDeclaration.vars) {
    auto [x, y] = visit(*methodDeclaration.vars);
    data += fmt::format("{} -> {} [label=\"vars\"];\n", name, x) + y;
  }
  if (methodDeclaration.stmts) {
    auto [x, y] = visit(*methodDeclaration.stmts);
    data += fmt::format("{} -> {} [label=\"stmts\"];\n", name, x) + y;
  }
  if (methodDeclaration.returnValueExp) {
    auto [x, y] = visit(*methodDeclaration.returnValueExp);
    data += fmt::format("{} -> {} [label=\"returnValueExp\"];\n", name, x) + y;
  }

  data += fmt::format("{} [label=\"Node: {}\"];\n", name, node);
  return {std::move(name), std::move(data)};
}

std::pair<std::string, std::string>
AstDotPrinter::visit(mjast::FormalList const &formals) {
  auto id = nextId();
  auto node = std::string("FormalList");
  auto name = fmt::format("{}_{}", node, id);
  std::string data;

  for (auto const &formal : formals.formals) {
    if (formal) {
      auto [x, y] = visit(*formal);
      data += fmt::format("{} -> {} [label=\"formal\"];\n", name, x) + y;
    }
  }

  data += fmt::format("{} [label=\"Node: {}\"];\n", name, node);
  return {std::move(name), std::move(data)};
}

std::pair<std::string, std::string>
AstDotPrinter::visit(mjast::Formal const &formal) {
  auto id = nextId();
  auto node = std::string("Formal");
  auto name = fmt::format("{}_{}", node, id);
  std::string data;

  if (formal.typ) {
    auto [x, y] = visit(*formal.typ);
    data += fmt::format("{} -> {} [label=\"typ\"];\n", name, x) + y;
  }
  if (formal.name) {
    auto [x, y] = visit(*formal.name);
    data += fmt::format("{} -> {} [label=\"name\"];\n", name, x) + y;
  }

  data += fmt::format("{} [label=\"Node: {}\"];\n", name, node);
  return {std::move(name), std::move(data)};
}

std::pair<std::string, std::string>
AstDotPrinter::visit(mjast::Type const &typ) {
  auto id = nextId();
  std::string node;
  std::string name;
  std::string data;

  typ.match(
      [&](mjast::IntArrayType const &t) {
        node = std::string("IntArrayType");
        name = fmt::format("{}_{}", node, id);
      },
      [&](mjast::BooleanType const &t) {
        node = std::string("BooleanType");
        name = fmt::format("{}_{}", node, id);
      },
      [&](mjast::IntegerType const &t) {
        node = std::string("IntegerType");
        name = fmt::format("{}_{}", node, id);
      },
      [&](mjast::IdentifierType const &t) {
        node = std::string("IdentifierType");
        name = fmt::format("{}_{}", node, id);

        auto [x, y] = visit(t.name);
        data += fmt::format("{} -> {} [label=\"name\"];\n", name, x) + y;
      });

  data += fmt::format("{} [label=\"Node: {}\"];\n", name, node);
  return {std::move(name), std::move(data)};
}

std::pair<std::string, std::string>
AstDotPrinter::visit(mjast::StatementList const &statements) {
  auto id = nextId();
  auto node = std::string("StatementList");
  auto name = fmt::format("{}_{}", node, id);
  std::string data;

  for (auto const &stmt : statements.stmts) {
    if (stmt) {
      auto [x, y] = visit(*stmt);
      data += fmt::format("{} -> {} [label=\"stmt\"];\n", name, x) + y;
    }
  }

  data += fmt::format("{} [label=\"Node: {}\"];\n", name, node);
  return {std::move(name), std::move(data)};
}

std::pair<std::string, std::string>
AstDotPrinter::visit(mjast::Statement const &statement) {
  auto id = nextId();
  std::string node;
  std::string name;
  std::string data;

  statement.match(
      [&](mjast::Block const &s) {
        node = std::string("Block");
        name = fmt::format("{}_{}", node, id);

        if (s.stmts) {
          auto [x, y] = visit(*s.stmts);
          data += fmt::format("{} -> {} [label=\"stmts\"];\n", name, x) + y;
        }
      },
      [&](mjast::If const &s) {
        node = std::string("If");
        name = fmt::format("{}_{}", node, id);

        if (s.cond) {
          auto [x, y] = visit(*s.cond);
          data += fmt::format("{} -> {} [label=\"cond\"];\n", name, x) + y;
        }
        if (s.truePathStmt) {
          auto [x, y] = visit(*s.truePathStmt);
          data +=
              fmt::format("{} -> {} [label=\"truePathStmt\"];\n", name, x) + y;
        }
        if (s.falsePathStmt) {
          auto [x, y] = visit(*s.falsePathStmt);
          data +=
              fmt::format("{} -> {} [label=\"falsePathStmt\"];\n", name, x) + y;
        }
      },
      [&](mjast::While const &s) {
        node = std::string("While");
        name = fmt::format("{}_{}", node, id);

        if (s.cond) {
          auto [x, y] = visit(*s.cond);
          data += fmt::format("{} -> {} [label=\"cond\"];\n", name, x) + y;
        }
        if (s.loopStmt) {
          auto [x, y] = visit(*s.loopStmt);
          data += fmt::format("{} -> {} [label=\"loopStmt\"];\n", name, x) + y;
        }
      },
      [&](mjast::Print const &s) {
        node = std::string("Print");
        name = fmt::format("{}_{}", node, id);

        if (s.exp) {
          auto [x, y] = visit(*s.exp);
          data += fmt::format("{} -> {} [label=\"exp\"];\n", name, x) + y;
        }
      },
      [&](mjast::Assign const &s) {
        node = std::string("Assign");
        name = fmt::format("{}_{}", node, id);

        if (s.name) {
          auto [x, y] = visit(*s.name);
          data += fmt::format("{} -> {} [label=\"name\"];\n", name, x) + y;
        }
        if (s.valueExp) {
          auto [x, y] = visit(*s.valueExp);
          data += fmt::format("{} -> {} [label=\"valueExp\"];\n", name, x) + y;
        }
      },
      [&](mjast::ArrayAssign const &s) {
        node = std::string("ArrayAssign");
        name = fmt::format("{}_{}", node, id);

        if (s.name) {
          auto [x, y] = visit(*s.name);
          data += fmt::format("{} -> {} [label=\"name\"];\n", name, x) + y;
        }
        if (s.indexExp) {
          auto [x, y] = visit(*s.indexExp);
          data += fmt::format("{} -> {} [label=\"indexExp\"];\n", name, x) + y;
        }
        if (s.valueExp) {
          auto [x, y] = visit(*s.valueExp);
          data += fmt::format("{} -> {} [label=\"valueExp\"];\n", name, x) + y;
        }
      });

  data += fmt::format("{} [label=\"Node: {}\"];\n", name, node);
  return {std::move(name), std::move(data)};
}

std::pair<std::string, std::string>
AstDotPrinter::visit(mjast::Exp const &expression) {
  auto id = nextId();
  std::string node;
  std::string name;
  std::string data;

  expression.match(
      [&](mjast::And const &e) {
        node = std::string("And");
        name = fmt::format("{}_{}", node, id);

        if (e.e1) {
          auto [x, y] = visit(*e.e1);
          data += fmt::format("{} -> {} [label=\"e1\"];\n", name, x) + y;
        }
        if (e.e2) {
          auto [x, y] = visit(*e.e2);
          data += fmt::format("{} -> {} [label=\"e2\"];\n", name, x) + y;
        }
      },
      [&](mjast::LessThan const &e) {
        node = std::string("LessThan");
        name = fmt::format("{}_{}", node, id);

        if (e.e1) {
          auto [x, y] = visit(*e.e1);
          data += fmt::format("{} -> {} [label=\"e1\"];\n", name, x) + y;
        }
        if (e.e2) {
          auto [x, y] = visit(*e.e2);
          data += fmt::format("{} -> {} [label=\"e2\"];\n", name, x) + y;
        }
      },
      [&](mjast::Plus const &e) {
        node = std::string("Plus");
        name = fmt::format("{}_{}", node, id);

        if (e.e1) {
          auto [x, y] = visit(*e.e1);
          data += fmt::format("{} -> {} [label=\"e1\"];\n", name, x) + y;
        }
        if (e.e2) {
          auto [x, y] = visit(*e.e2);
          data += fmt::format("{} -> {} [label=\"e2\"];\n", name, x) + y;
        }
      },
      [&](mjast::Minus const &e) {
        node = std::string("Minus");
        name = fmt::format("{}_{}", node, id);

        if (e.e1) {
          auto [x, y] = visit(*e.e1);
          data += fmt::format("{} -> {} [label=\"e1\"];\n", name, x) + y;
        }
        if (e.e2) {
          auto [x, y] = visit(*e.e2);
          data += fmt::format("{} -> {} [label=\"e2\"];\n", name, x) + y;
        }
      },
      [&](mjast::Times const &e) {
        node = std::string("Times");
        name = fmt::format("{}_{}", node, id);

        if (e.e1) {
          auto [x, y] = visit(*e.e1);
          data += fmt::format("{} -> {} [label=\"e1\"];\n", name, x) + y;
        }
        if (e.e2) {
          auto [x, y] = visit(*e.e2);
          data += fmt::format("{} -> {} [label=\"e2\"];\n", name, x) + y;
        }
      },
      [&](mjast::ArrayLookup const &e) {
        node = std::string("ArrayLookup");
        name = fmt::format("{}_{}", node, id);

        if (e.objExp) {
          auto [x, y] = visit(*e.objExp);
          data += fmt::format("{} -> {} [label=\"objExp\"];\n", name, x) + y;
        }
        if (e.indexExp) {
          auto [x, y] = visit(*e.indexExp);
          data += fmt::format("{} -> {} [label=\"indexExp\"];\n", name, x) + y;
        }
      },
      [&](mjast::ArrayLength const &e) {
        node = std::string("ArrayLength");
        name = fmt::format("{}_{}", node, id);

        if (e.objExp) {
          auto [x, y] = visit(*e.objExp);
          data += fmt::format("{} -> {} [label=\"objExp\"];\n", name, x) + y;
        }
      },
      [&](mjast::Call const &e) {
        node = std::string("Call");
        name = fmt::format("{}_{}", node, id);

        if (e.obj) {
          auto [x, y] = visit(*e.obj);
          data += fmt::format("{} -> {} [label=\"obj\"];\n", name, x) + y;
        }
        if (e.methodName) {
          auto [x, y] = visit(*e.methodName);
          data +=
              fmt::format("{} -> {} [label=\"methodName\"];\n", name, x) + y;
        }
        if (e.args) {
          auto [x, y] = visit(*e.args);
          data += fmt::format("{} -> {} [label=\"args\"];\n", name, x) + y;
        }
      },
      [&](mjast::IntegerLiteral const &e) {
        node = std::string("IntegerLiteral");
        name = fmt::format("{}_{}", node, id);

        auto [x, y] = visit(e.value);
        data += fmt::format("{} -> {} [label=\"value\"];\n", name, x) + y;
      },
      [&](mjast::True const &e) {
        node = std::string("True");
        name = fmt::format("{}_{}", node, id);
      },
      [&](mjast::False const &e) {
        node = std::string("False");
        name = fmt::format("{}_{}", node, id);
      },
      [&](mjast::IdentifierExp const &e) {
        node = std::string("IdentifierExp");
        name = fmt::format("{}_{}", node, id);

        auto [x, y] = visit(e.name);
        data += fmt::format("{} -> {} [label=\"exp\"];\n", name, x) + y;
      },
      [&](mjast::This const &e) {
        node = std::string("This");
        name = fmt::format("{}_{}", node, id);
      },
      [&](mjast::NewArray const &e) {
        node = std::string("NewArray");
        name = fmt::format("{}_{}", node, id);

        if (e.sizeExp) {
          auto [x, y] = visit(*e.sizeExp);
          data += fmt::format("{} -> {} [label=\"sizeExp\"];\n", name, x) + y;
        }
      },
      [&](mjast::NewObject const &e) {
        node = std::string("NewObject");
        name = fmt::format("{}_{}", node, id);

        if (e.name) {
          auto [x, y] = visit(*e.name);
          data += fmt::format("{} -> {} [label=\"name\"];\n", name, x) + y;
        }
      },
      [&](mjast::Not const &e) {
        node = std::string("Not");
        name = fmt::format("{}_{}", node, id);

        if (e.exp) {
          auto [x, y] = visit(*e.exp);
          data += fmt::format("{} -> {} [label=\"exp\"];\n", name, x) + y;
        }
      });

  data += fmt::format("{} [label=\"Node: {}\"];\n", name, node);
  return {std::move(name), std::move(data)};
}

std::pair<std::string, std::string>
AstDotPrinter::visit(mjast::ExpList const &expressions) {
  auto id = nextId();
  auto node = std::string("ExpList");
  auto name = fmt::format("{}_{}", node, id);
  std::string data;

  for (auto const &exp : expressions.exps) {
    if (exp) {
      auto [x, y] = visit(*exp);
      data += fmt::format("{} -> {} [label=\"exp\"];\n", name, x) + y;
    }
  }

  data += fmt::format("{} [label=\"Node: {}\"];\n", name, node);
  return {std::move(name), std::move(data)};
}

std::pair<std::string, std::string>
AstDotPrinter::visit(mjast::Identifier const &identifier) {
  auto id = nextId();
  auto node = std::string("Identifier");
  auto name = fmt::format("{}_{}", node, id);
  std::string data;

  auto [x, y] = visit(identifier.name);
  data += fmt::format("{} -> {} [label=\"name\"];\n", name, x) + y;

  data += fmt::format("{} [label=\"Node: {}\"];\n", name, node);
  return {std::move(name), std::move(data)};
}
std::pair<std::string, std::string> AstDotPrinter::visit(std::string_view str) {
  auto id = nextId();
  auto node = std::string("string");
  auto name = fmt::format("{}_{}", node, id);
  std::string data;

  data += fmt::format("{} [label={}];\n", name, str);
  return {std::move(name), std::move(data)};
}

std::pair<std::string, std::string> AstDotPrinter::visit(int const &i) {
  auto id = nextId();
  auto node = std::string("string");
  auto name = fmt::format("{}_{}", node, id);
  std::string data;

  data += fmt::format("{} [label=\"{}\"];\n", name, i);
  return {std::move(name), std::move(data)};
}

int AstDotPrinter::nextId() { return d_id++; }

} // namespace mjc