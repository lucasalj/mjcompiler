#include <catch.hpp>
#include <mjc_stringtable.h>
#include <string_view>

TEST_CASE("", "[stringtable]") {
  using namespace std::literals;
  mjc::StringTable table;
  auto testStr1 = "test1"sv;
  auto testStr2 = "test2"sv;
  auto testStr3 = "test3"sv;
  auto testStr4 = "test4"sv;
  auto id1 = table.insert(testStr1);
  auto id2 = table.insert(testStr2);
  auto id3 = table.insert(testStr3);
  auto id4 = table.insert(testStr4);
  REQUIRE(id1.str() == testStr1);
  REQUIRE(id2.str() == testStr2);
  REQUIRE(id3.str() == testStr3);
  REQUIRE(id4.str() == testStr4);
}