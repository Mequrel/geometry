#include "print.h"
#include <cstdio>

using namespace std;
using namespace geo;

string util::to_printable(const vector<core::SegmentPair> segment_pairs) {
  string result = "";
  //foreach(core::SegmentPair& segment_pair : segment_pairs) {
  for(int i=0; i<segment_pairs.size(); ++i) {
    result += util::to_printable(segment_pairs[i]);
    result += "\n";
  }
  return result;
}

// TODO: use boost::format
string util::to_printable(const core::SegmentPair segment_pair) {
  char buffer[100];
  sprintf(buffer, "[%s] - [%s]",
          util::to_printable(segment_pair.first).c_str(),
          util::to_printable(segment_pair.second).c_str());
  return string(buffer);
}

string util::to_printable(const core::Segment segment) {
  char buffer[100];
  sprintf(buffer, "(%s) - (%s)",
          util::to_printable(segment.first).c_str(),
          util::to_printable(segment.second).c_str());

  return string(buffer);
}

string util::to_printable(const core::Point point) {
  char buffer[100];
  sprintf(buffer, "%lf %lf", point.x, point.y);
  return string(buffer);
}