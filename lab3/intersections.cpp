#include "lib/parser.h"
#include "lib/print.h"
#include "algorithms/shamos_hoey.h"
#include "algorithms/brutal_intersections.h"
#include <iostream>
#include <string>

using namespace std;
using namespace geo;

enum AlgorithmType { 
  BRUTE, SHAMOS_HOEY
};

bool parseArguments(int argc, char const *argv[], AlgorithmType& algorith_type) {
  if(argc != 2) {
    return false;
  }

  if(string(argv[1]) == "brute") {
    algorith_type = BRUTE;
    return true;
  }
  
  if(string(argv[1]) == "SH") {
    algorith_type = SHAMOS_HOEY;
    return true;
  }

  return false;
}

int main(int argc, char const *argv[]) {
  AlgorithmType algorith_type;
  if(!parseArguments(argc, argv, algorith_type)) {
    cout << "Not valid arguments" << endl;
    return 0;
  }

  try {
    vector<core::Segment> segments = util::load_segments();

    vector<core::SegmentPair> intersections;

    if(algorith_type == BRUTE) {
      intersections = algo::get_intersections_brutally(segments);
    }
    else if(algorith_type == SHAMOS_HOEY) {
      intersections = algo::get_intersections_with_shamos_hoey(segments); 
    }

    cout << intersections.size() << endl;

    for(int i=0; i<intersections.size(); ++i) {
      core::SegmentPair& segments = intersections[i];
      core::Point intersection_point = core::get_intersection(
            segments.first, segments.second);

      cout << util::to_printable(segments) << " " 
           << util::to_printable(intersection_point) << endl;
    }
    //cout << util::to_printable(intersections);

    return 0;
  }
  catch(...) {
  //catch(util::PrimitivesParserError& e) {
    cout << "Error encountered during input parsing.";
    return 0;
  }
}