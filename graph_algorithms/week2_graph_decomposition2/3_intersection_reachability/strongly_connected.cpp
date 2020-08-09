#include <algorithm>
#include <iostream>
#include <vector>
#include <stack>

using std::vector;
using std::pair;
using std::stack;

int dfs(vector<vector<int>> adj, vector<int> &order) {
  /*
  * order: ordering of the vertices for DFS to run
  * [RETURN]: number of times a fresh DFS exploration took place 
  */

  /*
  * vector[i] can take 3 values:
  * 0 => vertex not visited
  * 1 => vertex visited but order not assigned
  * 2 => vertex visited and order assigned
  */
  vector<int> visited(adj.size(), 0);
  vector<int> new_order;
  int n_dfs = 0;
  for(int i = 0, t = 0; i < adj.size(); ++i) {
    int w = order[i];
    if(visited[w] == 2) {
      continue;
    }
    else {
      ++n_dfs;
      stack<int> to_explore;
      to_explore.push(w);
      while(!to_explore.empty()) {
        int u = to_explore.top();
        if(visited[u] == 0) {
          visited[u] = 1;
          for(auto v : adj[u]) {
            if(visited[v] == 0) {
              to_explore.push(v);
            }
          }
        }
        else if(visited[u] == 1) {
          visited[u] = 2;
          new_order.push_back(u);
          to_explore.pop();
        }
        else {
          to_explore.pop();
        }
      }
    }
  }
  for(int i = 0; i < new_order.size(); ++i) {
    order[i] = new_order[i];
  }
  return n_dfs;
}

int number_of_strongly_connected_components(vector<vector<int>> &adj) {
  int result = 0;
  vector<int> order;
  for(int i = 0; i < adj.size(); ++i) {
    order.push_back(i);
  }
  vector<vector<int>> adj_rev(adj.size());
  for(int i = 0; i < adj.size(); ++i) {
    for(int j = 0; j < adj[i].size(); ++j) {
      adj_rev[adj[i][j]].push_back(i);
    }
  }
  dfs(adj_rev, order);
  reverse(order.begin(), order.end());
  result = dfs(adj, order);
  return result;
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
  std::cout << number_of_strongly_connected_components(adj);
}
