#include <iostream>
#include <cassert>
#include <string>
#include <vector>
#include <climits>

using std::vector;
using std::string;
using std::max;
using std::min;

#define inf 1000000000

long long eval(long long a, long long b, char op) {
  if (op == '*') {
    return a * b;
  } else if (op == '+') {
    return a + b;
  } else if (op == '-') {
    return a - b;
  } else {
    assert(0);
  }
}

long long get_maximum_value(const string &exp) {
  //write your code here
  int size = (exp.size() + 1) / 2;
  long long m[size][size];
  long long M[size][size];

  for(int s = 0; s < size; ++s) {
    for(int i = 0; i < size - s; ++i) {
      m[i][i + s] = inf;
      M[i][i + s] = -inf;
      if(s == 0)
        m[i][i + s] = M[i][i + s] = exp[2*i] - '0';
      else {
        for(int k = i; k < i + s; ++k) {
          char op = exp[2*k + 1];
          auto v1 = eval(m[i][k], m[k + 1][i + s], op);
          auto v2 = eval(M[i][k], M[k + 1][i + s], op);
          auto v3 = eval(m[i][k], M[k + 1][i + s], op);
          auto v4 = eval(M[i][k], m[k + 1][i + s], op);

          m[i][i + s] = std::min(m[i][i + s], v1);
          m[i][i + s] = std::min(m[i][i + s], v2);
          m[i][i + s] = std::min(m[i][i + s], v3);
          m[i][i + s] = std::min(m[i][i + s], v4);
          
          M[i][i + s] = std::max(M[i][i + s], v1);
          M[i][i + s] = std::max(M[i][i + s], v2);
          M[i][i + s] = std::max(M[i][i + s], v3);
          M[i][i + s] = std::max(M[i][i + s], v4);
        }
      }
    }
  }

  return M[0][size - 1];
}

int main() {
  string s;
  std::cin >> s;
  std::cout << get_maximum_value(s) << '\n';
}
