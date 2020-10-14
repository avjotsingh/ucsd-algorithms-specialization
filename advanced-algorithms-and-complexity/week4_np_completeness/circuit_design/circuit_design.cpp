#include <bits/stdc++.h>
using namespace std;

struct Clause {
    int firstVar;
    int secondVar;
};

struct TwoSatisfiability {
private:
    void dfs_explore(int v, vector<vector<int>> *adj, vector<bool> *visited, vector<int> *newly_explored = nullptr, vector<int> *finish_order = nullptr) {
        stack<int> s;
        s.push(v);
        while(!s.empty()) {
            auto x = s.top();
            *(visited + x) = true;
            for(auto y: adj[x]) {
                if(*(visited + y) == false) {
                    s.push(y);
                }
            }
            if(s.top() == x) {
                s.pop();
                if(newly_explored) {
                    newly_explored->push_back(x);
                }
                if(finish_order) {
                    *finish_order->push_back(x);
                }
            }
        }
    }

    void dfs_normal(vector<vector<int>> *adj, vector<int> *finish_order) {
        vector<bool> visited(adj->size(), false);
        for(int i = 1; i < adj->size(); ++i) {
            if(!visited[i])  {
                dfs_explore(i, adj, &visited, nullptr, finish_order);
            }
        }
    }

    vector<int> dfs_check_satisfiable(vector<vector<int>> *adj, vector<int> *finish_order, vector<int> *assignment) {
        isSatisfiable = true;
        vector<int> assignment(adj->size(), -1);
        vector<bool> visited(adj->size(), false);
        for(auto iter = finish_order.begin(); iter != finish_order.end(); ++iter) {
            auto v = *iter;
            vector<int> newly_explored;
            dfs_explore(v, adj, &visited, &newly_explored);
            for(auto x: newly_explored) {
                auto x_bar = x > numVars ?  x - numVars : x + numVars;
                if(assignment[x] == -1) {
                    assignment[x] = 1;
                    assignment[x_bar] = 0;
                }
                else if(assignment[x] == 0) {
                    return false;
                }
            }
        }
        return true;
    }

public:
    int numVars;
    vector<Clause> clauses;

    TwoSatisfiability(int n, int m) :
        numVars(n),
        clauses(m)
    {  }

    bool isSatisfiable(vector<int>& result) {
        vector<vector<int>> adj(2*numVars + 1, vector<int>());
        for(int i = 0; i < clauses.size(); ++i) {
            int l1 = clauses[i].firstVar > 0 ? clauses[i].firstVar : clauses[i].firstVar + numVars;
            int l2 = clauses[i].secondVar > 0 ? clauses[i].secondVar : clauses[i].secondVar + numVars;
            int l1_bar = l1 > numVars ? l1 - numVars : l1 + numVars;
            int l2_bar = l2 > numVars ? l2 - numVars : l2 + numVars;
            adj[l1_bar].push_back(l2);
            adj[l2_bar].push_back(l1);
        }

        vector<int> dfs_finish_order;
        dfs_normal(&adj, &dfs_finish_order);

        bool satisfiable;
        auto assignment = dfs_check_satisfiable(&adj, &dfs_finish_order, &satisfiable);
        if(satisfiable) {
            for(int i = 1; i <= numVars; ++i) {
                result[i - 1] = assignment[i];
            }
        }

        return satisfiable;
    }
};

int main() {
    ios::sync_with_stdio(false);

    int n, m;
    cin >> n >> m;
    TwoSatisfiability twoSat(n, m);
    for (int i = 0; i < m; ++i) {
        cin >> twoSat.clauses[i].firstVar >> twoSat.clauses[i].secondVar;
    }

    vector<int> result(n);
    if (twoSat.isSatisfiable(result)) {
        cout << "SATISFIABLE" << endl;
        for (int i = 1; i <= n; ++i) {
            if (result[i-1]) {
                cout << -i;
            } else {
                cout << i;
            }
            if (i < n) {
                cout << " ";
            } else {
                cout << endl;
            }
        }
    } else {
        cout << "UNSATISFIABLE" << endl;
    }

    return 0;
}
