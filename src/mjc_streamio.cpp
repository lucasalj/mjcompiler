#include <mjc_streamio.h>

namespace mjc {

std::size_t StreamIO::streamSize(std::istream &in) {
  in.seekg(0, std::ios_base::end);
  std::size_t size = in.tellg();
  in.seekg(0, std::ios_base::beg);
  return size;
}

std::size_t StreamIO::readCharacters(std::istream &in, char *buffer,
                                     std::size_t nBytes) {
  in.read(buffer, nBytes);
  return in.gcount();
}

} // namespace mjc