#include "LengauerTarjanEdgeDominators.hpp"

#include <chrono>
#include <iostream>

namespace LengauerTarjan {

    LengauerTarjanEdgeDominators::LengauerTarjanEdgeDominators(std::vector<std::vector<int>> G)
        : originalVertexCount(static_cast<int>(G.size())),
        originalEdgeCount(0),
        startVertex(-1),
        originalGraph(G) {

        collect_edges();
    }

    void LengauerTarjanEdgeDominators::collect_edges() {
        edges.clear();

        for (int u = 0; u < originalVertexCount; ++u) {
            for (int v : originalGraph[u]) {
                edges.push_back({ u, v });
            }
        }

        originalEdgeCount = static_cast<int>(edges.size());
    }

    void LengauerTarjanEdgeDominators::build_transformed_graph() {
        int transformedVertexCount = originalVertexCount + originalEdgeCount;

        transformedGraph.assign(transformedVertexCount, {});
        edgeToNode.assign(originalEdgeCount, -1);
        nodeToEdge.assign(transformedVertexCount, -1);

        for (int edgeId = 0; edgeId < originalEdgeCount; ++edgeId) {
            int u = edges[edgeId].from;
            int v = edges[edgeId].to;

            int edgeNode = originalVertexCount + edgeId;

            edgeToNode[edgeId] = edgeNode;
            nodeToEdge[edgeNode] = edgeId;

            /*
                Original edge:

                    u -> v

                becomes:

                    u -> edgeNode -> v
            */

            transformedGraph[u].push_back(edgeNode);
            transformedGraph[edgeNode].push_back(v);
        }
    }

    std::pair<int, int>
        LengauerTarjanEdgeDominators::find_immediate_edge_dominator_of_vertex(int vertex) const {
        if (vertex < 0 || vertex >= originalVertexCount) {
            return { -1, -1 };
        }

        if (vertex >= static_cast<int>(transformedIdom.size())) {
            return { -1, -1 };
        }

        int current = transformedIdom[vertex];

        /*
            We are standing on an original vertex.

            We climb through its immediate dominator chain in the transformed graph.

            The first artificial edge-node we find represents the immediate
            edge dominator of this original vertex.
        */

        while (current != -1) {
            int edgeId = nodeToEdge[current];

            if (edgeId != -1) {
                return {
                    edges[edgeId].from,
                    edges[edgeId].to
                };
            }

            int parent = transformedIdom[current];

            // Safety if some implementation uses idom[start] = start.
            if (parent == current) {
                break;
            }

            current = parent;
        }

        return { -1, -1 };
    }

    std::vector<std::pair<int, int>>
        LengauerTarjanEdgeDominators::compute_dominators(int start) {

        startVertex = start;

        build_transformed_graph();

        LengauerTarjanVertexDominators vertexDominators(transformedGraph);

        transformedIdom = vertexDominators.compute_dominators(startVertex);

        std::vector<std::pair<int, int>> result(
            originalVertexCount,
            { -1, -1 }
        );

        for (int vertex = 0; vertex < originalVertexCount; ++vertex) {
            if (vertex == startVertex) {
                result[vertex] = { -1, -1 };
                continue;
            }

            result[vertex] = find_immediate_edge_dominator_of_vertex(vertex);
        }

        return result;
    }

}