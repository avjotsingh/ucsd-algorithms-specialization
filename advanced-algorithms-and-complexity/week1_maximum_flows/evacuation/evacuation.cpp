#include <iostream>
#include <vector>
#include <stack>
#include <climits>

using std::vector;
using std::stack;

/* This class implements a bit unusual scheme for storing edges of the graph,
 * in order to retrieve the backward edge for a given edge quickly. */
class FlowGraph {
public:
    struct Edge {
        int from, to, flow;
    };

private:
    /* List of all - forward and backward - edges */
    vector<Edge> edges;

    /* These adjacency lists store only indices of edges in the edges list */
    vector<vector<size_t> > graph;

public:
    explicit FlowGraph(size_t n): graph(n) {}

    void add_edge(int from, int to, int capacity) {
        /* Note that we first append a forward edge and then a backward edge,
         * so all forward edges are stored at even indices (starting from 0),
         * whereas backward edges are stored at odd indices in the list edges */
        Edge forward_edge = {from, to, capacity};
        Edge backward_edge = {to, from, 0};
        graph[from].push_back(edges.size());
        edges.push_back(forward_edge);
        graph[to].push_back(edges.size());
        edges.push_back(backward_edge);
    }

    size_t size() const {
        return graph.size();
    }

    const vector<size_t>& get_ids(int from) const {
        return graph[from];
    }

    const Edge& get_edge(size_t id) const {
        return edges[id];
    }

    void add_flow(size_t id, int flow) {
        /* To get a backward edge for a true forward edge (i.e id is even), we should get id + 1
         * due to the described above scheme. On the other hand, when we have to get a "backward"
         * edge for a backward edge (i.e. get a forward edge for backward - id is odd), id - 1
         * should be taken.
         *
         * It turns out that id ^ 1 works for both cases. Think this through! */
        edges[id].flow += flow;
        edges[id ^ 1].flow -= flow;
    }
};

FlowGraph read_data() {
    int vertex_count, edge_count;
    std::cin >> vertex_count >> edge_count;
    FlowGraph graph(vertex_count);
    for (int i = 0; i < edge_count; ++i) {
        int u, v, capacity;
        std::cin >> u >> v >> capacity;
        graph.add_edge(u - 1, v - 1, capacity);
    }
    return graph;
}

int getflow(FlowGraph &graph, int from, int to) {
    int flow = INT_MAX;
    vector<int> edge_ids(graph.size(), -1);
    vector<bool> explored(graph.size(), false);
    stack<int> to_explore;
    bool reached = false;

    to_explore.push(from);
    while(!to_explore.empty()) {
        if(reached) {
            break;
        }
        int u = to_explore.top();
        // std::cout << "stack top : " << u << " " << explored[u] << "\n";
        if(explored[u]) {
            to_explore.pop();
            continue;
        }
        else {
            explored[u] = true;
            auto edges = graph.get_ids(u);
            for(auto edge_id : edges) {
                auto edge = graph.get_edge(edge_id);
                // std::cout << edge_id << " " << edge.from << " " << edge.to << " " << edge.flow << "\n";
                if(edge.flow > 0 && !explored[edge.to]) {
                    to_explore.push(edge.to);
                    edge_ids[edge.to] = edge_id;
                    if(edge.to == to) {
                        reached = true;
                        break;
                    }
                }
            }
        }
    }
    if(edge_ids[to] == -1) {
        return 0;
    }
    else {
        int u = to;
        vector<size_t> path;
        while(edge_ids[u] != -1) {
            auto edge = graph.get_edge(edge_ids[u]);
            // std::cout << edge.from << "->" << edge.to << " " << edge.flow << "\n";
            flow = std::min(flow, edge.flow);
            path.push_back(edge_ids[u]);
            u = edge.from;
        }
        for(auto edge_id : path) {
            graph.add_flow(edge_id, -1*flow);
        }
        return flow;
    }
}

int max_flow(FlowGraph& graph, int from, int to) {
    int flow = 0;
    while(int f = getflow(graph, from, to)) {
        flow += f;
    }
    return flow;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    FlowGraph graph = read_data();

    std::cout << max_flow(graph, 0, graph.size() - 1) << "\n";
    return 0;
}
