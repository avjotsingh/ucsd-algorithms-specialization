#include <iostream>
#include <vector>

using std::vector;

long long get_number_of_inversions(vector<int> &a, size_t left, size_t right) {
  long long number_of_inversions = 0;
  if (right <= left + 1) return number_of_inversions;
  size_t ave = left + (right - left) / 2;
  number_of_inversions += get_number_of_inversions(a, left, ave);
  number_of_inversions += get_number_of_inversions(a, ave, right);
  //write your code here
  vector<int> temp(right - left);
  size_t i = left, j = ave, k = 0;
  while(i < ave && j < right) {
    if(a[i] <= a[j])
      temp[k++] = a[i++];
    else {
      number_of_inversions += ave - i;
      temp[k++] = a[j++];
    }
  }
  while(i < ave)
    temp[k++] = a[i++];
  while(j < right)
    temp[k++] = a[j++];

  for(k = 0; k < temp.size(); ++k) {
    a[left + k] = temp[k];
  }

  return number_of_inversions;
}

int main() {
  int n;
  std::cin >> n;
  vector<int> a(n);
  for (size_t i = 0; i < a.size(); i++) {
    std::cin >> a[i];
  }
  std::cout << get_number_of_inversions(a, 0, a.size()) << '\n';
}
