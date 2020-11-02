#include <string>
#include <iostream>
#include <vector>
#include <map>

using std::map;
using std::vector;
using std::string;

typedef map<char, int> edges;
typedef vector<edges> trie;

trie build_trie(vector<string> & patterns) {
  trie t;
  t.push_back(edges());
  for(auto pattern : patterns) {
    int current_node = 0;
    for(auto symbol : pattern) {
      if(t[current_node].find(symbol) != t[current_node].end()) {
        current_node = t[current_node][symbol];
      }
      else {
        t.push_back(edges());
        t[current_node][symbol] = t.size() - 1;
        current_node = t.size() - 1;
      }
    }
  }
  return t;
}

int main() {
  size_t n;
  std::cin >> n;
  vector<string> patterns;
  for (size_t i = 0; i < n; i++) {
    string s;
    std::cin >> s;
    patterns.push_back(s);
  }

  trie t = build_trie(patterns);
  for (size_t i = 0; i < t.size(); ++i) {
    for (const auto & j : t[i]) {
      std::cout << i << "->" << j.second << ":" << j.first << "\n";
    }
  }

  return 0;
}