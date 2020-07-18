#include <iostream>
#include <vector>
#include <chrono>
using namespace std::chrono;
using std::vector;

bool is_possible(vector<int> &A, int n, int a, int b, int c) {
	if(n == 0 && a == 0 && b == 0 && c == 0)
		return true;
	else if(n <= 0 && (a > 0 || b > 0 || c > 0))
		return false;
	else if(a < 0 || b < 0 || c < 0)
		return false;
	else {
		return is_possible(A, n - 1, a - A[n - 1], b, c) ||
			is_possible(A, n - 1, a, b - A[n - 1], c) ||
			is_possible(A, n - 1, a, b, c - A[n - 1]);
	}
}

int partition3(vector<int> &A) {
	int sum = 0;
	for(auto elem : A)
		sum += elem;
	if(A.size() < 3 || sum % 3 != 0)
		return 0;

	return is_possible(A, A.size(), sum / 3, sum / 3, sum / 3);
}

void test_solution() {
	int n = 20;
	vector<int> A;
	for(int i = 0; i < n; ++i)
		A.push_back(rand() % 31);
	auto start = high_resolution_clock::now();
	if(partition3(A))
		std::cout << "Partition possible\n";
	else
		std::cout << "Partition not possible\n";
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start);
	std::cout << "Time taken " << duration.count() << " ms\n";
	std::cout << "Test passed" << std::endl;
}

int main() {
	//test_solution();
  int n;
  std::cin >> n;
  vector<int> A(n);
  for (size_t i = 0; i < A.size(); ++i) {
    std::cin >> A[i];
  }
  std::cout << partition3(A) << '\n';
}
