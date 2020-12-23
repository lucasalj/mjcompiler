#ifndef MJAST_IDENTIFIEREXP_INCLUDED
#define MJAST_IDENTIFIEREXP_INCLUDED

#include <mjc_stringtable.h>

namespace mjast {

struct IdentifierExp {
  mjc::StringIndex name;
};

} // namespace mjast

#endif // MJAST_IDENTIFIEREXP_INCLUDED