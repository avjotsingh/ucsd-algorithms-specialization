#include <iostream>
#include <vector>
#include <queue>

using std::vector;
using std::queue;

int bipartite(vector<vector<int> > &adj) {
  /*
  * label[i] can take 3 values
  * 0 => label is unassigned
  * 1 => ith vertex belongs to group 1
  * 2 => ith vertex belongs to group 2
  */
  vector<int> label(adj.size(), 0);
  for(int i = 0; i < adj.size(); ++i) {
    if(label[i] > 0) {
      continue;
    }
    else {
      queue<int> q;
      q.push(i);
      label[i] = 1;
      while(!q.empty()) {
        int u = q.front();
        q.pop();
        for(auto v : adj[u]) {
          if(label[v] == label[u]) {
            return 0;
          }
          else if(label[v] == 0) {
            q.push(v);
            label[v] = (label[u] == 1) ? 2 : 1;
          }
        }
      }
    }
  }
  return 1;
}

int main() {
  int n, m;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  for (int i = 0; i < m; i++) {
    int x, y;
    std::cin >> x >> y;
    adj[x - 1].push_back(y - 1);
    adj[y - 1].push_back(x - 1);
  }
  std::cout << bipartite(adj);
}
