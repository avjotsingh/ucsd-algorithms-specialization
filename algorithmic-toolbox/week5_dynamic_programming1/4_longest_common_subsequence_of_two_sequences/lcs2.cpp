#include <iostream>
#include <vector>

using std::vector;

int lcs2(vector<int> &a, vector<int> &b) {
  //write your code here
  int dp[a.size()][b.size()];
  for(int i = 0; i < a.size(); ++i) {
    for(int j = 0; j < b.size(); ++j) {
      dp[i][j] = 0;
      auto v1 = (i > 0) ? dp[i - 1][j] : 0;
      auto v2 = (j > 0) ? dp[i][j - 1] : 0;
      auto v3 = (i > 0 && j > 0) ? dp[i - 1][j - 1] : 0;
      if(a[i] == b[j] && v3 >= 0)
        ++v3;
      else if(a[i] == b[j])
        v3 = 1;

      dp[i][j] = std::max(dp[i][j], v1);
      dp[i][j] = std::max(dp[i][j], v2);
      dp[i][j] = std::max(dp[i][j], v3);
    }
  }

  return dp[a.size() - 1][b.size() - 1];
}

int main() {
  size_t n;
  std::cin >> n;
  vector<int> a(n);
  for (size_t i = 0; i < n; i++) {
    std::cin >> a[i];
  }

  size_t m;
  std::cin >> m;
  vector<int> b(m);
  for (size_t i = 0; i < m; i++) {
    std::cin >> b[i];
  }

  std::cout << lcs2(a, b) << std::endl;
}
