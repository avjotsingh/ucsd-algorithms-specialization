#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>
#include <stack>

using std::vector;
using std::cin;
using std::cout;
using std::stack;

class MaxMatching {
 public:
  void Solve() {
    vector<vector<bool>> adj_matrix = ReadData();
    vector<int> matching = FindMatching(adj_matrix);
    WriteResponse(matching);
  }

 private:
  struct Edge {
    int from, to, flow;
  };

  vector<vector<bool>> ReadData() {
    int num_left, num_right;
    cin >> num_left >> num_right;
    vector<vector<bool>> adj_matrix(num_left, vector<bool>(num_right));
    for (int i = 0; i < num_left; ++i)
      for (int j = 0; j < num_right; ++j) {
        int bit;
        cin >> bit;
        adj_matrix[i][j] = (bit == 1);
      }
    return adj_matrix;
  }

  void WriteResponse(const vector<int>& matching) {
    for (int i = 0; i < matching.size(); ++i) {
      if (i > 0)
        cout << " ";
      if (matching[i] == -1)
        cout << "-1";
      else
        cout << (matching[i] + 1);
    }
    cout << "\n";
  }

  void compute_residual_flow_graph(int source, int sink, vector<vector<int>> &adj_list, vector<struct Edge> &edges) {
    //as long as the residual graph has a path from source to sink
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


  }

  vector<int> FindMatching(const vector<vector<bool>>& adj_matrix) {
    //#vertices on the left
    int n = adj_matrix.size();
    //#vertices on the right
    int m = adj_matrix[0].size();
    //add source and sink vertex and construct a graph
    vector<struct Edge> edges;
    vector<vector<int>> adj_list(n + m + 2);
    
    //add edges from source to left vertices
    for(int i = 1; i <= n; ++i) {
      edges.push_back({0, i, 1});
      adj_list[0].push_back(edges.size() - 1);
      edges.push_back({i, 0, 0});
      adj_list[i].push_back(edges.size() - 1);
    }
    //add edges form right vertices to sink
    for(int i = n + 1; i <= n + m; ++i) {
      edges.push_back({i, n + m + 1, 1});
      adj_list[i].push_back(edges.size() - 1);
      edges.push_back({n + m + 1, i, 0});
      adj_list[n + m + 1].push_back(edges.size() - 1);
    }
    //add all other edges
    for(int i = 0; i < adj_matrix.size(); ++i) {
      for(int j = 0; j < adj_matrix[i].size(); ++j) {
        if(adj_matrix[i][j]) {
          edges.push_back({i + 1, n + 1 + j, 1});
          adj_list[i + 1].push_back(edges.size() - 1);
          edges.push_back({n + 1 + j, i + 1, 0});
          adj_list[n + 1 + j].push_back(edges.size() - 1);
        }
      }
    }

    vector<int> matching;
    compute_residual_flow_graph(0, n + m + 1, adj_list, edges);
    for(int i = 1; i <= n; ++i) {
      int match = -1;
      for(auto e_id : adj_list[i]) {
        auto e = edges[e_id];
        if(e.flow == 0 && e.to > 0) {
          match = e.to - n - 1;
          break;
        }
      }
      matching.push_back(match);
    }
    return matching;
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  MaxMatching max_matching;
  max_matching.Solve();
  return 0;
}
