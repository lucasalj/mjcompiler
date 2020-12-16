#include <clipp.h>
#include <iostream>
#include <mjc_lexer.h>
#include <string>

void outputTokens(mjc::LexerProtocol *lex) {
  for (auto exit = false; !exit;) {
    auto currToken = lex->nextToken();
    if (currToken.kind() == mjc::Token::Kind::e_EOF) {
      exit = true;
    }
    std::cout << currToken << "\n";
  }
}

int main(int argc, char *argv[]) {
  std::string inputFileName;
  bool help = false;

  auto cli = (clipp::option("-v", "--version")([] {
                std::cout << "mjclexer version 1.0\n\n";
                std::exit(0);
              }) % "Show version",
              clipp::option("-h", "--help").set(help) % "Show help menu",
              (clipp::option("-f", "--file") &
               clipp::value("input file", inputFileName)) %
                  "Read from file");

  if (!clipp::parse(argc, argv, cli) || help) {
    std::cout << clipp::make_man_page(cli, argv[0])
                     .prepend_section("DESCRIPTION",
                                      "        A MiniJava lexer.")
                     .append_section("LICENSE", "        MIT");
    return 1;
  }

  if (inputFileName.empty()) {
    if (std::string text; std::getline(std::cin, text, '\0')) {

      auto in = std::unique_ptr<std::istream>(
          std::make_unique<std::istringstream>(text));
      auto lexer = mjc::Lexer::create(std::move(in), "std::cin");

      outputTokens(&lexer);
    }
  } else {
    auto lexer = mjc::Lexer::create(inputFileName);
    if (!lexer) {
      std::cerr << "Internal error!\n";
      return 1;
    }
    outputTokens(&*lexer);
  }

  return 0;
}