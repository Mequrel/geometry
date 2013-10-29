#include "print.h"
#include <cstdio>
#include <sstream>

using std::string;
using std::stringstream;
using std::vector;
using std::endl;
using namespace geo;

using geo::core::Polygon;

namespace geo { namespace util {

string to_printable(const vector<core::SegmentPair> segment_pairs) {
  string result = "";
  //foreach(core::SegmentPair& segment_pair : segment_pairs) {
  for(int i=0; i<segment_pairs.size(); ++i) {
    result += util::to_printable(segment_pairs[i]);
    result += "\n";
  }
  return result;
}

// TODO: use boost::format
string to_printable(const core::SegmentPair segment_pair) {
  char buffer[100];
  sprintf(buffer, "[%s] - [%s]",
          util::to_printable(segment_pair.first).c_str(),
          util::to_printable(segment_pair.second).c_str());
  return string(buffer);
}

string to_printable(const core::Segment segment) {
  char buffer[100];
  sprintf(buffer, "(%s) - (%s)",
          util::to_printable(segment.first).c_str(),
          util::to_printable(segment.second).c_str());

  return string(buffer);
}

string to_printable(const core::Point point) {
  char buffer[100];
  sprintf(buffer, "%lf %lf", point.x, point.y);
  return string(buffer);
}

string to_printable(const vector<Polygon> polygons) {
  stringstream result;

  result << polygons.size() << endl;
  // TODO(mequrel): change to foreach
  for(int i=0; i<polygons.size(); ++i) {
    result << util::to_printable(polygons[i]) << endl;
  }

  return result.str();
}

string to_printable(const Polygon polygon) {
  stringstream result;

  result << polygon.size() << endl;
  // TODO(mequrel): change to foreach
  for(int i=0; i<polygon.size(); ++i) {
    result << util::to_printable(polygon[i]) << endl;
  }

  return result.str();
}

}}