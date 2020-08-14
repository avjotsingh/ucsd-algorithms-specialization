#include <algorithm>
#include <iostream>
#include <iomanip>
#include <cassert>
#include <vector>
#include <cmath>

using std::vector;
using std::pair;

int Find(int x, vector<int> &parent) {
  if(parent[x] == x) {
    return x;
  }
  else {
    parent[x] = Find(parent[x], parent);
    return parent[x];
  }
}

void Union(int x, int y, vector<int> &rank, vector<int> &parent) {
  int u = Find(x, parent);
  int v = Find(y, parent);
  if(rank[u] == rank[v]) {
    parent[u] = v;
    rank[v] += 1;
  }
  else if(rank[u] > rank[v]) {
    parent[v] = u;
  }
  else {
    parent[u] = v;
  }
}

double clustering(vector<int> x, vector<int> y, int k) {
  double result = 0.;
  vector<int> rank(x.size(), 1);
  vector<int> parent(x.size());
  for(int i = 0; i < x.size(); ++i) {
    parent[i] = i;
  }

  struct edge {
    int u;
    int v;
    double cost;
  };
  vector<struct edge> E;
  for(int i = 0; i < x.size(); ++i) {
    for(int j = i; j < x.size(); ++j) {
      E.push_back({ 
          i, 
          j, 
          std::sqrt((x[i] - x[j])*(x[i] - x[j]) + (y[i] - y[j])*(y[i] - y[j])) 
        });
    }
  }

  sort(E.begin(), E.end(), [](const edge &e1, const edge &e2) { return e1.cost < e2.cost; });
  int i, count = 0;
  for(i = 0; i < E.size(); ++i) {
    int u = E[i].u;
    int v = E[i].v;
    double c = E[i].cost;
    if(Find(u, parent) != Find(v, parent)) {
      count++;
      result += c;
      Union(u, v, rank, parent);
      if(count == x.size() - k) {
        break;
      }
    }
  }
  while(++i < E.size()) {
    if(Find(E[i].u, parent) != Find(E[i].v, parent)) {
      result = E[i].cost;
      break;
    }
  }
  return result;
} 

int main() {
  size_t n;
  int k;
  std::cin >> n;
  vector<int> x(n), y(n);
  for (size_t i = 0; i < n; i++) {
    std::cin >> x[i] >> y[i];
  }
  std::cin >> k;
  std::cout << std::setprecision(10) << clustering(x, y, k) << std::endl;
}
