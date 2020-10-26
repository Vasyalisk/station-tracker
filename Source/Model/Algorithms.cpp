#include "Algorithms.h"

#include <Graph/DijkstraGraph.h>
#include <Graph/Algorithms.h>

namespace Station { namespace Model
{
	namespace StGraph = ::Station::Graph;

	Connection ConnectionFromTo(LinkedStation& fromSt, LinkedStation& toSt, std::vector<LinkedStRef_t> stations)
	{
		StGraph::DijkstraGraph graph{ stations };
		graph.GenerateConnections(fromSt);
		return StGraph::ConnectionFromTo(fromSt, toSt, graph);
	}

	Connection ConnectionFromTo(LinkedStation& fromSt, LinkedStation& toSt, std::list<LinkedStation>& stations)
	{
		std::vector<LinkedStRef_t> v;
		v.assign(stations.begin(), stations.end());
		return ConnectionFromTo(fromSt, toSt, v);
	}

	Connection MostPriceDiffConnectionFrom(LinkedStation& fromSt, std::vector<LinkedStRef_t> stations, double maxDist, double minPriceDiff)
	{
		StGraph::DijkstraGraph graph{ stations };
		graph.GenerateConnections(fromSt, maxDist);
		return StGraph::MostPriceDiffConnectionFrom(fromSt, graph, maxDist, minPriceDiff);
	}

	Connection MostPriceDiffConnectionFrom(LinkedStation& fromSt, std::list<LinkedStation>& stations, double maxDist, double minPriceDiff)
	{
		std::vector<LinkedStRef_t> v;
		v.assign(stations.begin(), stations.end());
		return MostPriceDiffConnectionFrom(fromSt, v, maxDist, minPriceDiff);
	}

	Connection MostPriceDiffConnection(std::list<LinkedStation>& stations, double minPriceDiff)
	{
		std::vector<LinkedStRef_t> v;
		v.assign(stations.begin(), stations.end());
		return MostPriceDiffConnection(v, minPriceDiff);
	}

	Connection MostPriceDiffConnection(std::vector<LinkedStRef_t> stations, double minPriceDiff)
	{
		StGraph::DijkstraGraph graph{ stations };
		return StGraph::MostPriceDiffConnection(graph, minPriceDiff);
	}

	Connection MostProfitConnectionFrom(LinkedStation& fromSt, std::vector<LinkedStRef_t> stations, double maxDist, double minProfit)
	{
		StGraph::DijkstraGraph graph{ stations };
		graph.GenerateConnections(fromSt, maxDist);
		return StGraph::MostProfitConnectionFrom(fromSt, graph, maxDist, minProfit);
	}
	Connection MostProfitConnectionFrom(LinkedStation& fromSt, std::list<LinkedStation>& stations, double maxDist, double minProfit)
	{
		std::vector<LinkedStRef_t> v;
		v.assign(stations.begin(), stations.end());
		return MostProfitConnectionFrom(fromSt, v, maxDist, minProfit);
	}
}}
