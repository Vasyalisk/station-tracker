#include "Constants.h"

#include <limits>
#include <array>

namespace Station { namespace Model
{
	namespace detail
	{
		const double DB_INF = std::numeric_limits<double>::infinity();
		const double DB_NAN = std::numeric_limits<double>::quiet_NaN();

		const double DEF_MIN_PROFIT = 0;
		const double DEF_MAX_DIST = DB_INF;
		const double DEF_MIN_PRICE_DIFF = 0;
		const std::array<double, 2> DEF_PRICES = { DB_NAN, DB_NAN };
	}
}}