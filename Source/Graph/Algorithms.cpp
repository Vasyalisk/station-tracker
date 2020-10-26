#include "Algorithms.h"

#include <iostream>

#include <Graph/DijkstraGraph.h>

namespace Station {	namespace Graph
{
	Conn_t ConnectionFromTo(LinkedSt_t& fromSt, LinkedSt_t& toSt, DijkstraGraph& graph)
	{
		if (!graph.hasStation(fromSt) || !graph.hasStation(toSt))
		{
			throw std::runtime_error("One of the stations is not in graph.");
		}

		Conn_t result{};

		if (!graph.hasConnections())
		{
			graph.GenerateConnections(fromSt);
			result = graph.ConnectionTo(toSt);
		}
		else if (graph.FromStation() == fromSt)
		{
			result = graph.ConnectionTo(toSt);
		}
		else if (graph.FromStation() == toSt)
		{
			result = graph.ConnectionTo(fromSt);
		}
		return result;
	}

	Conn_t MostPriceDiffConnection(DijkstraGraph& graph, double minPriceDiff)
	{
		if (minPriceDiff < 0)
		{
			throw std::runtime_error("Price difference is less than zero.");
		}

		// Searching for stations with lowest buy price and highest sell price.
		double minBuy = std::numeric_limits<double>::infinity(), maxSell = 0, priceDiff = -1;
		LinkedSt_t* stBuy = nullptr, * stSell = nullptr;

		for (const auto st : graph.getStations())
		{
			double newBuy = st.get().buyPrice, newSell = st.get().sellPrice;
			if (newBuy < minBuy)
			{
				minBuy = newBuy;
				stBuy = &st.get();
			}
			if (newSell > maxSell)
			{
				maxSell = newSell;
				stSell = &st.get();
			}

			priceDiff = std::isinf(minBuy) ? priceDiff : maxSell - minBuy;
		}

		// Conditions "!stBuy || !stSell" are used to supress C6011 warning.
		Conn_t result{};
		if (priceDiff < minPriceDiff || !stBuy || !stSell)
		{
		}
		else if (stBuy == stSell)
		{
			result.points = { stBuy };
		}
		else
		{
			result = ConnectionFromTo(*stBuy, *stSell, graph);
		}
		return result;
	}

	Conn_t MostPriceDiffConnectionFrom(LinkedSt_t& fromSt, DijkstraGraph& graph, double maxDist, double minPriceDiff)
	{
		if (minPriceDiff < 0)
		{
			throw std::runtime_error("Price difference is less than zero.");
		}

		if (!graph.hasStation(fromSt))
		{
			throw std::runtime_error("Station not in graph.");
		}

		if (graph.FromStation() != fromSt || !graph.hasConnections())
		{
			graph.GenerateConnections(fromSt, maxDist);
		}

		Conn_t result{};
		double maxDiff = minPriceDiff;
		for (auto &con : graph.Connections())
		{
			double newDiff = con.second.MaxPriceDiff();
			if (newDiff >= maxDiff)
			{
				maxDiff = newDiff;
				result = con.second;
			}
		}
		return result;
	}

	Conn_t MostProfitConnectionFrom(LinkedSt_t& fromSt, DijkstraGraph& graph, double maxDist, double minProfit)
	{
		if (graph.FromStation() != fromSt || !graph.hasConnections())
		{
			graph.GenerateConnections(fromSt, maxDist);
		}

		Conn_t result{};
		double maxProfit = minProfit;
		for (auto con : graph.Connections())
		{
			double newProfit = con.second.MaxProfit();
			if (newProfit >= maxProfit && con.second.Distance() <= maxDist)
			{
				maxProfit = newProfit;
				result = con.second;
			}
		}
		return result;
	}
}}