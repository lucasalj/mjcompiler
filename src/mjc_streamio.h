#ifndef MJC_STREAMIO_INCLUDED
#define MJC_STREAMIO_INCLUDED

#include <istream>

namespace mjc {
struct StreamIO {
  static std::size_t streamSize(std::istream &in);
  static std::size_t readCharacters(std::istream &in, char *buffer,
                                    std::size_t nBytes);
};

} // namespace mjc

#endif // MJC_STREAMIO_INCLUDED