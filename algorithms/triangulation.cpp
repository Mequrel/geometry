//#include "triangulation.h"
#include "../lib/core.h"
#include <algorithm>
#include <vector>

using std::vector;
using std::sort;
using geo::core::Point;
using geo::core::Polygon;

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

struct higher_y_than_lower_x {
  bool operator()(const Point& a, const Point& b) {
    return a.y > b.y || (a.y == b.y && a.x < b.x);
  }
};

vector<Polygon> triangulate_y_monotonic(const Polygon& polygon) {
  vector<Polygon> triangles;

  vector<Point> polygon_points(polygon);
  sort(polygon_points.begin(), polygon_points.end(), higher_y_than_lower_x());

  triangles.push_back(polygon_points);  

  return triangles;
}

}}

