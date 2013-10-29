#ifndef PRINT_H
#define PRINT_H

#include "core.h"
#include <string>
#include <vector>

namespace geo { namespace util {

std::string to_printable(const std::vector<geo::core::SegmentPair>);
std::string to_printable(const geo::core::SegmentPair);
std::string to_printable(const geo::core::Segment segment);
std::string to_printable(const geo::core::Point point);
std::string to_printable(const std::vector<geo::core::Polygon> polygons);
std::string to_printable(const geo::core::Polygon polygon);

}}

#endif