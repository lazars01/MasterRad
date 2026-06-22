#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <numeric>
#include <stdexcept>
#include "BBridges.hpp"
#include "BAP.hpp"
#include <chrono>
#include <iomanip>
#include <cstdlib>
#include <ctime>

using namespace std;

vector<vector<int>> generateRandomStronglyBiconnectedGraph(int n, double extraEdgeProbability = 0.25);
int countEdges(const std::vector<std::vector<int>>& graph);
void testAvgTimeBAP();
void testAvgTimeBBridges();


int main() {

    testAvgTimeBAP();
    testAvgTimeBBridges();

    return 0;
}

vector<vector<int>> generateRandomStronglyBiconnectedGraph(
    int n,
    double extraEdgeProbability
) {
    if (n < 3) {
        throw invalid_argument("Strongly biconnected graph generator requires n >= 3.");
    }

    extraEdgeProbability = max(0.0, min(1.0, extraEdgeProbability));

    vector<vector<int>> graph(n);
    vector<vector<bool>> hasEdge(n, vector<bool>(n, false));

    static random_device rd;
    static mt19937 rng(rd());

    auto addEdge = [&](int u, int v) {
        if (u != v && !hasEdge[u][v]) {
            graph[u].push_back(v);
            hasEdge[u][v] = true;
        }
        };

    vector<int> vertices(n);
    iota(vertices.begin(), vertices.end(), 0);
    shuffle(vertices.begin(), vertices.end(), rng);

    for (int i = 0; i < n; i++) {
        int u = vertices[i];
        int v = vertices[(i + 1) % n];

        addEdge(u, v);
    }

    bernoulli_distribution shouldAdd(extraEdgeProbability);

    for (int u = 0; u < n; u++) {
        for (int v = 0; v < n; v++) {
            if (u == v || hasEdge[u][v]) {
                continue;
            }

            if (shouldAdd(rng)) {
                addEdge(u, v);
            }
        }
    }

    return graph;
}

int countEdges(const std::vector<std::vector<int>>& graph) {
    int edges = 0;

    for (const auto& neighbours : graph) {
        edges += neighbours.size();
    }

    return edges;
}

void testAvgTimeBAP() {
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    std::vector<int> graphSizes = { 10, 20, 50, 75, 100, 125, 150, 175, 200 };

    constexpr int numberOfGraphsPerSize = 10;
    constexpr double extraEdgeProbability = 0.1;

    std::cout << std::left
        << std::setw(12) << "Vertices"
        << std::setw(18) << "Avg edges"
        << std::setw(22) << "Avg time (ms)"
        << '\n';

    std::cout << std::string(74, '-') << '\n';

    for (int n : graphSizes)
    {
        long long totalEdges = 0;
        double totalTimeMicroseconds = 0.0;

        for (int i = 0; i < numberOfGraphsPerSize; ++i)
        {
            auto graph = generateRandomStronglyBiconnectedGraph(
                n,
                extraEdgeProbability
            );

            totalEdges += countEdges(graph);

            auto start = std::chrono::steady_clock::now();

            B::BAP::b_ap(graph);

            auto end = std::chrono::steady_clock::now();

            std::chrono::duration<double, std::micro> elapsed = end - start;
            totalTimeMicroseconds += elapsed.count();
        }

        double averageEdges =
            static_cast<double>(totalEdges) / numberOfGraphsPerSize;

        double averageTimeMicroseconds =
            totalTimeMicroseconds / numberOfGraphsPerSize;

        double averageTimeMilliseconds =
            averageTimeMicroseconds / 1000.0;

        std::cout << std::left
            << std::setw(12) << n
            << std::setw(18) << averageEdges
            << std::setw(22) << averageTimeMilliseconds
            << '\n';
    }
}

void testAvgTimeBBridges() {
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    std::vector<int> graphSizes = { 10, 20, 50, 75, 100, 125, 150, 175, 200 };

    constexpr int numberOfGraphsPerSize = 10;
    constexpr double extraEdgeProbability = 0.1;

    std::cout << std::left
        << std::setw(12) << "Vertices"
        << std::setw(18) << "Avg edges"
        << std::setw(22) << "Avg time (ms)"
        << '\n';

    std::cout << std::string(74, '-') << '\n';

    for (int n : graphSizes)
    {
        long long totalEdges = 0;
        double totalTimeMicroseconds = 0.0;

        for (int i = 0; i < numberOfGraphsPerSize; ++i)
        {
            auto graph = generateRandomStronglyBiconnectedGraph(
                n,
                extraEdgeProbability
            );

            totalEdges += countEdges(graph);

            auto start = std::chrono::steady_clock::now();

            B::BBridges::b_bridges(graph);

            auto end = std::chrono::steady_clock::now();

            std::chrono::duration<double, std::micro> elapsed = end - start;
            totalTimeMicroseconds += elapsed.count();
        }

        double averageEdges =
            static_cast<double>(totalEdges) / numberOfGraphsPerSize;

        double averageTimeMicroseconds =
            totalTimeMicroseconds / numberOfGraphsPerSize;

        double averageTimeMilliseconds =
            averageTimeMicroseconds / 1000.0;

        std::cout << std::left
            << std::setw(12) << n
            << std::setw(18) << averageEdges
            << std::setw(22) << averageTimeMilliseconds
            << '\n';
    }
}