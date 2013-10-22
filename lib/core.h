#ifndef CORE_H
#define CORE_H

#include <algorithm>  // TODO: localize std::pair!

namespace geo { namespace core {

struct Point {
  double x;
  double y;

  Point() : x(0), y(0) {}
  Point(double _x, double _y) : x(_x), y(_y) {}
  friend Point operator+(const Point& a, const Point& b);
  friend Point operator-(const Point& a, const Point& b);
  friend Point operator*(double scalar, const Point& vec);
  friend bool operator==(const Point& a, const Point& b);
  friend bool operator!=(const Point& a, const Point& b);
};

Point operator+(const Point& a, const Point& b);
Point operator-(const Point& a, const Point& b);
Point operator*(double scalar, const Point& vec);
bool operator==(const Point& a, const Point& b);
bool operator!=(const Point& a, const Point& b);

typedef std::pair<Point, Point> Vector;
typedef std::pair<Point, Point> Segment;
typedef std::pair<Segment, Segment> SegmentPair;
  

enum Orientation {
  LEFT, STRAIGHT, RIGHT
};

Orientation get_point_orientation(Vector, Point);

bool intersects(Segment a, Segment b);
Point get_intersection(Segment a, Segment b);
bool contains(Segment segment, Point point);
bool is_between(Point first, Point asked, Point second);

double det(Point a, Point b);
double det3(Point a, Point b, Point relative);

}}
#endif

