#ifndef PARSER_H
#define PARSER_H

#include "core.h"
#include <vector>

namespace geo { namespace util {

  std::vector<core::Segment> load_segments();
  core::Polygon load_polygon();

// class PrimitivesParser {
// public:
//   virtual ~PrimitivesParser() {}
//   virtual std::vector<geo::core::Segment> get_segments() = 0;
//   virtual void parse() = 0;
// };

  // class PrimitivesParserError {};

// class StdInPrimitivesParser { //: public PrimitivesParser {
//   std::vector<core::Segment> segments;
// public:
//   std::vector<core::Segment> get_segments() {
//     return segments;
//   }
//   void parse() {
//     segments.clear();

//     int segments_number;
//     scanf("%d", &segments_number);

//     for(int i=0; i<segments_number; ++i) {
//       core::Point a, b;
//       scanf("%lf %lf %lf %lf", &a.x, &a.y, &b.x, &b.y);

//       segments.push_back(core::Segment(a, b));
//     }
//   }
// };

}}

#endif