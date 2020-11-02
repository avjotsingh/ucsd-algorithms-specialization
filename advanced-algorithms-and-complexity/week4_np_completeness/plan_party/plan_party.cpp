#include <iostream>
#include <vector>
#include <sys/resource.h>

using namespace std;

struct Vertex {
    int weight;
    std::vector <int> children;
};
typedef std::vector<Vertex> Graph;
typedef std::vector<int> Sum;

Graph ReadTree() {
    int vertices_count;
    std::cin >> vertices_count;

    Graph tree(vertices_count);

    for (int i = 0; i < vertices_count; ++i)
        std::cin >> tree[i].weight;

    for (int i = 1; i < vertices_count; ++i) {
        int from, to, weight;
        std::cin >> from >> to;
        tree[from - 1].children.push_back(to - 1);
        tree[to - 1].children.push_back(from - 1);
    }

    return tree;
}

int dfs(const Graph &tree, Sum &max_fun, int vertex, int parent) {
    if(max_fun[vertex] != -1) {
        return max_fun[vertex];
    }

    int fun_1 = 0;
    int fun_2 = tree[vertex].weight;
    for (int child : tree[vertex].children) {
        if (child != parent) {
            fun_1 += dfs(tree, max_fun, child, vertex);
            for(int grandchild : tree[child].children) {
               if(grandchild != vertex) {
                    fun_2 += dfs(tree, max_fun, grandchild, child);
                }
            }
        }
    }

    max_fun[vertex] = max(fun_1, fun_2);
    return max_fun[vertex];
}

int MaxWeightIndependentTreeSubset(const Graph &tree) {
    size_t size = tree.size();
    if (size == 0)
        return 0;
    Sum max_fun(size, -1);
    return dfs(tree, max_fun, 0, -1);
}

int main() {
    // This code is here to increase the stack size to avoid stack overflow
    // in depth-first search.
    const rlim_t kStackSize = 64L * 1024L * 1024L;  // min stack size = 64 Mb
    struct rlimit rl;
    int result;
    result = getrlimit(RLIMIT_STACK, &rl);
    if (result == 0)
    {
        if (rl.rlim_cur < kStackSize)
        {
            rl.rlim_cur = kStackSize;
            result = setrlimit(RLIMIT_STACK, &rl);
            if (result != 0)
            {
                fprintf(stderr, "setrlimit returned result = %d\n", result);
            }
        }
    }

    // Here begins the solution
    Graph tree = ReadTree();
    int weight = MaxWeightIndependentTreeSubset(tree);
    std::cout << weight << std::endl;
    return 0;
}
