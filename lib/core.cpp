#include "core.h"

using namespace std;
using namespace geo;

bool core::intersects(Segment a, Segment b) {
  return ((core::get_point_orientation(Vector(a), b.first)
          != core::get_point_orientation(Vector(a), b.second))
          &&
          (core::get_point_orientation(Vector(b), a.first)
          != core::get_point_orientation(Vector(b), a.second))) 

          ||
          // both colinear
          (core::get_point_orientation(Vector(a), b.first) == STRAIGHT
           && core::get_point_orientation(Vector(a), b.second) == STRAIGHT
           && (core::contains(a, b.first) || core::contains(a, b.second)));
}

core::Orientation core::get_point_orientation(Vector vec, Point point) {
  double det_value = core::det(vec.first, vec.second, point);

  if(det_value < 0) {
    return LEFT;
  }
  else if(det_value) {
    return RIGHT;
  }
  else {
    return STRAIGHT;
  }
}

bool core::contains(Segment segment, Point point) {
  return core::get_point_orientation(Vector(segment), point) == STRAIGHT && 
         core::is_between(segment.first, point, segment.second);
}

double core::det(Point a, Point b, Point relative) {
  return (a.x - relative.x) * (b.y - relative.y) - (a.y - relative.y) * (b.x - relative.x);
}

bool core::is_between(Point first, Point asked, Point second) {
  bool is_between_x = (first.x < asked.x && asked.x < second.x)
                      || (second.x < asked.x && asked.x < first.x);

  bool is_between_y = (first.y < asked.y && asked.y < second.y)
                      || (second.y < asked.y && asked.y < first.y);

  return is_between_x && is_between_y;
}