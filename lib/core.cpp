#include "core.h"

using namespace std;
using namespace geo;

// TODO: distinction between Point and Vector
// Introduce epsilon!

bool inline is_in_range(double asked, double lower_bound, double higher_bound) {
  return (lower_bound <= asked) && (asked <= higher_bound);
}

// uses idea from http://stackoverflow.com/questions/563198/how-do-you-detect-where-two-line-segments-intersect
// variables named in the same manner
bool core::intersects(Segment a, Segment b) {
  Point p = a.first;
  Point q = b.first;
  Point r = a.second - a.first;
  Point s = b.second - b.first;

  double det_rs = det(r, s);
  if(det_rs == 0.0f) {
    // parallel
    if(det((q - p), r) == 0.0f) {
      // colinear
      return core::is_between(a.first, b.first, a.second)
             || core::is_between(a.first, b.second, a.second);
    }
    return false;
  }

  double t = det((q - p), s) / det_rs;
  double u = det((q - p), r) / det_rs;

  return is_in_range(t, 0.0f, 1.0f) && is_in_range(u, 0.0f, 1.0f);
}

// uses idea from http://stackoverflow.com/questions/563198/how-do-you-detect-where-two-line-segments-intersect
// variables named in the same manner
core::Point core::get_intersection(Segment a, Segment b) {
  Point p = a.first;
  Point q = b.first;
  Point r = a.second - a.first;
  Point s = b.second - b.first;

  double det_rs = det(r, s);
  double t = det((q - p), s) / det_rs;
  double u = det((q - p), r) / det_rs;

  return p + t * r;
}

core::Orientation core::get_point_orientation(Vector vec, Point point) {
  double det_value = core::det3(vec.first, vec.second, point);

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

double core::det(Point a, Point b) {
  return a.x * b.y - a.y * b.x;
}

double core::det3(Point a, Point b, Point relative) {
  return det(a - relative, b - relative);
}

bool core::is_between(Point first, Point asked, Point second) {
  bool is_between_x = is_in_range(asked.x, first.x, second.x)
                      || is_in_range(asked.x, second.x, first.x);

  bool is_between_y = is_in_range(asked.y, first.y, second.y)
                      || is_in_range(asked.y, second.y, first.y);

  return is_between_x && is_between_y;
}

core::Point core::operator+(const Point& a, const Point& b) {
  return Point(a.x + b.x, a.y + b.y);
}

core::Point core::operator-(const Point& a, const Point& b) {
  return Point(a.x - b.x, a.y - b.y);
}

core::Point core::operator*(double scalar, const Point& vec) {
  return Point(scalar * vec.x, scalar * vec.y);
}

bool core::operator==(const Point& a, const Point& b) {
  return a.x == b.x && a.y == b.y;
}

bool core::operator!=(const Point& a, const Point& b) {
  return !(a == b);
}
