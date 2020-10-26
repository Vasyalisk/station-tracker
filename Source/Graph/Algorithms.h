#pragma once

#include <Graph/Types.h>
#include <Graph/DijkstraGraph.h>

namespace Station { namespace Graph
{
	namespace defaults = Station::Model::detail;

	// Finds shortest connection between two specified stations.
	Conn_t ConnectionFromTo(LinkedSt_t &fromSt, LinkedSt_t &toSt, DijkstraGraph& graph);

	// Finds two stations with the most price difference and then the shortest connection between them.
	Conn_t MostPriceDiffConnection(
		DijkstraGraph& graph, 
		double minPriceDiff=defaults::DEF_MIN_PRICE_DIFF
	);
	
	// Finds a station with the most price difference and then the shortest connection between it and the fromSt.
	Conn_t MostPriceDiffConnectionFrom(
		LinkedSt_t& fromSt,
		DijkstraGraph& graph,
		double maxDist = defaults::DEF_MAX_DIST,
		double minPriceDiff = defaults::DEF_MIN_PRICE_DIFF
	);

	// Finds all shortest connections from fromSt and then finds the one with the most profit.
	Conn_t MostProfitConnectionFrom(
		LinkedSt_t &fromSt,
		DijkstraGraph& graph,
		double maxDist = defaults::DEF_MAX_DIST,
		double minProfit = defaults::DEF_MIN_PROFIT
	);
} }
