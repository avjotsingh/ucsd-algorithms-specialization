#include <iostream>
#include <string>
#include <climits>

using std::string;

#define inf 1000000

int edit_distance(const string &str1, const string &str2) {
  	//write your code here
	int dp[str1.size() + 1][str2.size() + 1];
	for(int i = 0; i <= str1.size(); ++i) {
		for(int j = 0; j <= str2.size(); ++j) {
			dp[i][j] = inf;
			if(i == 0)
				dp[i][j] = j;
			else if(j == 0)
				dp[i][j] = i;
			else {
				auto v1 = (i > 0) ? dp[i - 1][j] + 1: inf;
				auto v2 = (j > 0) ? dp[i][j - 1] + 1: inf;
				auto v3 = (i > 0 && j > 0) ? dp[i - 1][j - 1] + 1: inf;
				if(str1[i - 1] == str2[j - 1])
					v3 -= 1;

				dp[i][j] = std::min(dp[i][j], v1);
				dp[i][j] = std::min(dp[i][j], v2);
				dp[i][j] = std::min(dp[i][j], v3);
			}
		}
	}

	return dp[str1.size()][str2.size()];
}

int main() {
  string str1;
  string str2;
  std::cin >> str1 >> str2;
  std::cout << edit_distance(str1, str2) << std::endl;
  return 0;
}
