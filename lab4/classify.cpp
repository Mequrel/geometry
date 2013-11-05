#include "../lib/parser.h"
#include "../lib/print.h"
//#include "../algorithms/triangulation.h"
#include "../algorithms/triangulation.cpp"
#include <iostream>

using namespace std;
using namespace geo;

int main(int argc, char const *argv[]) {
  try {
    core::Polygon polygon = util::load_polygon();

    vector<pair<Point, geo::algo::MonotonicClassification> > classified_points
       = algo::classify_y_monotonic(polygon);

    for(int i=0; i<classified_points.size(); ++i) {
      cout << util::to_printable(classified_points[i].first) << " " << classified_points[i].second << endl;
    }
    return 0;
  }
  catch(...) {
  //catch(util::PrimitivesParserError& e) {
    cout << "Error encountered during input parsing.";
    return 0;
  }
}