#include <cstdio>
#include <algorithm>
#include <list>

using namespace std;

const int INF = 1000000000;

list<int> hull;

struct Point {
  double x, y;
};

struct POINT {
  double x, y;
  float f;
};

double inline abs(double x) {
  return (x < 0.0f) ? -x : x;
}

void f(POINT& p) {
  float d = static_cast<float>(abs(p.x) + abs(p.y));
  
  if(d == 0.0f) {
    p.f = -1.0f;
    return;
  }
  
  float y = static_cast<float>(p.y);
  float a = y / d;
  
  
  if(p.x >= 0) {
    if(p.y >= 0)
      p.f = a;
    else
      p.f = 4.0f - a;
  } else
    p.f = 2.0f - a;
}

bool inline cmp(POINT a, POINT b) {
  return (a.f < b.f) || (a.f == b.f && a.x > b.x);
}

double det(POINT a, POINT b, POINT c) {
  return = a.x*b.y + b.x*c.y + c.x*a.y - b.y*c.x - c.y*a.x - a.y*b.x;
}

int lbo() {
  int a = hull.back();
  hull.pop_back();
  int b = hull.back();
  hull.push_back(a);
  return b;
}

int main() {
  //----
  // pobieranie danych
  //----
  
  int n;
  scanf("%d", &n);
  
  POINT p[n];
    
  POINT first; first.x = INF; first.y = INF;
  
  printf("podaj wspolrzedne punktow:\n");
  for(int i=0; i<n; ++i) {
    scanf("%d %d", &p[i].x, &p[i].y);
    p[i].n = i+1;
    
    if(first.y > p[i].y) {
      first = p[i];
    } else if(first.y == p[i].y)
      if(first.x > p[i].x)
        first = p[i];
  }
  
  //-------
  // przestawianie wspolrzednych i obliczanie f
  //-------
  
  for(int i=0; i<n; ++i) {
    p[i].x -= first.x;
    p[i].y -= first.y;

    f(p[i]);
  }
  
  //-----
  // sortowanie
  //-----
  
  sort(p, p+n, cmp);
   
  //-----
  //Graham
  //-----
  hull.push_back(0);
  hull.push_back(1);
  hull.push_back(2);
  
  for(int i=3; i<n; ++i) {
    while(det(p[lbo()], p[hull.back()], p[i]) <= 0)
      hull.pop_back();
  
    hull.push_back(i);     
  }
  
  //-----
  // wynik
  //-----
  
  printf("otoczka:\n");
  for(list<int>::iterator it=hull.begin(); it!=hull.end(); ++it)
    printf("%d ", p[*it].n);
  
  return 0;
}
