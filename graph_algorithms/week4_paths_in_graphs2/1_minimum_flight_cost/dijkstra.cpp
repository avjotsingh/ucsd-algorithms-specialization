#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using std::vector;
using std::queue;
using std::pair;
using std::priority_queue;

struct node {
  int id;
  long dist;
};

bool operator<(const node &n1, const node &n2) {
  return n1.dist > n2.dist;
}

long long distance(vector<vector<int> > &adj, vector<vector<int> > &cost, int s, int t) {
  priority_queue<node> q;
  long long inf = 1000000000001;
  vector<long long> dist(adj.size(), inf);
  for(int i = 0; i < adj.size(); ++i) {
    dist[i] = inf;
    long d = (i == s) ? 0 : dist[i];
    q.push({i, d});
  }
  for(int i = 0; i < adj.size(); ++i) {
    while(dist[q.top().id] != inf) {
      q.pop();
    }
    node top = q.top();
    q.pop();
    int u = top.id;
    dist[u] = top.dist;
    for(int j = 0; j < adj[top.id].size(); ++j) {
      int v = adj[u][j];
      if(dist[v] == inf) {
        q.push({v, dist[u] + cost[u][j]}); 
      }
    }
  }
  return (dist[t] == inf) ? -1 : dist[t];
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
  int s, t;
  std::cin >> s >> t;
  s--, t--;
  std::cout << distance(adj, cost, s, t);
}
