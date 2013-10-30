//#include "triangulation.h"
#include "../lib/core.h"
#include <algorithm>
#include <stack>
#include <vector>

using geo::core::Point;
using geo::core::Polygon;
using std::make_pair;
using std::pair;
using std::sort;
using std::stack;
using std::vector;

namespace geo { namespace algo {

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
  LEFT=1, RIGHT
};

struct higher_y_than_lower_x {
  bool operator()(const pair<Point, PolygonPart>& a, const pair<Point, PolygonPart>& b) {
    return a.first.y > b.first.y || (a.first.y == b.first.y && a.first.x < b.first.x);
  }
};


vector<pair<Point, PolygonPart> > divide_points_from_monotonic_polygon(const Polygon& polygon) {
  vector<pair<Point, PolygonPart> > result;

  int highest_y_point_index = find_highest_y_point_index(polygon);
  int current_index = highest_y_point_index;

  Point current_lowest = polygon[current_index];
  result.push_back(make_pair(current_lowest, LEFT));  
  current_index = (current_index+1) % polygon.size();
  Point next_point = polygon[current_index];   // iterate counterclockwise;

  while(is_below_or_same_y(next_point, current_lowest)) {
    current_lowest = next_point;
    result.push_back(make_pair(current_lowest, LEFT));
    current_index = (current_index+1) % polygon.size();
    next_point = polygon[current_index];
  }

  while(current_index != highest_y_point_index) {
    result.push_back(make_pair(polygon[current_index], RIGHT));
    current_index = (current_index+1) % polygon.size();
  }

  return result;
}

typedef pair<Point, PolygonPart> DividedPoint;

Polygon make_triange(Point a, Point b, Point c) {
  Polygon triangle;
  triangle.push_back(a);
  triangle.push_back(b);
  triangle.push_back(c);
  return triangle;
}

vector<Polygon> triangulate_y_monotonic(const Polygon& polygon) {
  vector<Polygon> triangles;

  vector<DividedPoint> points = divide_points_from_monotonic_polygon(polygon);
  sort(points.begin(), points.end(), higher_y_than_lower_x());

  stack<DividedPoint> points_stack;
  points_stack.push(points[0], points[1]);

  for(int i=3; i<points.size(); ++i) {
    DividedPoint& dpoint = points[i];


    DividedPoint top = points_stack.top();
    if (dpoint.second != top.second) {
      vector<pair<Point, Point> > pairs = get_pairs_from_stack(points_stack);
      for(int i=0; i<pairs.size(); ++i) {
        triangles.push_back(make_triangle(
            dpoint.first, pairs[i].first, pairs[i].second));
      }
      while(!points_stack.empty()) {
        points_stack.pop();
      }

      points_stack.push(top);
      points_stack.push(dpoint);
    }
    else {
      // test na to czy jest w wierzcholku
    }
  }


  Polygon res;
  for(int i=0; i<points.size(); ++i) {
    if(points[i].second == RIGHT) {
      points[i].first.y *= -1.0f;
    }

    res.push_back(points[i].first);
  }

  triangles.push_back(res);  

  return triangles;
}

}}

