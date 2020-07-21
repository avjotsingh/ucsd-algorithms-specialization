#include <algorithm>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <string>
#include <cmath>
#include <chrono>

using namespace std::chrono;

using std::vector;
using std::string;
using std::pair;
using std::min;

#define inf 1.0E+10

struct point {
  int x;
  int y;
};

double closest_points(vector<point> &px, vector<point> &py, size_t start, size_t end) {
  if(start + 1 == end)
    return inf;

  //split the plane into two regions and recurse
  auto mid = start + (end - start) / 2;
  double d1 = closest_points(px, py, start, mid);
  double d2 = closest_points(px, py, mid, end);
  double d = min(d1, d2);

  // vector<point> strip;
  // for(auto p : py) {
  //   if(p.x >= px[mid].x - d && p.x <= px[mid].x + d)
  //     strip.push_back(p);
  // }

  vector<point> strip;
  for(size_t i = start; i < end; ++i) {
    if(px[i].x >= px[mid].x - d && px[i].x <= px[mid].x + d)
      strip.push_back(px[i]);
  }
  sort(strip.begin(), strip.end(), [](point p1, point p2) { return p1.y < p2.y; });

  for(size_t i = 0; i < strip.size(); ++i) {
    for(size_t j = i + 1; j < strip.size() && j - i <= 7; ++j) {
      double dist = sqrt(pow(strip[i].x - strip[j].x, 2) + pow(strip[i].y - strip[j].y, 2));
      d = min(d, dist);
    }
  }

  return d;
}

double minimal_distance(vector<int> x, vector<int> y) {
  //write your code here
  vector<struct point> pvec_x;
  vector<struct point> pvec_y;
  for(int i = 0; i < x.size(); ++i) {
    pvec_x.push_back({x[i], y[i]});
    pvec_y.push_back({x[i], y[i]});
  }

  sort(pvec_x.begin(), pvec_x.end(), [](point p1, point p2) { return p1.x < p2.x; });
  sort(pvec_y.begin(), pvec_y.end(), [](point p1, point p2) { return p1.y < p2.y; });
  return closest_points(pvec_x, pvec_y, 0, pvec_x.size());
}

void test_solution() {
  size_t n = rand()%100000 + 2;
  vector<int> x(n);
  vector<int> y(n);
  for(size_t i = 0; i < n; ++i) {
    x.push_back(rand()%2000000000 - 1000000000);
    y.push_back(rand()%2000000000 - 1000000000);
  }

  auto start = high_resolution_clock::now();
  std::cout << std::fixed;
  std::cout << "started..." << std::endl;
  std::cout << std::setprecision(9) << minimal_distance(x, y) << std::endl;

  auto stop = high_resolution_clock::now();
  auto duration = duration_cast<milliseconds>(stop - start);

  std::cout << "Time taken: " << duration.count() << " ms" << std::endl;
}

int main() {
  //test_solution();
  size_t n;
  std::cin >> n;
  vector<int> x(n);
  vector<int> y(n);
  for (size_t i = 0; i < n; i++) {
    std::cin >> x[i] >> y[i];
  }
  std::cout << std::fixed;
  std::cout << std::setprecision(9) << minimal_distance(x, y) << "\n";
}
