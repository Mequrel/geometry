#ifndef SHAMOS_HOEY_H
#define SHAMOS_HOEY_H

#include "../lib/core.h"
#include <vector>

namespace geo { namespace algo {

std::vector<core::SegmentPair> get_intersections_with_shamos_hoey(std::vector<core::Segment> segments);

}}

#endif