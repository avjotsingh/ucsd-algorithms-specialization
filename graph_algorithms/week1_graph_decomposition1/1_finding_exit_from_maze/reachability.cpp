#include <iostream>
#include <vector>
#include <stack>

using std::vector;
using std::pair;
using std::stack;

int reach(vector<vector<int> > &adj, int x, int y) {
  int reachable = 0;
  stack<int> to_explore;
  vector<bool> visited(adj.size(), false);

  to_explore.push(x);
  while(!to_explore.empty()) {
    int u = to_explore.top();
    if(visited[u]) {
      to_explore.pop();
    }
    else {
      visited[u] = true;
      for(auto v : adj[u]) {
      if(v == y) {
        return 1;
      }
      else {
          to_explore.push(v);
        }
      }
    }
  }
  return 0;
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
  int x, y;
  std::cin >> x >> y;
  std::cout << reach(adj, x - 1, y - 1);
}
