#include <bits/stdc++.h>
using namespace std;

struct Node {
    int id = -1;
    int low = -1;
    bool on_stack = false;
    vector<int> neighbours;
    unordered_map<int, bool> assignment;
};

class TwoSatisfiability {
private:
    int numVars;
    unordered_map<int, Node> vertices;
    int dfs_id;
    stack<int> stk;
    unordered_map<int, int> assignment;
    bool satisfiable;
 
public:

    TwoSatisfiability(int n): numVars(n), vertices(unordered_map<int, Node>(2*n)), dfs_id(1), satisfiable(true) { }

    void add_clause(int firstVar, int secondVar) {
        vertices[-firstVar].neighbours.push_back(secondVar);
        vertices[-secondVar].neighbours.push_back(firstVar);
    }

    void dfs(int i) {
        vertices[i].id = vertices[i].low = ++dfs_id;
        vertices[i].on_stack = true;
        stk.push(i);

        for(auto v: vertices[i].neighbours) {
            if(vertices[v].id == -1) {
                dfs(v);
                vertices[i].low = min(vertices[i].low, vertices[v].low);
            }
            else if(vertices[v].on_stack) {
                vertices[i].low = min(vertices[i].low, vertices[v].low);
            }
        }

        if(vertices[i].low == vertices[i].id) {
            int w;
            do {
                w = stk.top();
                stk.pop();
                
                vertices[w].low = vertices[i].low;
                vertices[w].on_stack = false;
                if(vertices[w].low == vertices[-w].low) {
                    satisfiable = false;
                    return;
                }

                if(assignment.find(w) == assignment.end()) {                
                    assignment[w] = 1;
                    assignment[-w] = 0;
                }
            } while(w != i);
        }
    }

    void solve() {
        for(int i = -numVars; i <= numVars; ++i) {
            if(i != 0 && vertices[i].id == -1) {
                dfs(i);
            }
        }
    }

    void print_solution() {
        if(!satisfiable) {
            cout << "UNSATISFIABLE" << endl;
        }
        else {
            cout << "SATISFIABLE" << endl;
            for(int i = 1; i <= numVars; ++i) {
                if(assignment[i]) {
                    cout << i;
                }
                else {
                    cout << -i;
                }
                if(i < numVars) {
                    cout << " ";
                }
                else {
                    cout << endl;
                }
            }
        }
    }
};

int main() {
    ios::sync_with_stdio(false);

    int n, m;
    cin >> n >> m;
    TwoSatisfiability twoSat(n);
    for (int i = 0; i < m; ++i) {
        int firstVar, secondVar;
        cin >> firstVar >> secondVar;
        twoSat.add_clause(firstVar, secondVar);
    }

    twoSat.solve();
    twoSat.print_solution();

    return 0;
}
