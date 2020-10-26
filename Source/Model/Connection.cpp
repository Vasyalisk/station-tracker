#include "Connection.h"

#include <limits>
#include <cmath>
#include <string>
#include <iostream>

#include <Model/LinkedStation.h>

namespace Station { namespace Model
{
	Connection::Connection()
	{
		points = std::vector<LinkedStation*>{};
	}

	double Connection::Distance() const
	{
		if (points.size() <= 1)
		{
			return 0.0;
		}

		double d = 0;
		const LinkedStation* pSt1 = points.at(0);
		const LinkedStation* pSt2;
		for (size_t i = 1; i < points.size(); i++)
		{
			pSt2 = points.at(i);
			d += pSt2->DistanceTo(*pSt1);
			pSt1 = pSt2;
		}
		return d;
	}

	std::array<LinkedStation*, 2> Connection::EndPoints()
	{
		return { points.at(0), points.at(points.size() - 1) };
	}

	std::array<double, 2> Connection::Profit()
	{
		double dist = Distance();
		auto difAr = PriceDiff();
		return { difAr[0] / dist, difAr[1] / dist };
	}

	std::array<double, 2> Connection::PriceDiff()
	{
		if (!isEmpty())
		{
			double buy1 = points[0]->buyPrice, sell1 = points[0]->sellPrice;
			double buy2 = points.back()->buyPrice, sell2 = points.back()->sellPrice;
			return { sell2 - buy1, sell1 - buy2 };
		}
		else
		{
			constexpr double nan_ = std::numeric_limits<double>::quiet_NaN();
			return { nan_, nan_ };
		}
	}

	void Connection::AddPoint(LinkedStation* point)
	{
		auto it = std::find(points.begin(), points.end(), point);
		if (it == points.end() - 1)
		{
			throw std::runtime_error("Duplicate end points are not allowed.");
		}
		points.push_back(point);
	}

	double Connection::MaxPriceDiff()
	{
		auto difAr = PriceDiff();
		double onSell = difAr[0], onBuy = difAr[1];
		if (std::isnan(onSell))
		{
			return onBuy;
		}
		else if (std::isnan(onBuy))
		{
			return onSell;
		}
		else
		{
			return onSell > onBuy ? onSell : onBuy;
		}
	}

	double Connection::MaxProfit()
	{
		return MaxPriceDiff() / Distance();
	}

	double Connection::MinLoss()
	{
		double minLoss = 1 / MaxProfit();

		if (minLoss < 0 || isnan(minLoss))
		{
			minLoss = std::numeric_limits<double>::infinity();
		}

		return minLoss;
	}

	const LinkedStation* Connection::Start()
	{
		return points[0];
	}

	const LinkedStation* Connection::End()
	{
		return points[points.size() - 1];
	}

	bool Connection::isEmpty() const
	{
		return points.empty();
	}

	bool Connection::isValid() const
	{
		return points.size() > 1;
	}
}

	bool Model::operator==(const Connection& lhs, const Connection& rhs)
	{
		bool isEqual = true;
		if (lhs.points.size() != rhs.points.size())
		{
			isEqual = false;
		}
		else
		{
			for (size_t i = 0; i < lhs.points.size(); i++)
			{
				auto& p1 = *lhs.points[i], & p2 = *rhs.points[i];
				if (p1 != p2)
				{
					isEqual = false;
					break;
				}
			}
		}
		return isEqual;
	}

	bool Model::operator!=(const Connection& lhs, const Connection& rhs)
	{
		return !(lhs == rhs);
	}
}