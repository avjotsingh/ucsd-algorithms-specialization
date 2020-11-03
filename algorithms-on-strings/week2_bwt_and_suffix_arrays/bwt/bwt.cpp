#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <chrono>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;

string BWT(const string& text) {
  string result = "";
  int n = text.size();
  vector<string> bw_matrix;
  for(int i = n - 1; i >= 0; --i) {
  	string suffix = text.substr(i, n - i);
  	string prefix = text.substr(0, i);
  	bw_matrix.push_back(suffix + prefix);
  }

  sort(bw_matrix.begin(), bw_matrix.end());
  for(int i = 0; i < n; ++i) {
  	result += bw_matrix[i][n - 1];
  }
  return result;
}

void test_solution() {
	string test_string = "";
	char letters[] = {'A', 'C', 'G', 'T'};
	for(int i = 0; i < 1000; ++i) {
		int rand_idx = rand() % 4;
		test_string += letters[rand_idx];
	}
	auto start = std::chrono::high_resolution_clock::now();
	auto result = BWT(test_string);
	auto end = std::chrono::high_resolution_clock::now();
	auto time_taken = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
	cout << "Time taken: " << time_taken.count() << " ms" << endl;
}

int main() {
  //test_solution();
  string text;
  cin >> text;
  cout << BWT(text) << endl;
  return 0;
}