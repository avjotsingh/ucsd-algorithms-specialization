#include <iostream>
#include <cassert>

int gcd_naive(int a, int b) {
  int current_gcd = 1;
  for (int d = 2; d <= a && d <= b; d++) {
    if (a % d == 0 && b % d == 0) {
      if (d > current_gcd) {
        current_gcd = d;
      }
    }
  }
  return current_gcd;
}

int gcd(int a, int b) {
  if(a == 0)
    return b;
  return gcd(b%a, a);
}

void test_solution() {
  assert(gcd(10, 10) == 10);
  assert(gcd(5, 2) == 1);
  assert(gcd(47, 0) == 47);
  assert(gcd(0, 47) == 47);
  assert(gcd(18, 35) == 1);
  assert(gcd(28851538, 1183019) == 17657);

  int n_test = 100;
  for(int i = 0; i < n_test; ++i) {
    int a = rand() % 1000;
    int b = rand() % 1000;
    assert(gcd(a, b) == gcd_naive(a, b));
  }
}

int main() {
  int a, b;
  std::cin >> a >> b;
  //std::cout << gcd_naive(a, b) << std::endl;
  //test_solution();
  std::cout << gcd(a, b) << std::endl;  
  return 0;
}
