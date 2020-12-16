#ifndef MJC_FILEPOSITION_INCLUDED
#define MJC_FILEPOSITION_INCLUDED

#include <string>

namespace mjc {

struct FilePosition {
  std::string fileName;
  std::size_t lineNumber;
};

} // namespace mjc

#endif // MJC_FILEPOSITION_INCLUDED
