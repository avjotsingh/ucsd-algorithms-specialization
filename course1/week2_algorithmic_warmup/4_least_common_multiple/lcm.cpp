#include <iostream>
#include <cassert>

long long lcm_naive(int a, int b) {
  for (long l = 1; l <= (long long) a * b; ++l)
    if (l % a == 0 && l % b == 0)
      return l;

  return (long long) a * b;
}

long long lcm_fast(int a, int b) {
	if(a == 0 || b == 0)
		return 0L;

	long long result = 0;
	for(result = a; ; result += a) {
		if(result % b == 0)
			return result;
	}
}

void test_solution() {
	assert(lcm_fast(6, 8) == 24);
	assert(lcm_fast(761457, 614573) == 467970912861);

	int n_test = 1000;
	for(int i = 0; i < n_test; ++i) {
		int a = rand() % 100;
		int b = rand() % 100;
		assert(lcm_fast(a, b) == lcm_naive(a, b));
	}

	n_test = 5;
	for(int i = 0; i < n_test; ++i) {
		std::cout << i << '\n' << std::endl;
		int a = rand() % 10000000;
		int b = rand() % 10000000;
		assert(lcm_fast(a, b) == lcm_naive(a, b));
	}

	std::cout << "Tests passed..." << '\n' << std::endl;
}

int main() {
  int a, b;
  std::cin >> a >> b;
  //std::cout << lcm_naive(a, b) << std::endl;
  //test_solution();
  std::cout << lcm_fast(a, b) << std::endl;
  return 0;
}
