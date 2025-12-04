#include "LengauerTarjanEdgeDominators.hpp"

namespace LengauerTarjan {

    std::vector<std::pair<int, int>> LengauerTarjanEdgeDominators::compute(const std::vector<std::vector<int>>& G, int start) {
        const int n = (int)G.size();

        // map each original edge to an edge-node id
        std::vector<std::pair<int, int>> E; E.reserve(1 << 12);
        std::unordered_map<long long, int> eid; eid.reserve(1 << 12);
        auto key = [](int u, int v)->long long { return ((long long)u << 32) ^ (unsigned)v; };

        for (int u = 0; u < n; ++u)
            for (int v : G[u]) {
                int id = (int)E.size();
                E.emplace_back(u, v);
                eid[key(u, v)] = id;
            }
        const int m = E.size();
        const int S = m; 

        // build edge graph EG 
        std::vector<std::vector<int>> EG(m + 1);
        for (int i = 0; i < m; ++i)
            if (E[i].first == start) EG[S].push_back(i);
        for (int i = 0; i < m; ++i) {
            int u = E[i].first, v = E[i].second;
            for (int w : G[v]) {
                auto it = eid.find(key(v, w));
                if (it != eid.end()) EG[i].push_back(it->second);
            }
        }

        LengauerTarjanVertexDominators lt = LengauerTarjanVertexDominators(EG);
        std::vector<int> idom = lt.compute_dominators(S); 

        std::vector<std::vector<int>> tree(m + 1);
        std::vector<int> parent(m + 1, -1), depth(m + 1, -1);
        for (int v = 0; v <= m; ++v) {
            int p = idom[v];
            parent[v] = p;
            if (p != -1) tree[p].push_back(v);
        }
        if (m >= 0) {
            std::vector<int> st{ S };
            depth[S] = 0;
            while (!st.empty()) {
                int u = st.back(); st.pop_back();
                for (int w : tree[u]) {
                    depth[w] = depth[u] + 1;
                    st.push_back(w);
                }
            }
        }

        auto lca = [&](int a, int b) {
            if (a == -1) return b;
            if (b == -1) return a;
            int u = a, v = b;
            if (depth[u] < depth[v]) std::swap(u, v);
            while (depth[u] > depth[v]) u = parent[u];
            while (u != v) { u = parent[u]; v = parent[v]; }
            return u;
            };

        std::vector<std::vector<int>> incoming(n);
        for (int i = 0; i < m; ++i) incoming[E[i].second].push_back(i);

        std::vector<std::pair<int, int>> res(n, { -1,-1 });
        for (int v = 0; v < n; ++v) {
            if (v == start) { res[v] = { -1,-1 }; continue; }

            int cur = -1;
            for (int e : incoming[v]) {
                if (depth[e] == -1) continue; 
                cur = lca(cur, e);
            }
            if (cur == -1 || cur == S) res[v] = { -1,-1 };
            else res[v] = E[cur];
        }
        return res;
    }
}