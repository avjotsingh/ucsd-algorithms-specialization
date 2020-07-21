#include <iostream>
#include <vector>

using std::vector;

vector<int> optimal_summands(int n) {
  vector<int> summands;
  //write your code here
  while(n > 0) {
    int count = summands.size();
    if(n >= count + 1) {
      summands.push_back(count + 1);
      n -= count + 1;
    }
    else {
      summands[count - 1] += n;
      n = 0;
    }
  }
  return summands;
}

int main() {
  int n;
  std::cin >> n;
  vector<int> summands = optimal_summands(n);
  std::cout << summands.size() << '\n';
  for (size_t i = 0; i < summands.size(); ++i) {
    std::cout << summands[i] << ' ';
  }
}
