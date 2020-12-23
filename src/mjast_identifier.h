#ifndef MJAST_IDENTIFIER_INCLUDED
#define MJAST_IDENTIFIER_INCLUDED

#include <mjc_stringtable.h>

namespace mjast {

struct Identifier {
  mjc::StringIndex name;
};

} // namespace mjast

#endif // MJAST_IDENTIFIER_INCLUDED