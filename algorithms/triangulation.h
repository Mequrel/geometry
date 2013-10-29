#ifndef TRIANGULATION_H
#define TRIANGULATION_H

#include "../lib/core.h"
#include <vector>

namespace geo { namespace algo {

  bool is_y_monotonic(core::Polygon polygon);
  std::vector<core::Polygon> triangulate_y_monotonic(core::Polygon polygon);

}}

#endif