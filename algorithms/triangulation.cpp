//#include "triangulation.h"
#include "../lib/core.h"
#include "../lib/print.h"
#include <iostream>
#include <algorithm>
#include <stack>
#include <vector>

using geo::core::get_point_orientation;
using geo::core::Orientation;
using geo::core::Point;
using geo::core::Polygon;
using geo::core::Vector;
using std::make_pair;
using std::pair;
using std::sort;
using std::stack;
using std::vector;

namespace geo { namespace algo {

const bool DEBUG = true;

void debug(std::string str) {
  if(DEBUG) {
    std::cout << str << std::endl;
  }
}

// assumption: points.size() > 0
int find_highest_y_point_index(const vector<Point>& points) {
  int best_index = 0;
  // TODO(mequrel): replace with boost or stdlib with cpp11 lambdas
  for(int i=1; i<points.size(); ++i) {
    if(points[best_index].y < points[i].y) {
      best_index = i;
    }
  }
  return best_index;
}

bool inline are_monotonic_paths_crossed(int left_count, int right_count, int polygon_size) {
  return (left_count + right_count) >= polygon_size;
}

bool inline is_below_or_same_y(Point asked, Point relative) {
  return asked.y <= relative.y;
}

// assumption: polygon is closed and have at least three edges!
int get_counterclockwise_monotonic_edges_count(const Polygon& polygon, int start_point_index) {
  int edges_count = 0;
  Point current_lowest = polygon[start_point_index];;
  Point next_point = polygon[(start_point_index+edges_count+1) % polygon.size()];   // iterate counterclockwise;

  while(is_below_or_same_y(next_point, current_lowest)) {
    edges_count++;
    current_lowest = next_point;
    next_point = polygon[(start_point_index+edges_count+1) % polygon.size()];   // iterate counterclockwise
  }
  
  return edges_count;
}

int get_clockwise_monotonic_edges_count(const Polygon& polygon, int start_point_index) {
  int edges_count = 0;
  Point current_lowest = polygon[start_point_index];;
  Point next_point = polygon[(start_point_index + polygon.size() - edges_count - 1) % polygon.size()]; // iterate clockwise;

  while(is_below_or_same_y(next_point, current_lowest)) {
    edges_count++;
    current_lowest = next_point;
    next_point = polygon[(start_point_index + polygon.size() - edges_count - 1) % polygon.size()]; // iterate clockwise
  }
  
  return edges_count;
}


bool is_y_monotonic(const Polygon& polygon) {
  int highest_y_point_index = find_highest_y_point_index(polygon);

  int left_count = get_counterclockwise_monotonic_edges_count(polygon, highest_y_point_index);
  int right_count = get_clockwise_monotonic_edges_count(polygon, highest_y_point_index);

  return are_monotonic_paths_crossed(left_count, right_count, polygon.size());
}

enum PolygonPart {
  SIDE_LEFT=1, SIDE_RIGHT
};

struct higher_y_than_lower_x {
  bool operator()(const pair<Point, PolygonPart>& a, const pair<Point, PolygonPart>& b) {
    return a.first.y > b.first.y || (a.first.y == b.first.y && a.first.x < b.first.x);
  }
};


pair<vector<Point>, vector<Point> > divide_points_from_monotonic_polygon(const Polygon& polygon) {
  vector<Point> left_side, right_side;

  int highest_y_point_index = find_highest_y_point_index(polygon);
  int current_index = highest_y_point_index;

  Point current_lowest = polygon[current_index];
  left_side.push_back(current_lowest);  
  current_index = (current_index+1) % polygon.size();
  Point next_point = polygon[current_index];   // iterate counterclockwise;

  while(is_below_or_same_y(next_point, current_lowest)) {
    current_lowest = next_point;
    left_side.push_back(current_lowest);
    current_index = (current_index+1) % polygon.size();
    next_point = polygon[current_index];
  }

  int last_left_point = (current_index - 1 + polygon.size()) % polygon.size();
  current_index = (highest_y_point_index - 1 + polygon.size()) % polygon.size();

  while(current_index != last_left_point) {
    right_side.push_back(polygon[current_index]);
    current_index = (current_index - 1 + polygon.size()) % polygon.size();
  }

  return make_pair(left_side, right_side);
}

Polygon make_triangle(Point a, Point b, Point c) {
  Polygon triangle;
  triangle.push_back(a);
  triangle.push_back(b);
  triangle.push_back(c);
  return triangle;
}

bool inline is_inside(const Polygon& triangle, PolygonPart side) {
  Orientation orientation = get_point_orientation(Vector(triangle[0], triangle[1]), triangle[2]);
  return (side == SIDE_LEFT && orientation == geo::core::RIGHT)
      || (side == SIDE_RIGHT && orientation == geo::core::LEFT);
}

typedef pair<Point, PolygonPart> DividedPoint;
typedef vector<DividedPoint> DividedSegmentStack;

vector<pair<Point, Point> > get_pairs_from_stack(const DividedSegmentStack& points_stack) {
  vector<pair<Point, Point> > pairs;

  for(int i=points_stack.size()-1; i>=1; --i) {
    pairs.push_back(make_pair(points_stack[i-1].first, points_stack[i].first));
  }

  return pairs;
}

vector<Polygon> triangulate_y_monotonic(const Polygon& polygon) {
  vector<Polygon> triangles;

  pair<vector<Point>, vector<Point> > division = divide_points_from_monotonic_polygon(polygon);
  vector<Point>& left_side = division.first;
  vector<Point>& right_side = division.second;

  //debug(geo::util::to_printable(right_side[0]));

  vector<DividedPoint> left_side_annotated;
  for(int i=0; i<left_side.size(); ++i) {
    left_side_annotated.push_back(make_pair(left_side[i], SIDE_LEFT));
  }
  vector<DividedPoint> right_side_annotated;
  for(int i=0; i<right_side.size(); ++i) {
    right_side_annotated.push_back(make_pair(right_side[i], SIDE_RIGHT));
  }

  vector<DividedPoint> points;
  points.resize(left_side_annotated.size() + right_side_annotated.size());
  std::merge(left_side_annotated.begin(), left_side_annotated.end(),
            right_side_annotated.begin(), right_side_annotated.end(),
            points.begin(), higher_y_than_lower_x());


  DividedSegmentStack points_stack;
  points_stack.push_back(points[0]);
  points_stack.push_back(points[1]);

  for(int i=2; i<points.size(); ++i) {
    DividedPoint& dpoint = points[i];

    DividedPoint top = points_stack.back();
    if (dpoint.second != top.second) {
      vector<pair<Point, Point> > pairs = get_pairs_from_stack(points_stack);
      for(int i=0; i<pairs.size(); ++i) {
        triangles.push_back(make_triangle(
            dpoint.first, pairs[i].first, pairs[i].second));
      }
      while(!points_stack.empty()) {
        points_stack.pop_back();
      }

      points_stack.push_back(top);
      points_stack.push_back(dpoint);
    }
    else {
      vector<pair<Point, Point>> pairs = get_pairs_from_stack(points_stack);
      DividedPoint last_popped = points_stack.back();
      points_stack.pop_back();
      for(int i=0; i<pairs.size(); ++i) {

        Polygon triangle = make_triangle(dpoint.first, pairs[i].first, pairs[i].second);
        if(!is_inside(triangle, dpoint.second)) {
          break;
        }
        
        triangles.push_back(triangle);
        last_popped = points_stack.back();
        points_stack.pop_back();
      }

      points_stack.push_back(last_popped);

      points_stack.push_back(dpoint);
    }
  }

   
  return triangles;
}



enum MonotonicClassification {
  START = 1, END, SPLIT, MERGE, REGULAR
};

int get_next_index(int current_index, int size) {
  return (current_index + 1) % size;
}

int get_prev_index(int current_index, int size) {
  return (current_index - 1 + size) % size;
}

bool inline below_y(Point asked, Point relative_to) {
  return asked.y < relative_to.y;
}

bool inline above_y(Point asked, Point relative_to) {
  return asked.y > relative_to.y;
}

MonotonicClassification classify_point(Point point, Point prev, Point next) {

  if(below_y(point, prev) && below_y(point, next)) {
    if(core::get_point_orientation(Vector(prev, point), next) == core::LEFT) {
      return END;
    }
    else {
      return SPLIT;
    }
  }
  else if(above_y(point, prev) && above_y(point, next)) {
    if(core::get_point_orientation(Vector(prev, point), next) == core::LEFT) {
      return START;
    }
    else {
      return MERGE;
    }
  }
  else {
    return REGULAR;
  }
}

// assumption n > 2
vector<pair<Point, geo::algo::MonotonicClassification> >classify_y_monotonic(Polygon polygon) {
  vector<pair<Point, geo::algo::MonotonicClassification> > classified_points;

  for(int i=0; i<polygon.size(); ++i) {
    Point point = polygon[i];

    Point prev = polygon[get_prev_index(i, polygon.size())];
    Point next = polygon[get_next_index(i, polygon.size())];

    MonotonicClassification result = classify_point(point, prev, next);
    classified_points.push_back(make_pair(point, result));
  }

  return classified_points;
}






}}

