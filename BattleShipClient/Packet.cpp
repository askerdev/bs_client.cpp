#include "Packet.h"
#include "types.h"
#include <iostream>
#include <stdexcept>
#include <string>

std::string net::Marshal(net::Packet packet)
{
	return std::to_string(packet.type) + packet.body + ";";
}

net::Packet net::Unmarshal(std::string in)
{
	net::MsgType type;

	switch (in[0])
	{
	case '0':
		type = net::MsgType::STATE;
		break;
	case '1':
		type = net::MsgType::JOIN;
		break;
	case '2':
		type = net::MsgType::MOVE;
		break;
	case '3':
		type = net::MsgType::EXIT;
		break;
	case '4':
		type = net::MsgType::PLACESHIP;
		break;
	case '5':
		type = net::MsgType::INFO;
		break;
	default:
		throw std::invalid_argument("invlaid data");
	}
	return{ type, in.substr(1, in.size() - 2) };
}

Cell net::ParseCell(const std::string& data)
{
	if (data.size() != 3)
	{
		throw std::invalid_argument("invalid cell");
	}

	int x = data[0] - '0';
	int y = data[1] - '0';

	core::CellState state;
	switch (data[2])
	{
	case '0':
		state = core::CellState::BLOWN;
		break;
	case '1':
		state = core::CellState::HIT;
		break;
	case '2':
		state = core::CellState::FREE;
		break;
	case '3':
		state = core::CellState::MISS;
		break;
	case '4':
		state = core::CellState::SHIP;
		break;
	default:
		throw std::invalid_argument("invalid cell");
	}

	return { x, y, state };
}

std::pair<std::vector<Cell>, std::vector<Cell>> net::ParseState(net::Packet packet)
{
	if (packet.type != net::MsgType::STATE)
	{
		throw std::invalid_argument("invalid packet type");
	}

	packet.body.erase(0, 1);
	packet.body.erase(packet.body.size() - 1, 1);

	std::vector<std::string> boards = split(packet.body, '|');
	std::vector<Cell> self;
	std::vector<Cell> opponent;

	if (boards.size() > 0)
	{
		for (auto rawCell : split(boards[0], ','))
		{
			self.push_back(ParseCell(rawCell));
		}
	}
	if (boards.size() == 2)
	{
		for (auto rawCell : split(boards[1], ','))
		{
			opponent.push_back(ParseCell(rawCell));
		}
	}
	return { self,opponent };
}