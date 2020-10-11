#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int from;
    int to;
};

class Clauses {
private:
    vector<vector<int>> c;

public:
    void addNewClause() {
        c.push_back(vector<int>());
    }

    void push_back(int i) {
        c[c.size() - 1].push_back(i);
    }

    vector<vector<int>> get_clauses() {
        return c;
    }
};

struct ConvertHampathToSat {
    int numVertices;
    vector<Edge> edges;
    vector<vector<int>> clauses;

    ConvertHampathToSat(int n, int m) :
        numVertices(n),
        edges(m)
    {  }

    inline int X(int i, int j) {
        return numVertices*(i - 1) + j;
    }

    void printEquisatisfiableSatFormula() {
        Clauses clauses;

        /* 
            Each vertex belongs to a path
            X(i, 1) v X(i, 2) v ... v X(i, n) for each node i
        */
       for(int i = 1; i <= numVertices; ++i) {
           clauses.addNewClause();
           for(int j = 1; j <= numVertices; ++j) {
               clauses.push_back(X(i, j));
           }
       }

       /*
        Each vertex appears just once in a path
        -X(i, j) v -X(i, k) for all i, j, k where j != k
        */
        for(int i = 1; i <= numVertices; ++i) {
           for(int j = 1; j < numVertices; ++j) {
               for(int k = j+1; k <= numVertices; ++k) {
                   clauses.addNewClause();
                   clauses.push_back(-X(i, j));
                   clauses.push_back(-X(i, k));
               }
           }
       }

       /*
        Each position in the path is occupied by a vertex
        X(1, j) v X(2, j) v ... v X(n, j) for all positions j
        */
       for(int j = 1; j <= numVertices; ++j) {
           clauses.addNewClause();
           for(int i = 1; i <= numVertices; ++i) {
               clauses.push_back(X(i, j));
           }
       }

       /*
        No two vertices occupy the same position on a path
        -X(i, j) v -X(k, j) for all i, j, k where i != k
        */
       for(int j = 1; j <= numVertices; ++j) {
           for(int i = 1; i < numVertices; ++i) {
               for(int k = i + 1; k <= numVertices; ++k) {
                   clauses.addNewClause();
                   clauses.push_back(-X(i, j));
                   clauses.push_back(-X(k, j));
               }
           }
       }

       /*
        Two consecutive positions in a path can only have nodes which have an edge between them
        -X(i, j) v -X(k, j+1) for all i, j, k where (i, k) is not an edge
        */
       bool adj[numVertices + 1][numVertices + 1];
       for(int i = 0; i <= numVertices; ++i) {
           for(int j = 0; j <= numVertices; ++j) {
               adj[i][j] = false;
           }
       }
       for(auto e: edges) {
           adj[e.from][e.to] = true;
           adj[e.to][e.from] = true;
       }

       for(int i = 1; i < numVertices; ++i) {
           for(int k = i + 1; k <= numVertices; ++k) {
               if(!adj[i][k]) {
                   for(int j = 1; j < numVertices; ++j) {
                       clauses.addNewClause();
                       clauses.push_back(-X(i, j));
                       clauses.push_back(-X(k, j + 1));

                       clauses.addNewClause();
                       clauses.push_back(-X(k, j));
                       clauses.push_back(-X(i, j + 1));
                   }
               }
           }
       }

       auto cl = clauses.get_clauses();
       cout << cl.size() << " " << numVertices*numVertices << endl;
       for(auto c: cl) {
           for(auto l: c) {
               cout << l << " ";
           }
           cout << 0 << endl;
       }
    }
};

int main() {
    ios::sync_with_stdio(false);

    int n, m;
    cin >> n >> m;
    ConvertHampathToSat converter(n, m);
    for (int i = 0; i < m; ++i) {
        cin >> converter.edges[i].from >> converter.edges[i].to;
    }

    converter.printEquisatisfiableSatFormula();

    return 0;
}
