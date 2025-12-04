#pragma once

#include <vector>

namespace Strong {

	class StrongAP {
	public:
		static std::vector<int> strong_aps(std::vector<std::vector<int>> G, int s);
	private:
		static bool reachable_all(const std::vector<std::vector<int>>& G, int s, int banned);
		static bool is_strong_ap(const std::vector<std::vector<int>>& G, int v);
	};
}