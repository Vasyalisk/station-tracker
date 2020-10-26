#include "LinkedStation.h"

#include <string>
#include <iostream>

#include <Model/Types.h>

namespace Station { namespace Model
{
	LinkedStation::LinkedStation(Station& st)
		:Station(st.getName(), st.buyPrice, st.sellPrice)
	{
	}

	double LinkedStation::DistanceTo(const LinkedStation& other) const
	{
		auto link = const_cast<LinkedStation*>(this)->FindLink(const_cast<LinkedStation&>(other));
		return link.second.getDist();
	}

	bool LinkedStation::hasLinkTo(const LinkedStation& other) const
	{
		auto name = other.getName();
		return hasLinkTo(name);
	}

	bool LinkedStation::hasLinkTo(std::string& other) const
	{
		auto CompareName = [&](Link_t link) { return link.first->getName() == other; };
		auto it = std::find_if(links.begin(), links.end(), CompareName);

		bool hasLink = false;
		if (it != links.end())
		{
			hasLink = true;
		}

		return hasLink;
	}

	LinkRef_t LinkedStation::FindLink(LinkedStation& other)
	{
		if (&other == this)
		{
			throw std::runtime_error("These are the same stations.");
		}

		auto CompareLink = [&](Link_t& link) { return link.first == &other; };
		auto it = std::find_if(links.begin(), links.end(), CompareLink);

		if (it == links.end())
		{
			throw std::runtime_error("The stations are not linked");
		}

		return LinkRef_t{ (*it).first, (*it).second };
	}

	void LinkedStation::AddLink(LinkedStation& other, LinkData lData)
	{
		if (other == *this)
		{
			throw std::runtime_error("Can't link the station to itself.");
		}

		links.push_back({ &other, lData });
		other.links.push_back({ this, lData });
	}

	void LinkedStation::DeleteLink(LinkedStation& other)
	{
		auto CompareLink = [](Link_t& link, LinkedStation* st) { return link.first == st; };

		auto CompareOther = [&](Link_t& link) { return CompareLink(link, this); };
		auto otherIt = std::find_if(other.links.begin(), other.links.end(), CompareOther);

		auto CompareLocal = [&](Link_t& link) { return CompareLink(link, &other); };
		auto localIt = std::find_if(links.begin(), links.end(), CompareLocal);

		if (otherIt == other.links.end() || localIt == links.end())
		{
			throw std::runtime_error("Link doesn't exist");
		}

		other.links.erase(otherIt);
		links.erase(localIt);
	}
}}