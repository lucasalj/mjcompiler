#ifndef MJAST_NEWOBJECT_INCLUDED
#define MJAST_NEWOBJECT_INCLUDED

#include <memory>

namespace mjast {

struct Identifier;

struct NewObject {
  std::unique_ptr<Identifier> name;
};

} // namespace mjast

#endif // MJAST_NEWOBJECT_INCLUDED