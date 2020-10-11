#include <ios>
#include <iostream>
#include <vector>

using namespace std;

struct Edge {
    int from;
    int to;
};

struct ConvertGSMNetworkProblemToSat {
    int numVertices;
    vector<Edge> edges;

    ConvertGSMNetworkProblemToSat(int n, int m) :
        numVertices(n),
        edges(m)
    {  }

    void printEquisatisfiableSatFormula() {
        int c = 4*numVertices + 3*edges.size();
        int v = 3*numVertices;
        cout << c << " " << v << endl;
        for(int i = 0; i < numVertices; ++i) {
            cout << 3*i + 1 << " " << 3*i + 2 << " " << 3*i + 3 << " " << 0 << endl;
            cout << -(3*i + 1) << " " << -(3*i + 2) << " " << 0 << endl;
            cout << -(3*i + 2) << " " << -(3*i + 3) << " " << 0 << endl;
            cout << -(3*i + 3) << " " << -(3*i + 1) << " " << 0 << endl;
        }
        for(int i = 0; i < edges.size(); ++i) {
            int u = edges[i].from - 1;
            int v = edges[i].to - 1;
            cout << -(3*u + 1) << " " << -(3*v + 1) << " " << 0 << endl;
            cout << -(3*u + 2) << " " << -(3*v + 2) << " " << 0 << endl;
            cout << -(3*u + 3) << " " << -(3*v + 3) << " " << 0 << endl;
        }
    }
};

int main() {
    ios::sync_with_stdio(false);

    int n, m;
    cin >> n >> m;
    ConvertGSMNetworkProblemToSat converter(n, m);
    for (int i = 0; i < m; ++i) {
        cin >> converter.edges[i].from >> converter.edges[i].to;
    }

    converter.printEquisatisfiableSatFormula();

    return 0;
}
