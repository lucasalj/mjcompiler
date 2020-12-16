#include <charconv>
#include <clipp.h>
#include <ctre.hpp>
#include <fmt/format.h>
#include <fstream>
#include <iostream>
#include <magic_enum.hpp>
#include <mjc_astdotprinter.h>
#include <mjc_parser.h>
#include <mjc_streamio.h>
#include <range/v3/action.hpp>
#include <sstream>
#include <string>
#include <string_view>
#include <vector>

class CLITokensLexer : public mjc::LexerProtocol {
public:
  ~CLITokensLexer() override = default;

  CLITokensLexer(std::vector<std::string> strs)
      : d_tokenStrings(std::move(strs)) {
    ranges::action::reverse(d_tokenStrings);
  }

  [[nodiscard]] mjc::Token nextToken() override {
    static constexpr auto pattern = ctll::fixed_string{
        "^Token\\(Token::Kind::([^,\\)]+)(?:,\\s*([^\\)]+))?\\)$"};
    if (d_tokenStrings.empty()) {
      std::cerr << "No more input tokens\n";
      d_success = false;
      return mjc::Token();
    }

    if (auto tokenStr = std::string_view(d_tokenStrings.back());
        auto m = ctre::match<pattern>(tokenStr)) {
      auto tokenKindStr = m.get<1>().to_view();
      auto tokenValStr = m.get<2>().to_view();
      d_tokenStrings.pop_back();
      ++d_lineNumber;
      auto tokKind = magic_enum::enum_cast<mjc::Token::Kind>(tokenKindStr);
      if (!tokKind.has_value()) {
        std::cerr << fmt::format("Token string ill formatted {}\n", tokenStr);
        d_success = false;
      }
      if (!tokenValStr.empty()) {
        int result;
        if (tokenValStr[0] == '"' &&
            tokenValStr[tokenValStr.size() - 1] == '"') {
          auto str = tokenValStr.substr();
          return mjc::Token(tokKind.value(),
                            std::string(str.begin(), str.end()));
        } else if (auto [p, ec] = std::from_chars(
                       tokenValStr.data(),
                       tokenValStr.data() + tokenValStr.size(), result);
                   ec == std::errc()) {
          return mjc::Token(tokKind.value(), result);
        } else {
          std::cerr << fmt::format("Token string ill formatted {}\n", tokenStr);
          d_success = false;
        }
      }
      return mjc::Token(tokKind.value());
    } else {
      std::cerr << fmt::format("Token string ill formatted {}\n", tokenStr);
      d_success = false;
    }
    return mjc::Token(mjc::Token::Kind::e_EOF);
  }

  bool success() const noexcept override { return d_success; }

  mjc::FilePosition currentPosition() const override {
    return {"stdin", d_lineNumber};
  }

private:
  bool d_success{true};
  std::size_t d_lineNumber{0};
  std::vector<std::string> d_tokenStrings;
};

int main(int argc, char *argv[]) {
  std::string inputFileName;
  bool help = false;
  bool dotfmt = false;

  auto cli =
      (clipp::option("-v", "--version")([] {
         std::cout << "mjcparser version 1.0\n\n";
         std::exit(0);
       }) % "Show version",
       clipp::option("-h", "--help").set(help) % "Show help menu",
       (clipp::option("-f", "--file") &
        clipp::value("input file", inputFileName)) %
           "Read from file",
       (clipp::required("-t", "--fmt") & (clipp::required("dot").set(dotfmt))) %
           "Output format");

  if (!clipp::parse(argc, argv, cli) || help) {
    std::cout << clipp::make_man_page(cli, argv[0])
                     .prepend_section("DESCRIPTION",
                                      "        A MiniJava parser.")
                     .append_section("LICENSE", "        MIT");
    return 1;
  }

  std::vector<std::string> tokenStrings;

  if (inputFileName.empty()) {

    for (std::string line; std::getline(std::cin, line);) {
      tokenStrings.push_back(std::move(line));
      line = std::string();
    }
  } else {
    std::string wholeText;
    try {

      std::ifstream inputFile(inputFileName);
      auto inputSize = mjc::StreamIO::streamSize(inputFile);
      wholeText.insert(0, inputSize, '\0');
      if (mjc::StreamIO::readCharacters(inputFile, wholeText.data(),
                                        inputSize) < inputSize) {

        std::cerr << fmt::format("Error while trying to read from file {}: "
                                 "unable to read the complete file\n",
                                 inputFileName);
        std::exit(1);
      }
    } catch (std::exception const &e) {

      std::cerr << fmt::format("Error while trying to read from file {}: {}\n",
                               inputFileName, e.what());
      std::exit(1);
    }

    std::istringstream in(wholeText);
    for (std::string line; std::getline(in, line);) {
      tokenStrings.push_back(std::move(line));
      line = std::string();
    }
  }

  auto parser = mjc::Parser{std::unique_ptr<mjc::LexerProtocol>(
      new CLITokensLexer{std::move(tokenStrings)})};

  auto ast = parser.parse();
  if (!parser.success()) {
    std::cerr << "Failed to parse input!\n";
  }

  if (dotfmt) {
    mjc::AstDotPrinter printer;
    std::string output;
    printer.print(output, ast.get());
    std::cout << output << "\n";
  }

  return 0;
}