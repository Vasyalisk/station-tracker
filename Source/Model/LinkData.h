#pragma once

namespace Station { namespace Model
{
	// Contains distance of the link between stations. Can be extended to provide additional info.
	class LinkData
	{
	private:
		double dist_;
	public:
		LinkData(double dist);

		// Throws an error if dist is less or equal than zero.
		void setDist(double dist);
		double getDist() const;
	};
}}

