#pragma once

#include "LengauerTarjanVertexDominators.hpp"

#include <vector>
#include <utility>

namespace LengauerTarjan {

    class LengauerTarjanEdgeDominators {
    private:
        struct Edge {
            int from;
            int to;
        };

        int originalVertexCount;
        int originalEdgeCount;
        int startVertex;

        std::vector<std::vector<int>> originalGraph;
        std::vector<std::vector<int>> transformedGraph;

        std::vector<Edge> edges;

        // edge id -> artificial node in transformed graph
        std::vector<int> edgeToNode;

        // transformed node -> edge id
        // for original vertices this is -1
        std::vector<int> nodeToEdge;

        // vertex dominators computed on transformed graph
        std::vector<int> transformedIdom;

    private:
        void collect_edges();

        void build_transformed_graph();

        std::pair<int, int> find_immediate_edge_dominator_of_vertex(int vertex) const;

    public:
        LengauerTarjanEdgeDominators(std::vector<std::vector<int>> G);

        std::vector<std::pair<int, int>> compute_dominators(int start);
    };

}