#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;

vector<int> optimal_sequence_greedy(int n) {
  std::vector<int> sequence;
  while (n >= 1) {
    sequence.push_back(n);
    if (n % 3 == 0) {
      n /= 3;
    } else if (n % 2 == 0) {
      n /= 2;
    } else {
      n = n - 1;
    }
  }
  reverse(sequence.begin(), sequence.end());
  return sequence;
}

vector<int> optimal_sequence(int n) {
  int dp[n + 1];
  dp[1] = 0;
  for(int i = 2; i <= n; ++i) {
    dp[i] = dp[i - 1] + 1;
    if(i % 3 == 0)
      dp[i] = std::min(dp[i], dp[i / 3] + 1);
    if(i % 2 == 0)
      dp[i] = std::min(dp[i], dp[i / 2] + 1);
  }

  vector<int> sequence;
  while(n >= 1) {
    sequence.push_back(n);
    if(n % 3 == 0 && dp[n] == 1 + dp[n / 3])
      n /= 3;
    else if(n % 2 == 0 && dp[n] == 1 + dp[n / 2])
      n /= 2;
    else
      n -= 1;
  }

  reverse(sequence.begin(), sequence.end());
  return sequence;
}

int main() {
  int n;
  std::cin >> n;
  vector<int> sequence = optimal_sequence(n);
  std::cout << sequence.size() - 1 << std::endl;
  for (size_t i = 0; i < sequence.size(); ++i) {
    std::cout << sequence[i] << " ";
  }
}
