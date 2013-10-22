#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

struct Point {
  double x, y;

  bool friend operator==(const Point& a, const Point& b);
  bool friend operator!=(const Point& a, const Point& b);
};

bool operator==(const Point& a, const Point& b) {
  return a.x == b.x && a.y == b.y;
}

bool operator!=(const Point& a, const Point& b) {
  return !(a == b);
}

vector<Point> load_points() {
  int n;
  scanf("%d", &n);

  vector<Point> points;

  for(int i=0; i<n; ++i) {
    Point point;
    scanf("%lf %lf", &point.x, &point.y);

    points.push_back(point);
  }

  return points;
}

bool inline is_first(const Point& a, const Point& b) {
  return a.y < b.y || (a.y == b.y && a.x < b.x);
}

Point get_first(vector<Point>& points) {
  int current_first_index = 0;
  for (int i = 1; i < points.size(); ++i) {
    if(is_first(points[i], points[current_first_index])) {
      current_first_index = i;
    }
  }
  return points[current_first_index];
}

double inline det(Point x, Point y, Point z) {
  return (x.x - z.x) * (y.y - z.y) - (x.y - z.y) * (y.x - z.x);
}

double dist2(const Point& a, const Point& b) {
  return (b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y);
}

bool is_more_to_the_left_or_further(Point& asked, Point& more_to, Point& relative_to) {
  double det_value = det(relative_to, more_to, asked);
  return det_value > 0 || (det_value == 0.0 && dist2(relative_to, asked) > dist2(relative_to, more_to));
}

Point get_point_with_biggest_angle(vector<Point>& points, Point last_hull_point) {
  Point current_candidate = points[0];

  for(int i=1; i<points.size(); ++i) {
    Point& point = points[i];

    if(is_more_to_the_left_or_further(point, current_candidate, last_hull_point)) {
      current_candidate = point;
    } 
  }

  return current_candidate;
}

vector<Point> find_convex_hull_with_jarvis(vector<Point>& points) {
  Point first = get_first(points);
  
  vector<Point> convex_hull;
  convex_hull.push_back(first);
   
  do {
    Point point = get_point_with_biggest_angle(points,
                                               convex_hull.back());

    convex_hull.push_back(point);
  } while(convex_hull.back() != first);

  return convex_hull;
}

int main() {
  vector<Point> points = load_points();
  vector<Point> convex_hull = find_convex_hull_with_jarvis(points);

  for (int i = 0; i < convex_hull.size(); ++i) {
    printf("%lf %lf\n", convex_hull[i].x, convex_hull[i].y);
  }

  return 0;
}