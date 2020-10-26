#include "LinkData.h"

#include <iostream>

namespace Station { namespace Model
{ 
	LinkData::LinkData(double dist)
	{
		setDist(dist);
	}

	void LinkData::setDist(double dist)
	{
		if (dist < 0)
		{
			throw std::runtime_error("Distance is less than zero.");
		}
		dist_ = dist;
	}

	double LinkData::getDist() const
	{
		return dist_;
	}
}}
