#pragma once
#include <vector>
#include <algorithm>

namespace LengauerTarjan {

    class LengauerTarjanVertexDominators {
    public:

        LengauerTarjanVertexDominators(std::vector<std::vector<int>> G);
        std::vector<int> compute_dominators(int start);
        static void DFS(std::vector<std::vector<int>> G, int start, std::vector<bool>& visited);

    private:
        int N;
        std::vector<std::vector<int>> graph, pred, bucket;
        std::vector<int> semi, idom, ancestor, label, vertex, parent;
        int dfs_time;

        void add_edge(int u, int v);
        void dfs(int v);
        void compress(int v);
        int eval(int v);
        void link(int v, int w);
    };

}
