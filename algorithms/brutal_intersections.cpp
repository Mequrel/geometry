#include "brutal_intersections.h"

using namespace std;
using namespace geo;

vector<core::SegmentPair> algo::get_intersections_brutally(vector<core::Segment> segments) {
  vector<core::SegmentPair> result;

  for(int i=0; i<segments.size(); ++i) {
    for(int j=i+1; j<segments.size(); ++j) {
      // foreach pair of segments

      if(core::intersects(segments[i], segments[j])) {
        result.push_back(core::SegmentPair(segments[i], segments[j]));
      }
    }
  }
  
  return result;
}
