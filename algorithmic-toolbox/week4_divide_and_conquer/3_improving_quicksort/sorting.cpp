#include <iostream>
#include <vector>
#include <cstdlib>

using std::vector;
using std::swap;

int partition2(vector<int> &a, int l, int r) {
  int x = a[l];
  int j = l;
  for (int i = l + 1; i <= r; i++) {
    if (a[i] <= x) {
      j++;
      swap(a[i], a[j]);
    }
  }
  swap(a[l], a[j]);
  return j;
}

std::pair<int, int> partition3(vector<int> &a, int l, int r) {
  int m = partition2(a, l, r);
  swap(a[m], a[l]);
  int x = a[l];
  int i = l;
  for(int j = l + 1; j <= m; ++j) {
    if(a[j] < x) {
      ++i;
      swap(a[i], a[j]);
    }
  }

  swap(a[i], a[l]);
  return {i, m};

}

void randomized_quick_sort(vector<int> &a, int l, int r) {
  if (l >= r) {
    return;
  }

  int k = l + rand() % (r - l + 1);
  swap(a[l], a[k]);
  auto m = partition3(a, l, r);
  int m1 = m.first;
  int m2 = m.second;

  randomized_quick_sort(a, l, m1 - 1);
  randomized_quick_sort(a, m2 + 1, r);
}

int main() {
  int n;
  std::cin >> n;
  vector<int> a(n);
  for (size_t i = 0; i < a.size(); ++i) {
    std::cin >> a[i];
  }
  randomized_quick_sort(a, 0, a.size() - 1);
  for (size_t i = 0; i < a.size(); ++i) {
    std::cout << a[i] << ' ';
  }
}
