#include <iostream>
#include <vector>

using std::vector;

int negative_cycle(vector<vector<int> > &adj, vector<vector<int> > &cost) {
  /*
  * Bellman Ford's algorithm is able to detect negative weight cycles but it needs a source vertex
  * Since we do not know anything about the graph and the negative cycle, we do not know what vertex to consider as source vertex
  * [SOLUTION] : We add an additional vertex with a directed edge of weight 0 to every other vertex
  * [SOLUTION] : We can now run Bellman Ford's algorithm with this additional vertex as the source vertex
  */
  vector<int> a, c;
  for(int i = 0; i < adj.size(); ++i) {
    a.push_back(i);
    c.push_back(0);
  }
  adj.push_back(a);
  cost.push_back(c);

  int inf = 100000;
  bool change = false;
  vector<int> dist(adj.size(), inf);
  dist[adj.size() - 1] = 0;
  
  for(int i = 0; i < adj.size(); ++i) {
    change = false;
    for(int j = 0; j < adj.size(); ++j) {
      for(int k = 0; k < adj[j].size(); ++k) {
        int v = adj[j][k];
        if(dist[j] != inf && dist[v] > dist[j] + cost[j][k]) {
          change = true;
          dist[v] = dist[j] + cost[j][k];
        }
      }
    }
  }

  adj.erase(adj.end() - 1);
  cost.erase(cost.end() - 1);
  return change ? 1 : 0;
}

int main() {
  int n, m;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  vector<vector<int> > cost(n, vector<int>());
  for (int i = 0; i < m; i++) {
    int x, y, w;
    std::cin >> x >> y >> w;
    adj[x - 1].push_back(y - 1);
    cost[x - 1].push_back(w);
  }
  std::cout << negative_cycle(adj, cost);
}
