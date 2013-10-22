#ifndef BRUTAL_INTERSECTIONS
#define BRUTAL_INTERSECTIONS

#include "../lib/core.h"
#include <vector>

namespace geo { namespace algo {

std::vector<core::SegmentPair> get_intersections_brutally(std::vector<core::Segment> segments);

}}

#endif
