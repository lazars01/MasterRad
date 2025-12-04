#pragma once

#include <vector>

namespace Strong {

	class StrongBridges {
	public:
		static std::vector<std::pair<int, int>> strong_bridges(std::vector<std::vector<int>> G, int s);
	};
}