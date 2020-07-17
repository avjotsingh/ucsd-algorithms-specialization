#include <iostream>
#include <vector>
#include <climits>

using std::vector;

int lcs3(vector<int> &a, vector<int> &b, vector<int> &c) {
  //write your code here
  int dp[a.size()][b.size()][c.size()];

  for(int i = 0; i < a.size(); ++i) {
    for(int j = 0; j < b.size(); ++j) {
      for(int k = 0; k < c.size(); ++k) {
        dp[i][j][k] = 0;
        auto v1 = (i > 0) ? dp[i - 1][j][k] : 0;
        auto v2 = (j > 0) ? dp[i][j - 1][k] : 0;
        auto v3 = (k > 0) ? dp[i][j][k - 1] : 0;
        auto v4 = (i > 0 && j > 0) ? dp[i - 1][j - 1][k] : 0;
        auto v5 = (j > 0 && k > 0) ? dp[i][j - 1][k - 1] : 0;
        auto v6 = (i > 0 && k > 0) ? dp[i - 1][j][k - 1] : 0;
        auto v7 = (i > 0 && j > 0 && k > 0) ? dp[i - 1][j - 1][k - 1] : 0;
        if(a[i] == b[j] && a[i] == c[k] && b[j] == c[k])
          v7 += 1;

        dp[i][j][k] = std::max(dp[i][j][k], v1);
        dp[i][j][k] = std::max(dp[i][j][k], v2);
        dp[i][j][k] = std::max(dp[i][j][k], v3);
        dp[i][j][k] = std::max(dp[i][j][k], v4);
        dp[i][j][k] = std::max(dp[i][j][k], v5);
        dp[i][j][k] = std::max(dp[i][j][k], v6);
        dp[i][j][k] = std::max(dp[i][j][k], v7);
      }
    }
  }
  return dp[a.size() - 1][b.size() - 1][c.size() - 1];
}

int main() {
  size_t an;
  std::cin >> an;
  vector<int> a(an);
  for (size_t i = 0; i < an; i++) {
    std::cin >> a[i];
  }
  size_t bn;
  std::cin >> bn;
  vector<int> b(bn);
  for (size_t i = 0; i < bn; i++) {
    std::cin >> b[i];
  }
  size_t cn;
  std::cin >> cn;
  vector<int> c(cn);
  for (size_t i = 0; i < cn; i++) {
    std::cin >> c[i];
  }
  std::cout << lcs3(a, b, c) << std::endl;
}
