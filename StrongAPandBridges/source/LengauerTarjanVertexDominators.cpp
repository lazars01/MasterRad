#include "LengauerTarjanVertexDominators.hpp"

namespace LengauerTarjan {

    LengauerTarjanVertexDominators::LengauerTarjanVertexDominators(std::vector<std::vector<int>> G) : N(G.size()), pred(G.size()), bucket(G.size()),
        semi(G.size(), -1), idom(G.size(), -1), ancestor(G.size(), -1),
        label(G.size()), vertex(G.size()), parent(G.size(), -1), dfs_time(0) {
        for (int i = 0; i < N; ++i) label[i] = i;
        graph = G;
    }

    void LengauerTarjanVertexDominators::add_edge(int u, int v) {
        graph[u].push_back(v);
    }

    void LengauerTarjanVertexDominators::DFS(std::vector<std::vector<int>> G, int start, std::vector<bool>& visited) {
        
        for (int u : G[start]) {
            if (!visited[u]) {
                DFS(G, u, visited);
                visited[u] = true;
            }
        }
    }

    void LengauerTarjanVertexDominators::dfs(int v) {
        semi[v] = dfs_time;
        vertex[dfs_time] = v;
        dfs_time++;

        for (int w : graph[v]) {
            if (semi[w] == -1) {
                parent[w] = v;
                dfs(w);
            }
            pred[w].push_back(v);
        }
    }

    void LengauerTarjanVertexDominators::compress(int v) {
        if (ancestor[ancestor[v]] != -1) {
            compress(ancestor[v]);
            if (semi[label[ancestor[v]]] < semi[label[v]])
                label[v] = label[ancestor[v]];
            ancestor[v] = ancestor[ancestor[v]];
        }
    }

    int LengauerTarjanVertexDominators::eval(int v) {
        if (ancestor[v] == -1) return label[v];
        compress(v);
        if (semi[label[ancestor[v]]] < semi[label[v]])
            return label[ancestor[v]];
        else
            return label[v];
    }

    void LengauerTarjanVertexDominators::link(int v, int w) {
        ancestor[w] = v;
    }

    std::vector<int> LengauerTarjanVertexDominators::compute_dominators(int start) {
        dfs_time = 0;
        dfs(start);

        int n = dfs_time;

        for (int i = n - 1; i > 0; --i) {
            int w = vertex[i];
            for (int v : pred[w]) {
                int u = eval(v);
                if (semi[u] < semi[w])
                    semi[w] = semi[u];
            }
            bucket[vertex[semi[w]]].push_back(w);
            link(parent[w], w);
            for (int v : bucket[parent[w]]) {
                int u = eval(v);
                idom[v] = (semi[u] < semi[v]) ? u : parent[w];
            }
            bucket[parent[w]].clear();
        }

        for (int i = 1; i < n; ++i) {
            int w = vertex[i];
            if (idom[w] != vertex[semi[w]])
                idom[w] = idom[idom[w]];
        }

        idom[start] = -1;
        return idom;
    }
}