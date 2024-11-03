#pragma once
#include "Cell.h"
#include "types.h"
#include <string>
#include <utility>
#include <vector>

#define TOTAL_PACKET_SIZE 4100
#define PACKET_HEADERS_SIZE 4
#define PACKET_BODY_SIZE 4096

namespace net
{
	enum MsgType
	{
		STATE = 0,
		JOIN = 1,
		MOVE = 2,
		EXIT = 3,
		PLACESHIP = 4,
		INFO = 5,
	};

	struct Packet
	{
		MsgType type;
		std::string body;
	};

	struct Ship
	{
		core::ShipType type;
		core::Orientation orientation;
		std::pair<int, int> coords;
	};

	std::string Marshal(net::Packet packet);

	net::Packet Unmarshal(std::string in);

	std::pair<std::vector<Cell>, std::vector<Cell>> ParseState(net::Packet);

	Cell ParseCell(const std::string&);
}
