#include <iostream>
#include <vector>

using std::vector;

int get_majority_element(vector<int> &a, int left, int right) {
  if (left == right) return -1;
  if (left + 1 == right) return a[left];
  //write your code here
  int n = right - left;
  int mid = left + n / 2;
  int a1 = get_majority_element(a, left, mid);
  int a2 = get_majority_element(a, mid, right);

  int cnt_a1 = 0, cnt_a2 = 0;
  for(int i = left; i < right; ++i) {
    if(a[i] == a1)
      ++cnt_a1;
    else if(a[i] == a2)
      ++cnt_a2;
  }

  //std::cout << "left : " << left << " right: " << right << " a1: " << a1 << " a2: " << a2 << " cnt_a1: " << cnt_a1 << " cnt_a2: " << cnt_a2 << std::endl;
  if(cnt_a1 > n/2 && cnt_a1 >= cnt_a2)
    return a1;
  else if(cnt_a2 > n/2 && cnt_a2 > cnt_a1)
    return a2;
  else
    return -1;
}

int main() {
  int n;
  std::cin >> n;
  vector<int> a(n);
  for (size_t i = 0; i < a.size(); ++i) {
    std::cin >> a[i];
  }
  std::cout << (get_majority_element(a, 0, a.size()) != -1) << '\n';
}
