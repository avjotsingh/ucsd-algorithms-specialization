#include <iostream>
#include <vector>
#include <chrono>

using namespace std::chrono;
using std::vector;

int optimal_weight(int W, const vector<int> &w) {
  //write your code here
  int dp[2][W + 1];
  for(int j = 0; j <= W; ++j)
    dp[0][j] = 0;
  for(int i = 0; i < w.size(); ++i) {
    for(int j = 0; j <= W; ++j) {
      dp[1][j] = dp[0][j];
      if(j >= w[i])
        dp[1][j] = std::max(dp[1][j], w[i] + dp[0][j - w[i]]);
    }
    for(int j = 0; j <= W; ++j)
      dp[0][j] = dp[1][j];
  }

  return dp[1][W];
}

void test_solution() {
  int W = 10000;
  int n = 100000;
  vector<int> w;
  for(int i = 0; i < n; ++i)
    w.push_back(rand() % 100000);
  auto start = high_resolution_clock::now();
  std::cout << optimal_weight(W, w) << std::endl;
  auto stop = high_resolution_clock::now();
  auto duration = duration_cast<milliseconds>(stop - start);
  std::cout << "Time taken : " << duration.count() << " ms" << std::endl;
  std::cout << "Tests passed" << std::endl;
}

int main() {
  //test_solution();
  int n, W;
  std::cin >> W >> n;
  vector<int> w(n);
  for (int i = 0; i < n; i++) {
    std::cin >> w[i];
  }
  std::cout << optimal_weight(W, w) << '\n';
}
