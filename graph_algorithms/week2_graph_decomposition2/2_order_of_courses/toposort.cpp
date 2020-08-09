#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>

using std::vector;
using std::pair;
using std::stack;
using std::cout;

void dfs(vector<vector<int> > &adj, vector<int> &used, vector<int> &order, int x) {
  /*
  * used[i] can take 3 values, which indicate the following
  * 0 => vertex not visited
  * 1 => vertex visited but order not assigned
  * 2 => vertex visited and order assigned
  */
  for(int i = 0; i < adj.size(); ++i) {
    /*
    * if the ith vertex has already been assigned an order, skip
    * [NOTE] : used[i] cannot be equal to 1 because a new for loop iteration starts only when all the vertices in a DFS tree have been assigned an order
    */
    if(used[i] == 2)
      continue;
    else {
      /*
      * start exploring DFS tree from vertex i
      */
      stack<int> to_explore;
      to_explore.push(i);
      while(!to_explore.empty()) {
        int u = to_explore.top();
        if(used[u] == 0) {
          used[u] = 1;
          for(auto v : adj[u]) {
            if(used[v] == 0) {
              to_explore.push(v);
            }
          }
        }
        else if(used[u] == 1) {
          used[u] = 2;
          order.push_back(u);
          to_explore.pop();
        }
        else {
          to_explore.pop();
        }
      }
    }
  }

  reverse(order.begin(), order.end());
}     

vector<int> toposort(vector<vector<int> > adj) {
  vector<int> used(adj.size(), 0);
  vector<int> order;
  dfs(adj, used, order, 0);
  return order;
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
  vector<int> order = toposort(adj);
  for (size_t i = 0; i < order.size(); i++) {
    std::cout << order[i] + 1 << " ";
  }
}
