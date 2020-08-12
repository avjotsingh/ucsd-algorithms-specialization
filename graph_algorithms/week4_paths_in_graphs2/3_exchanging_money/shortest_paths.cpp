#include <iostream>
#include <limits>
#include <vector>
#include <queue>

using std::vector;
using std::queue;
using std::pair;
using std::priority_queue;

void shortest_paths(vector<vector<int> > &adj, vector<vector<int> > &cost, int s, vector<long long> &distance, vector<int> &reachable, vector<int> &shortest) {
  int V = adj.size();
  long long inf = 1000000000001;

  for(int i = 0; i < V; ++i) {
    distance[i] = inf;
    reachable[i] = false;
    shortest[i] = 1;
  }
  distance[s] = 0;
  reachable[s] = true;
  shortest[s] = 1;
  /*
  * Run V - 1 iterations of Bellman Ford's algorithm
  * if an edge (u, v) can be relaxed, it means v is reachable from src
  */
  for(int i = 0; i < V - 1; ++i) {
    for(int j = 0; j < V; ++j) {
      for(int k = 0; k < adj[j].size(); ++k) {
        int v = adj[j][k];
        if(distance[j] != inf && distance[v] > distance[j] + cost[j][k]) {
          reachable[v] = true;
          distance[v] = distance[j] + cost[j][k];
        }
      }
    }
  }

  /*
  * Run one more iteration of Bellman Ford's algorithm to detect the vertices that can be reached from a negative weight cycle
  * One of these vertices will definitely lie on a cycle
  * Run BFS/DFS on all these vertices to detect the set of vertices which can be relaxed further
  * This set of vertices after BFS is reachable from the negative weight cycle
  */
  queue<int> to_explore;
  vector<int> visited(V, false);
  for(int j = 0; j < V; ++j) {
    for(int k = 0; k < adj[j].size(); ++k) {
      int v = adj[j][k];
      if(distance[j] != inf && distance[v] > distance[j] + cost[j][k]) {
        to_explore.push(v);
      }
    }
  }

  /* BFS */
  while(!to_explore.empty()) {
    int u = to_explore.front();
    to_explore.pop();
    visited[u] = true;
    shortest[u] = 0;
    for(auto v : adj[u]) {
      if(!visited[v]) {
        to_explore.push(v);
      }
    }
  }
}

int main() {
  int n, m, s;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  vector<vector<int> > cost(n, vector<int>());
  for (int i = 0; i < m; i++) {
    int x, y, w;
    std::cin >> x >> y >> w;
    adj[x - 1].push_back(y - 1);
    cost[x - 1].push_back(w);
  }
  std::cin >> s;
  s--;
  vector<long long> distance(n, std::numeric_limits<long long>::max());
  vector<int> reachable(n, 0);
  vector<int> shortest(n, 1);
  shortest_paths(adj, cost, s, distance, reachable, shortest);
  for (int i = 0; i < n; i++) {
    if (!reachable[i]) {
      std::cout << "*\n";
    } else if (!shortest[i]) {
      std::cout << "-\n";
    } else {
      std::cout << distance[i] << "\n";
    }
  }
}
