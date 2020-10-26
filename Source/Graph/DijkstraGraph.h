#pragma once

#include <unordered_map>
#include <vector>

#include <Graph/Types.h>
#include <Graph/Graph.h>
#include <Model/Constants.h>

namespace Station { namespace Graph
{
	namespace StModel = Station::Model;

	// Graph which keeps track of visited nodes (stations) and supports Dijkstra algorithm for finding shortest connections from specified
	// station.
	class DijkstraGraph : public Station::Graph::Graph
	{
	private:
		std::unordered_map<LinkedSt_t*, Conn_t> connectionMap_;
		LinkedSt_t * fromSt_;
		bool hasConnections_;

		void DijkstraAlgorithm(double maxDist);
	public:

		DijkstraGraph(std::vector<LinkedStRef_t> stations);

		// Generate connections using underlying Dijkstra algorithm
		void GenerateConnections(LinkedSt_t &fromSt, double maxDist=StModel::detail::DEF_MAX_DIST);
		std::unordered_map<LinkedSt_t*, Conn_t> Connections() const;
		const LinkedSt_t& FromStation() const;
		bool hasConnections() const;

		// Clear all connections
		void Refresh();
		Conn_t & ConnectionTo(LinkedSt_t &st);
	};
}}

