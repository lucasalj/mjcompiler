#ifndef MJC_STRINGTABLE_INCLUDED
#define MJC_STRINGTABLE_INCLUDED

#include <absl/container/flat_hash_map.h>
#include <string>
#include <string_view>
#include <vector>

namespace mjc {

class StringTable;

class StringIndex {
public:
  StringIndex(std::size_t idx, StringTable *table) noexcept;
  std::string_view str() const;
  operator std::string_view() const;

  friend bool operator==(StringIndex const &a, StringIndex const &b) noexcept;
  friend bool operator!=(StringIndex const &a, StringIndex const &b) noexcept;

private:
  std::size_t d_index{0};
  StringTable *d_table_p{nullptr};
};

class StringTable {
public:
  StringIndex insert(std::string_view str);

private:
  absl::flat_hash_map<std::string_view, std::size_t> d_indexes;
  std::vector<std::string> d_storage;

  friend class StringIndex;
};

inline StringIndex::StringIndex(std::size_t idx, StringTable *table) noexcept
    : d_index{idx}, d_table_p{table} {}

inline std::string_view StringIndex::str() const {
  return d_table_p->d_storage[d_index];
}

inline StringIndex::operator std::string_view() const { return str(); }

inline bool operator==(StringIndex const &a, StringIndex const &b) noexcept {
  return a.d_index == b.d_index && a.d_table_p == b.d_table_p;
}

inline bool operator!=(StringIndex const &a, StringIndex const &b) noexcept {
  return !(a == b);
}

inline StringIndex StringTable::insert(std::string_view str) {
  auto [it, inserted] = d_indexes.emplace(str, d_storage.size());
  if (inserted) {
    d_storage.push_back(std::string(str));
  }
  return {it->second, this};
}

} // namespace mjc

#endif // MJC_STRINGTABLE_INCLUDED