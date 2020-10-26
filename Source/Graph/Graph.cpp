#include "Graph.h"

#include <iostream>
#include <vector>
#include <string>

#include <Graph/Types.h>

namespace Station { namespace Graph
{
	Graph::Graph(std::vector<LinkedStRef_t> stations)
	{
		setStations(stations);
		visited_.reserve(stations_.size());
		for (LinkedSt_t& st : stations_)
		{
			visited_[&st] = false;
		}
	}

	void Graph::Refresh()
	{
		for (auto entry : visited_)
		{
			entry.second = false;
		}
	}

	void Graph::setStations(std::vector<LinkedStRef_t> stations)
	{
		stations_.assign(stations.begin(), stations.end());
	}

	std::vector<std::reference_wrapper<LinkedSt_t>> Graph::getStations()
	{
		return stations_;
	}

	bool Graph::hasStation(const LinkedSt_t& st) const
	{
		bool hasSt = false;
		auto it = std::find(stations_.begin(), stations_.end(), std::ref(st));
		return it != stations_.end() ? true : false;
	}

	bool Graph::isVisited(size_t i) const
	{
		return isVisited(stations_[i]);
	}

	bool Graph::isVisited(const LinkedSt_t& st) const
	{
		return visited_.at(&const_cast<LinkedSt_t&>(st));
	}

	bool Graph::isVisited(std::string& name) const
	{
		size_t i = 0;
		for (auto st : stations_)
		{
			if (name == st.get().getName())
			{
				break;
			}
			i++;
		}

		if (i == stations_.size())
		{
			throw std::runtime_error("Station is not in graph.");
		}

		return isVisited(i);
	}

	void Graph::setVisited(size_t i)
	{
		visited_[&stations_[i].get()] = true;
	}

	void Graph::setVisited(LinkedSt_t& st)
	{
		visited_[&const_cast<LinkedSt_t&>(st)] = true;
	}

	void Graph::setVisited(std::string name)
	{
		size_t i = 0;
		for (auto st : stations_)
		{
			if (name == st.get().getName())
			{
				setVisited(st);
				break;
			}
			i++;
		}

		if (i == stations_.size())
		{
			throw std::runtime_error("Station is not in graph.");
		}
	}
}}
