#include <iostream>
#include "STBridges.hpp"
#include "STAP.hpp"
#include <vector>
#include <random>
#include <unordered_set>
#include <chrono>
#include <iomanip>
#include <cstdlib>
#include <ctime>

using namespace std;

vector<vector<int>> generateRandomDirectedGraph(int n, int m);
void testAvgTimeSTAP();
void testAvgTimeSTBridges();

int main() {
    testAvgTimeSTAP();
    testAvgTimeSTBridges();

    return 0;
}

vector<vector<int>> generateRandomDirectedGraph(int n, int m) {
	vector<vector<int>> graph(n);
	unordered_set<long long> usedEdges;

	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int> dist(0, n - 1);

	while ((int)usedEdges.size() < m) {
		int u = dist(gen);
		int v = dist(gen);

		if (u == v)
			continue;

		long long edgeCode = 1LL * u * n + v;

		if (usedEdges.count(edgeCode))
			continue;

		usedEdges.insert(edgeCode);
		graph[u].push_back(v);
	}

	return graph;
}

void testAvgTimeSTBridges() {
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    std::vector<pair<int, int>> graphSizes = { {10, 60}, {20, 240}, {50, 700}, {75, 1000}, {100, 1500}, {125, 1800}, {150, 2200}, {175, 2500}, {200, 3000} };

    constexpr int numberOfGraphsPerSize = 10;

    std::cout << std::left
        << std::setw(12) << "Vertices"
        << std::setw(18) << "Edges"
        << std::setw(22) << "Avg time (ms)"
        << '\n';

    std::cout << std::string(74, '-') << '\n';

    for (const auto& size : graphSizes)
    {
        double totalTimeMicroseconds = 0.0;

        for (int i = 0; i < numberOfGraphsPerSize; ++i)
        {
            auto graph = generateRandomDirectedGraph(size.first, size.second);

            random_device rd;
            mt19937 gen(rd());
            uniform_int_distribution<int> dist(0, size.first - 1);

            int s = dist(gen);
            int t = dist(gen);

            auto start = std::chrono::steady_clock::now();

            ST::STBridges::st_bridges(graph, s, t);

            auto end = std::chrono::steady_clock::now();

            std::chrono::duration<double, std::micro> elapsed = end - start;
            totalTimeMicroseconds += elapsed.count();
        }


        double averageTimeMicroseconds =
            totalTimeMicroseconds / numberOfGraphsPerSize;

        double averageTimeMilliseconds =
            averageTimeMicroseconds / 1000.0;

        std::cout << std::left
            << std::setw(12) << size.first
            << std::setw(12) << size.second
            << std::setw(22) << averageTimeMilliseconds
            << '\n';
    }
}

void testAvgTimeSTAP() {
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    std::vector<pair<int, int>> graphSizes = { {10, 60}, {20, 240}, {50, 700}, {75, 1000}, {100, 1500}, {125, 1800}, {150, 2200}, {175, 2500}, {200, 3000} };

    constexpr int numberOfGraphsPerSize = 10;

    std::cout << std::left
        << std::setw(12) << "Vertices"
        << std::setw(18) << "Edges"
        << std::setw(22) << "Avg time (ms)"
        << '\n';

    std::cout << std::string(74, '-') << '\n';

    for (const auto& size : graphSizes)
    {
        double totalTimeMicroseconds = 0.0;

        for (int i = 0; i < numberOfGraphsPerSize; ++i)
        {
            auto graph = generateRandomDirectedGraph(size.first, size.second);

            random_device rd;
            mt19937 gen(rd());
            uniform_int_distribution<int> dist(0, size.first - 1);

            int s = dist(gen);
            int t = dist(gen);

            auto start = std::chrono::steady_clock::now();

            ST::STAP::st_ap(graph, s, t);

            auto end = std::chrono::steady_clock::now();

            std::chrono::duration<double, std::micro> elapsed = end - start;
            totalTimeMicroseconds += elapsed.count();
        }


        double averageTimeMicroseconds =
            totalTimeMicroseconds / numberOfGraphsPerSize;

        double averageTimeMilliseconds =
            averageTimeMicroseconds / 1000.0;

        std::cout << std::left
            << std::setw(12) << size.first
            << std::setw(12) << size.second
            << std::setw(22) << averageTimeMilliseconds
            << '\n';
    }
}