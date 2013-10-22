#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

struct Point {
  double x, y;
};

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
  return a.y > b.y || (a.y == b.y && a.x > b.x);
}

Point extract_first(vector<Point>& points) {
  int current_first_index = 0;
  for (int i = 1; i < points.size(); ++i) {
    if(is_first(points[i], points[current_first_index])) {
      current_first_index = i;
    }
  }
  Point first = points[current_first_index];
  swap(points[current_first_index], points[points.size()-1]);
  points.pop_back();
  return first;
}

double inline det(Point x, Point y, Point z) {
  return (x.x - z.x) * (y.y - z.y) - (x.y - z.y) * (y.x - z.x);
}

class angle_relative_to {
  Point relative_point;

public:
  angle_relative_to(Point& _relative_point) : relative_point(_relative_point) {}

  bool operator()(const Point& a, const Point& b) {
    return det(relative_point, a, b) < 0;
  }
};

bool is_not_left_turn(Point& a, Point& b, Point& c) {
  return det(a, b, c) <= 0;
}

bool is_not_valid_convex_hull_with(vector<Point>& convex_hull, Point new_point) {
  int hull_length = convex_hull.size();
  return (hull_length > 1) && is_not_left_turn(new_point,
                                               convex_hull[hull_length-1],
                                               convex_hull[hull_length-2]);
}

vector<Point> find_convex_hull_with_graham(vector<Point>& points) {
  Point first = extract_first(points);
  
  sort(points.begin(), points.end(), angle_relative_to(first));

  vector<Point> convex_hull;
  convex_hull.push_back(first);

  for(int i=0; i<points.size(); ++i) {
    while(is_not_valid_convex_hull_with(convex_hull, points[i])) {
      convex_hull.pop_back();
    }
    convex_hull.push_back(points[i]);
  }
  return convex_hull;
}

int main() {
  vector<Point> points = load_points();
  vector<Point> convex_hull = find_convex_hull_with_graham(points);

  for (int i = 0; i < convex_hull.size(); ++i) {
    printf("%lf %lf\n", convex_hull[i].x, convex_hull[i].y);
  }
  printf("%lf %lf\n", convex_hull[0].x, convex_hull[0].y);

  return 0;
}