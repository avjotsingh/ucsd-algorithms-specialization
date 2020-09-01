#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>
#include <stack>

using std::vector;
using std::cin;
using std::cout;
using std::stack;

class StockCharts {
 public:
  void Solve() {
    vector<vector<int>> stock_data = ReadData();
    int result = MinCharts(stock_data);
    WriteResponse(result);
  }

 private:
  struct Edge {
    int from, to, flow;
  };

  vector<vector<int>> ReadData() {
    int num_stocks, num_points;
    cin >> num_stocks >> num_points;
    vector<vector<int>> stock_data(num_stocks, vector<int>(num_points));
    for (int i = 0; i < num_stocks; ++i)
      for (int j = 0; j < num_points; ++j) {
        cin >> stock_data[i][j];
      }
    return stock_data;
  }

  void WriteResponse(int result) {
    cout << result << "\n";
  }

  int compute_flow(int source, int sink, vector<vector<int>> &adj_list, vector<struct Edge> &edges) {
    int flow = 0;
    while(true) {
      bool reachable = false;
      stack<int> to_explore;
      vector<bool> explored(adj_list.size(), false);
      vector<int> followed_edge(adj_list.size(), -1);

      to_explore.push(source);
      while(!to_explore.empty()) {
        if(reachable) {
          break;
        }
        int u = to_explore.top();
        if(explored[u]) {
          to_explore.pop();
          continue;
        }
        else {
          explored[u] = true;
          for(auto e_id : adj_list[u]) {
            auto e = edges[e_id];
            if(e.flow == 1 && !explored[e.to]) {
              followed_edge[e.to] = e_id;
              to_explore.push(e.to);
              if(e.to == sink) {
                reachable = true;
                break;
              }
            }
          }
        }
      }

      if(followed_edge[sink] == -1) {
        //cannot find more flows from source to sink; graph is in maximal flow state
        break;
      }
      else {
        ++flow;
        //update the graph
        //change the flow of edges (source to sink path) from 1 to 0
        //change the flow of reverse edges from 0 to 1
        int to = sink;
        while(followed_edge[to] != -1) {
          int e_id = followed_edge[to];
          edges[e_id].flow = 0;
          edges[e_id ^ 1].flow = 1;
          to = edges[e_id].from;
        }
      }
    }
    return flow;
  }

  int MinCharts(const vector<vector<int>>& stock_data) {
    int n = stock_data.size();
    vector<struct Edge> edges;
    vector<vector<int>> adj_list(2*n + 2);

    int src = 0, sink = 2*n + 1;
    for(int i = 1; i <= n; ++i) {
      adj_list[src].push_back(edges.size());
      edges.push_back({src, i, 1});
      adj_list[i].push_back(edges.size());
      edges.push_back({i, src, 0});
    }
    for(int i = n + 1; i <= 2*n; ++i) {
      adj_list[i].push_back(edges.size());
      edges.push_back({i, sink, 1});
      adj_list[sink].push_back(edges.size());
      edges.push_back({sink, i, 0});
    }
    for(int i = 0; i < stock_data.size() - 1; ++i) {
      for(int j = i + 1; j < stock_data.size(); ++j) {
        if(compare(stock_data[i], stock_data[j])) {
          adj_list[i + 1].push_back(edges.size());
          edges.push_back({i + 1, n + j + 1, 1});
          adj_list[n + j + 1].push_back(edges.size());
          edges.push_back({n + j + 1, i + 1, 0});
        }
        else if(compare(stock_data[j], stock_data[i])) {
          adj_list[j + 1].push_back(edges.size());
          edges.push_back({j + 1, n + i + 1, 1});
          adj_list[n + i + 1].push_back(edges.size());
          edges.push_back({n + i + 1, j + 1, 0});
        }
      }
    }
    int max_flow = compute_flow(src, sink, adj_list, edges);
    return n - max_flow;
  }

  bool compare(const vector<int>& stock1, const vector<int>& stock2) {
    bool result = true;
    for(int i = 0; i < stock1.size(); ++i) {
      if(stock1[i] >= stock2[i]) {
        result = false;
        break;
      }
    }
    return result;
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  StockCharts stock_charts;
  stock_charts.Solve();
  return 0;
}
