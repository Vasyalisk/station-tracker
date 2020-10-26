#include "Constants.h"

namespace Station {	namespace Simulation
{
	namespace detail
	{
		const size_t DEF_ST_NUMBER = 6;
		const GenRange_t DEF_BUY_RANGE{ 25, 90 }, DEF_SELL_RANGE{ 15, 70 }, DEF_DIST_RANGE = { 5, 40 };
		const std::vector<std::string> DEF_PREFs { "Big", "Small", "Long", "Short", "Old", "New"  };
		const std::vector<std::string> DEF_POSTs { "Tree", "River", "Rock", "Lake", "Hill", "Mountain" };
		const std::vector<std::string> DEF_NAMES{};
	}
}}

