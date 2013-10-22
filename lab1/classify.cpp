#include <cstdio>
#include <ctime>
#include <string>
#include <vector>

#include "shewchuk.h"

using namespace std;

struct Point {
  double x, y;
};


std::vector<Point> points;

void LoadData() {
  int points_number;
  scanf("%d", &points_number);

  for (int i = 0; i < points_number; ++i) {
    Point point;
    scanf("%lf %lf", &point.x, &point.y);
    points.push_back(point);
  }
}

Point a, b;

enum RESULT {
  LEFT, STRAIGHT, RIGHT
};

std::string get_result_str(RESULT result) {
  if(result == LEFT) {
    return "1";
  }
  else if(result == STRAIGHT) {
    return "2";
  }
  else {
    return "3";
  }
}
enum TYPE {
  DET, S_FAST, S_EXACT, S_SLOW
};

double det(Point x, Point y, Point z) {
  return (x.x - z.x) * (y.y - z.y) - (x.y - z.y) * (y.x - z.x);
}

double* s_point(Point point) {
  double* s_repr = new double[2];
  s_repr[0] = point.x;
  s_repr[1] = point.y;
  return s_repr;
}

RESULT line_side(TYPE type, Point x, Point y, Point z) {
  double det_result;

  if(type == DET) {
    det_result = det(x, y, z);
  }
  else if (type == S_FAST) {
    det_result = orient2dfast(s_point(x), s_point(y), s_point(z));
  }
  else if (type == S_EXACT) {
    det_result = orient2dexact(s_point(x), s_point(y), s_point(z));
  }
  else {
    det_result = orient2dslow(s_point(x), s_point(y), s_point(z));
  }



  if(det_result > 0) {
    return LEFT;
  }
  else if(det_result < 0) {
    return RIGHT;
  }
  else {
    return STRAIGHT;
  }
}


void Classify(TYPE type) {
  int left = 0;
  int right = 0;
  int straight = 0;

  for (std::vector<Point>::iterator i = points.begin(); i != points.end(); ++i) {
    Point& point = *i;

    RESULT result = line_side(type, a, b, point);
    std::string result_str = get_result_str(result);

    if(result == LEFT) {
      left ++;
    }
    else if (result == STRAIGHT) {
      straight++;
    }
    else {
      right++;
    }

    //printf("%f %f %s\n", point.x, point.y, result_str.c_str());
  }  

  printf("\n\nleft: %d\nright: %d\nstraight: %d\n", left, right, straight);
}

int main(int argc, char** argv) {
  if (argc != 2) {
    printf("bad arguments\n");
    return 0;
  }

  TYPE type;
  if (std::string(argv[1]) == "slow") {
    type = S_SLOW;
  }
  else if (std::string(argv[1]) == "exact") {
    type = S_EXACT;
  }
  else if (std::string(argv[1]) == "fast") {
    type = S_FAST;
  }
  else if (std::string(argv[1]) == "dot") {
    type = DET;
  }
  else {
    printf("bad arguments\n");
    return 0;
  }

  LoadData();  

  a.x = -1.0;
  a.y = 0.0;
  b.x = 1.0;
  b.y = 0.1;

  clock_t begin = clock();

  Classify(type);

  clock_t end = clock();
  double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;

  printf("classification time in secs: %lf\n\n", elapsed_secs);


  return 0;
}