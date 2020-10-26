#include "DijkstraGraph.h"

#include <vector>
#include <iostream>
#include <queue>

#include <Graph/Graph.h>
#include <Graph/Types.h>

namespace Station { namespace Graph
{
	void DijkstraGraph::DijkstraAlgorithm(double maxDist)
	{
		typedef std::pair<std::reference_wrapper<LinkedSt_t>, double> StackPair_t;

		class ComparePairs
		{
		public:
			bool operator() (const StackPair_t lhs, const StackPair_t rhs) const
			{
				return std::greater<double>()(lhs.second, rhs.second);
			}
		};

		std::priority_queue<StackPair_t, std::vector<StackPair_t>, ComparePairs> stack;
		ConnectionTo(*fromSt_).points.push_back(fromSt_);
		stack.push(StackPair_t{ std::ref(*fromSt_), 0 });

		while (!stack.empty())
		{
			// Choosing top node from stack
			LinkedSt_t& st = stack.top().first;
			stack.pop();

			// Passing visited nodes
			if (isVisited(st) || ConnectionTo(st).Distance() > maxDist)
			{
				continue;
			}
			else
			{
				setVisited(st);
			}

			// Adding child nodes to stack
			for (auto link : st.links)
			{
				Conn_t* conTo = &ConnectionTo(*link.first);
				Conn_t newCon = ConnectionTo(st);
				newCon.AddPoint(link.first);
				double newDist = newCon.Distance();

				if (newCon.Distance() > maxDist)
				{
					continue;
				}

				if (conTo->isEmpty())
				{
					conTo->points = newCon.points;
					stack.push(StackPair_t{ *link.first, newDist });
				}
				else if (newDist < conTo->Distance())
				{
					conTo->points = newCon.points;
					stack.push({ *link.first, newDist });
				}
			}
		}
	}

	DijkstraGraph::DijkstraGraph(std::vector<LinkedStRef_t> stations)
		:Graph(stations)
	{
		if (stations.empty())
		{
			throw std::runtime_error("There are no stations.");
		}

		fromSt_ = &stations.front().get();
		connectionMap_.reserve(stations.size());
		for (auto &st : stations)
		{
			connectionMap_[&st.get()] = Conn_t{};
		}

		hasConnections_ = false;
	}

	void DijkstraGraph::GenerateConnections(LinkedSt_t &fromSt, double maxDist)
	{
		auto stations_ = getStations();
		auto it = std::find(stations_.begin(), stations_.end(), std::ref(fromSt));
		if (it == stations_.end())
		{
			throw std::runtime_error("Station not in graph.");
		}
		else if (maxDist <= 0)
		{
			throw std::runtime_error("Max distance should be greater than zero.");
		}
		fromSt_ = &fromSt;

		DijkstraAlgorithm(maxDist);
		hasConnections_ = true;
	}

	std::unordered_map<LinkedSt_t*, Conn_t> DijkstraGraph::Connections() const
	{
		return connectionMap_;
	}

	const LinkedSt_t& DijkstraGraph::FromStation() const
	{
		const auto &newRef = *fromSt_;
		return newRef;
	}

	bool DijkstraGraph::hasConnections() const
	{
		return hasConnections_;
	}

	void DijkstraGraph::Refresh()
	{
		Graph::Refresh();
		for (auto entry : connectionMap_)
		{
			entry.second = Conn_t{};
		}
	}

	Conn_t & DijkstraGraph::ConnectionTo(LinkedSt_t& st)
	{
		return connectionMap_[&st];
	}
}}
