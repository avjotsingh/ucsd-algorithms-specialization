#include <algorithm>
#include <iostream>
#include <climits>
#include <vector>

using std::vector;

struct Segment {
  int start, end;
};

vector<int> optimal_points(vector<Segment> &segments) {
  vector<int> points;
  //write your code here

  sort(segments.begin(), segments.end(), [](const Segment s1, const Segment s2) { return s1.start < s2.start; });
  int intersection[2] = {segments[0].start, segments[0].end};
  for (size_t i = 1; i < segments.size(); ++i) {
    if(intersection[1] < segments[i].start) {
      points.push_back(intersection[1]);
      intersection[0] = segments[i].start;
      intersection[1] = segments[i].end;
    }
    else {
      intersection[0] = std::max(intersection[0], segments[i].start);
      intersection[1] = std::min(intersection[1], segments[i].end);
    }
  }

  points.push_back(intersection[1]);
  return points;
}

int main() {
  int n;
  std::cin >> n;
  vector<Segment> segments(n);
  for (size_t i = 0; i < segments.size(); ++i) {
    std::cin >> segments[i].start >> segments[i].end;
  }
  vector<int> points = optimal_points(segments);
  std::cout << points.size() << "\n";
  for (size_t i = 0; i < points.size(); ++i) {
    std::cout << points[i] << " ";
  }
}
