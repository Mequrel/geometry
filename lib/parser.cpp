#include "parser.h"
#include <cstdio>

using std::vector;

namespace geo { namespace util {

vector<core::Segment> load_segments() {
  vector<core::Segment> segments;

  int segments_number;
  scanf("%d", &segments_number);

  for(int i=0; i<segments_number; ++i) {
    core::Point a, b;
    scanf("%lf %lf %lf %lf", &a.x, &a.y, &b.x, &b.y);

    segments.push_back(core::Segment(a, b));
  }
  
  return segments;
}

core::Polygon load_polygon() {
  core::Polygon polygon;

  int points_number;
  scanf("%d", &points_number);

  for(int i=0; i<points_number; ++i) {
    core::Point point;
    // TODO(mequrel): extract to function
    scanf("%lf %lf", &point.x, &point.y);

    polygon.push_back(point);
  }

  return polygon;
}

}}

