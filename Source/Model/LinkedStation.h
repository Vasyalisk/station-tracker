#pragma once

#include <vector>

#include <Model/Station.h>
#include <Model/Types.h>

namespace Station { namespace Model
{
	// Station with links to other stations
	class LinkedStation : public Station
	{
	public:

		LinkedStation(Station& st);
		using Station::Station;

		double DistanceTo(const LinkedStation& other) const;
		bool hasLinkTo(const LinkedStation& other) const;
		bool hasLinkTo(std::string& other) const;
		LinkRef_t FindLink(LinkedStation& other);
		void AddLink(LinkedStation& other, LinkData lData);
		void DeleteLink(LinkedStation& other);
		std::vector<Link_t> links;
	};
}}

