#include <algorithm>
#include <iostream>
#include <vector>
#include <cassert>

using std::vector;

long long max_dot_product_naive(vector<int> a, vector<int> b) {
  int n = a.size();
  long long revenue = 0;
  for(int i = 0; i < n; ++i) {
    //pick the ad with the highest revenue per click & slot with highest clicks
    auto max_revenue_iter = a.begin();
    auto max_clicks_iter = b.begin();

    for(auto iter_a = a.begin(), iter_b = b.begin(); iter_a < a.end() && iter_b < b.begin(); ++iter_a, ++iter_b) {
      if(*iter_a > *max_revenue_iter)
        max_revenue_iter = iter_a;
      if(*iter_b > *max_clicks_iter)
        max_clicks_iter = iter_b;
    }

    revenue += (*max_revenue_iter) * (*max_clicks_iter);
    a.erase(max_revenue_iter);
    b.erase(max_clicks_iter);
  }

  return revenue;
}

long long max_dot_product(vector<int> a, vector<int> b) {
  // write your code here
  long long result = 0;
  sort(a.begin(), a.end());
  sort(b.begin(), b.end());

  for (size_t i = 0; i < a.size(); i++) {
    result += ((long long) a[i]) * b[i];
  }
  return result;
}

int main() {
  size_t n;
  std::cin >> n;
  vector<int> a(n), b(n);
  for (size_t i = 0; i < n; i++) {
    std::cin >> a[i];
  }
  for (size_t i = 0; i < n; i++) {
    std::cin >> b[i];
  }
  std::cout << max_dot_product(a, b) << std::endl;
}
