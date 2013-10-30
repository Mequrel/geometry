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

    if(!algo::is_y_monotonic(polygon)) {
      cout << "Polygon is not y monotonic. Cannot triangulate." << endl;
      return 0;
    }

    vector<core::Polygon> triangles = algo::triangulate_y_monotonic(polygon);
    cout << util::to_printable(triangles);
    return 0;
  }
  catch(...) {
  //catch(util::PrimitivesParserError& e) {
    cout << "Error encountered during input parsing.";
    return 0;
  }
}