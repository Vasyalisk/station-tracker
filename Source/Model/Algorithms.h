#pragma once

#include <Model/Connection.h>
#include <Model/LinkedStation.h>
#include <Model/Constants.h>

#include <vector>
#include <list>
#include <Model/Types.h>

namespace Station { namespace Model
{
	// Finds shortest connection between two specified stations.
	Connection ConnectionFromTo(LinkedStation& fromSt, LinkedStation& toSt, std::vector<LinkedStRef_t> stations);
	// Finds shortest connection between two specified stations.
	Connection ConnectionFromTo(LinkedStation& fromSt, LinkedStation& toSt, std::list<LinkedStation>& stations);

	// Finds two stations with the most price difference and then the shortest connection between them.
	Connection MostPriceDiffConnection(
		std::vector<LinkedStRef_t> stations,
		double minPriceDiff = detail::DEF_MIN_PRICE_DIFF
	);
	// Finds two stations with the most price difference and then the shortest connection between them.
	Connection MostPriceDiffConnection(
		std::list<LinkedStation>& stations,
		double minPriceDiff = detail::DEF_MIN_PRICE_DIFF
	);

	// Finds a station with the most price difference and then the shortest connection between it and the fromSt.
	Connection MostPriceDiffConnectionFrom(
		LinkedStation &fromSt,
		std::vector<LinkedStRef_t> stations,
		double maxDist = detail::DEF_MAX_DIST,
		double minPriceDiff = detail::DEF_MIN_PRICE_DIFF
	);
	// Finds a station with the most price difference and then the shortest connection between it and the fromSt.
	Connection MostPriceDiffConnectionFrom(
		LinkedStation& fromSt,
		std::list<LinkedStation>& stations,
		double maxDist = detail::DEF_MAX_DIST,
		double minPriceDiff = detail::DEF_MIN_PRICE_DIFF
	);

	// Finds all shortest connections from fromSt and then finds the one with the most profit.
	Connection MostProfitConnectionFrom(
		LinkedStation& fromSt,
		std::vector<LinkedStRef_t> stations,
		double maxDist = detail::DEF_MAX_DIST,
		double minProfit = detail::DEF_MIN_PROFIT
	);
	// Finds all shortest connections from fromSt and then finds the one with the most profit.
	Connection MostProfitConnectionFrom(
		LinkedStation& fromSt,
		std::list<LinkedStation>& stations,
		double maxDist = detail::DEF_MAX_DIST,
		double minProfit = detail::DEF_MIN_PROFIT
	);
}}
