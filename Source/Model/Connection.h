#pragma once

#include <vector>
#include <array>

#include <Model/LinkedStation.h>

namespace Station { namespace Model
{
	// Class Connection holds a sequence of linked stations and provides methods for obtaining various numeric data.
	class Connection
	{
	private:
	public:
		std::vector<LinkedStation*> points;

		Connection();

		double Distance() const;
		std::array<LinkedStation*, 2> EndPoints();

		// First price difference is "buy at start -> sell at end", second "buy at end -> sell at start".
		std::array<double, 2> PriceDiff();

		// Profit is a price difference per unit of distance. 
		std::array<double, 2> Profit();

		void AddPoint(LinkedStation* point);
		double MaxPriceDiff();
		double MaxProfit();
		double MinLoss();
		const LinkedStation* Start();
		const LinkedStation* End();

		// Has no points.
		bool isEmpty() const;

		// Has one or zero points.
		bool isValid() const;

	};

	bool operator==(const Connection& lhs, const Connection& rhs);
	bool operator!=(const Connection& lhs, const Connection& rhs);
}}

