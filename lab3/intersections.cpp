#include "lib/parser.h"
#include "lib/print.h"
#include "algorithms/shamos_hoey.h"
#include "algorithms/brutal_intersections.h"
#include <iostream>

using namespace std;
using namespace geo;

int main(int argc, char const *argv[]) {
  try {
    vector<core::Segment> segments = util::load_segments();

    vector<core::SegmentPair> intersections = algo::get_intersections_with_shamos_hoey(segments);
    //vector<core::SegmentPair> intersections = algo::get_intersections_brutally(segments);

    cout << "Found intersections:" << endl;
    cout << util::to_printable(intersections);

    return 0;
  }
  catch(...) {
  //catch(util::PrimitivesParserError& e) {
    cout << "Error encountered during input parsing.";
    return 0;
  }
}