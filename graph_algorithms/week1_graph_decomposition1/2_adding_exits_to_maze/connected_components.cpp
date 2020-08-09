#include <iostream>
#include <vector>
#include <stack>

using std::vector;
using std::pair;
using std::stack;

int number_of_components(vector<vector<int> > &adj) {
  int res = 0;
  stack<int> to_explore;
  vector<bool> visited(adj.size(), false);
  for(int i = 0; i < adj.size(); ++i) {
    if(!visited[i]) {
      ++res;
      to_explore.push(i);
      while(!to_explore.empty()) {
        int u = to_explore.top();
        if(visited[u]) {
          to_explore.pop();
        }
        else {
          visited[u] = true;
          for(auto v : adj[u]) {
            to_explore.push(v);
          }
        }
      }
    }
  }
  return res;
}

int main() {
  size_t n, m;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  for (size_t i = 0; i < m; i++) {
    int x, y;
    std::cin >> x >> y;
    adj[x - 1].push_back(y - 1);
    adj[y - 1].push_back(x - 1);
  }
  std::cout << number_of_components(adj);
}
