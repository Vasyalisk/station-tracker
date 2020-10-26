#pragma once

#include <vector>
#include <unordered_map>
#include <string>
#include <functional>

#include <Graph/Types.h>

namespace Station { namespace Graph
{
	// Basic graph to keep track of visited nodes (stations).
	class Graph
	{
	private:
		std::unordered_map<LinkedSt_t*, bool> visited_;
		std::vector<LinkedStRef_t> stations_;
	public:

		Graph(std::vector<LinkedStRef_t> stations);

		void Refresh();
		void setStations(std::vector<LinkedStRef_t> stations);
		std::vector<LinkedStRef_t> getStations();
		bool hasStation(const LinkedSt_t& st) const;

		bool isVisited(size_t i) const;
		bool isVisited(const LinkedSt_t& st) const;
		bool isVisited(std::string& name) const;

		void setVisited(size_t i);
		void setVisited(LinkedSt_t &st);
		void setVisited(std::string name);
	};
}}
