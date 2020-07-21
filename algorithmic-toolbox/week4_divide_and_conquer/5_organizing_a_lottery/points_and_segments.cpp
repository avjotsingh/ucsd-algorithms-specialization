#include <iostream>
#include <vector>
#include <algorithm>
using std::vector;

struct segment {
    int start;
    int end;
};

size_t find_start_greater_than(vector<int> &starts, int point) {
  size_t low = 0, high = starts.size();
  while(low < high) {
    auto mid = low + (high - low) / 2;
    if(starts[mid] <= point)
      low = mid + 1;
    else
      high = mid;
  }

  return low;
}

size_t find_end_less_than(vector<int> &ends, int point) {
  size_t low = 0, high = ends.size();
  while(low < high) {
    auto mid = low + (high - low) / 2;
    if(ends[mid] >= point)
      low = mid + 1;
    else
      high = mid;
  }

  return low;
}

vector<int> fast_count_segments(vector<int> starts, vector<int> ends, vector<int> points) {
  vector<int> cnt(points.size());
  //write your code here
  sort(starts.begin(), starts.end());
  sort(ends.begin(), ends.end(), std::greater<int>());

  for(size_t i = 0; i < points.size(); ++i) {
    int m = find_start_greater_than(starts, points[i]);
    m = starts.size() - m;
    int n = find_end_less_than(ends, points[i]);
    n = ends.size() - n;
    cnt[i] = starts.size() - m - n;
  }
  return cnt;
}

vector<int> naive_count_segments(vector<int> starts, vector<int> ends, vector<int> points) {
  vector<int> cnt(points.size());
  for (size_t i = 0; i < points.size(); i++) {
    for (size_t j = 0; j < starts.size(); j++) {
      cnt[i] += starts[j] <= points[i] && points[i] <= ends[j];
    }
  }
  return cnt;
}

int main() {
  int n, m;
  std::cin >> n >> m;
  vector<int> starts(n), ends(n);
  for (size_t i = 0; i < starts.size(); i++) {
    std::cin >> starts[i] >> ends[i];
  }
  vector<int> points(m);
  for (size_t i = 0; i < points.size(); i++) {
    std::cin >> points[i];
  }
  //use fast_count_segments
  vector<int> cnt = fast_count_segments(starts, ends, points);
  for (size_t i = 0; i < cnt.size(); i++) {
    std::cout << cnt[i] << ' ';
  }
}
