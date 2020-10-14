#include <bits/stdc++.h>
using namespace std;

struct Clause {
    int firstVar;
    int secondVar;
};

struct TwoSatisfiability {
private:
    vector<vector<int>> adj_list;
    unordered_map<int, int> vid;
    unordered_map<int, int> rvid;

    void construct_adjacency_list() {
        for(int i = 0; i < clauses.size(); ++i) {
            adj_list[vid[-clauses[i].firstVar]].push_back(vid[clauses[i].secondVar]);
            adj_list[vid[-clauses[i].secondVar]].push_back(vid[clauses[i].firstVar]);
        }
    }

    vector<pair<int, int>> dfs() {
        vector<pair<int, int>> finish_times;
        vector<bool> visited(adj_list.size(), false);
        for(int i = 1; i < adj_list.size(); ++i) {
            finish_times.push_back({i, INT_MAX});
        }
        int time = 0;
        for(int i = 1; i < adj_list.size(); ++i) {
            cout << "i:" << i << endl;
            if(!visited[i]) {
                cout << "dfs " << i << endl;
                stack<int> s;
                s.push(i);
                while(!s.empty()) {
                    int u = s.top();
                    cout << "u " << u << endl;
                    visited[u] = true;
                    for(auto v: adj_list[u]) {
                        if(!visited[v]) {
                            s.push(v);
                        }
                    }
                    if(u == s.top()) {
                        s.pop();
                        if(finish_times[u - 1].second == INT_MAX) {
                            ++time;
                            finish_times[u - 1].second = time;
                        }
                    }
                }
            }
            else {
                cout << "visited " << i << endl;
            }
        }
        cout << "done DFS\n";
        return finish_times;
    }

    bool dfs_and_assign(vector<pair<int, int>> finish_times, vector<int> &results) {
        for(int i = 0; i < results.size(); ++i) {
            results[i] = -1;
        }
        vector<bool> visited(adj_list.size(), false);
        for(auto e: finish_times) {
            auto x = e.first;
            if(!visited[x]) {
                stack<int> s;
                s.push(x);
                while(!s.empty()) {
                    int u = s.top();
                    int uid = rvid[u];
                    if(uid < 0 && results[-uid] == -1) {
                        results[-uid] = 0;
                    }
                    else if(uid > 0 && results[uid] == -1) {
                        results[uid] == 1;
                    }
                    else if((uid < 0 && results[-uid] == 1) || (uid > 0 && results[uid] == 0)) {
                        return false;
                    }
                    for(auto v: adj_list[u]) {
                        if(!visited[v]) {
                            s.push(v);
                        }
                    }
                    if(u == s.top()) {
                        s.pop();
                    }
                }
            }
        }
        return true;
    }

public:
    int numVars;
    vector<Clause> clauses;

    TwoSatisfiability(int n, int m): numVars(n), clauses(m), adj_list(vector<vector<int>>(2*n + 1, vector<int>())) {
        for(int i = 1; i <= numVars; ++i) {
            vid[i] = i;
            vid[-i] = i + numVars;
            rvid[i] = i;
            rvid[i + numVars] = -i;
        }
    }

    bool isSatisfiable(vector<int>& result) {
        construct_adjacency_list();
        cout << "adj list done\n";
        auto finish_times = dfs();
        cout << "one dfs done\n";
        sort(finish_times.begin(), finish_times.end(), [](pair<int, int> a, pair<int, int> b) { return a.second < b.second; });

        return dfs_and_assign(finish_times, result);
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
