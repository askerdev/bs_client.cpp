#pragma once
#include <string>
#include <vector>

namespace core
{
	enum CellState
	{
		BLOWN = 0,
		HIT = 1,
		FREE = 2,
		MISS = 3,
		SHIP = 4,
	};

	enum ShipType
	{
		BOAT = 1,
		DESTROYER = 2,
		CRUISER = 3,
		BATTLESHIP = 4,
	};

	enum Orientation
	{
		UNKNOWN = 0,
		HORIZONTAL = 1,
		VERTICAL = 2,
	};
}

template <typename T>
std::string join(const std::vector<T>& in, const std::string& sep = ",");

std::vector<std::string> split(const std::string& in, const char sep = ',');