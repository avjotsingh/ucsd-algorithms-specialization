#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>
using std::vector;

double get_optimal_value(int capacity, vector<int> weights, vector<int> values) {
  double value = 0.0;

  // write your code here
  int n = weights.size();
  vector<std::pair<double, int>> items(n);
  for(int i = 0; i < values.size(); ++i)
    items[i] = { values[i]/(double)weights[i], weights[i] };
  sort(items.begin(), items.end(), [](std::pair<double, int> p1, std::pair<double, int> p2) { return p1.first > p2. first; });

  int i = 0;
  while(capacity > 0 && i < n) {
    int a = std::min(capacity, items[i].second);
    value += (double) a * items[i].first;
    items[i].second -= a;
    capacity -= a;
    if(items[i].second == 0)
      ++i;
  }

  return value;
}

int main() {
  int n;
  int capacity;
  std::cin >> n >> capacity;
  vector<int> values(n);
  vector<int> weights(n);
  for (int i = 0; i < n; i++) {
    std::cin >> values[i] >> weights[i];
  }

  double optimal_value = get_optimal_value(capacity, weights, values);

  std::cout.precision(10);
  std::cout << optimal_value << std::endl;
  return 0;
}
