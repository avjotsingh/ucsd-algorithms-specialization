#include <iostream>
#include <vector>
#include <stack>

using std::vector;
using std::pair;
using std::stack;

int acyclic(vector<vector<int> > &adj) {
  vector<int> visited(adj.size(), false);
  vector<int> finish(adj.size(), 0);
  stack<int> to_explore;
  int t = 0;

  for(int i = 0; i < adj.size(); ++i) {
    if(visited[i])
      continue;
    to_explore.push(i);
    while(!to_explore.empty()) {
      int u = to_explore.top();
      if(visited[u]) {
        ++t;
        finish[u] = t;
        to_explore.pop();
      }
      else {
        visited[u] = true;
        for(auto v : adj[u]) {
          if(!visited[v])
            to_explore.push(v);
          else if(finish[v] == 0)
            return 1;
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
  }
  std::cout << acyclic(adj);
}
