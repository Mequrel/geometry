#ifndef CORE_H
#define CORE_H

#include <algorithm>  // TODO: localize std::pair!

namespace geo { namespace core {

struct Point {
  double x;
  double y;
};

typedef std::pair<Point, Point> Vector;
typedef std::pair<Point, Point> Segment;
typedef std::pair<Segment, Segment> SegmentPair;
  

enum Orientation {
  LEFT, STRAIGHT, RIGHT
};

Orientation get_point_orientation(Vector, Point);

bool intersects(Segment a, Segment b);
bool contains(Segment segment, Point point);
bool is_between(Point first, Point asked, Point second);

double det(Point a, Point b, Point relative);

}}
#endif

