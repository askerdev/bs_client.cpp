#include "Console.h"
#include "types.h"
#include <exception>
#include <iomanip>
#include <iostream>
#include <string>
#include <utility>

void Console::PrintCommands()
{
	std::cout << std::setw(32) << std::right << "MENU" << std::endl;
	std::cout << "1: Join a game" << std::endl;
	std::cout << "2: Shoot" << std::endl;
	std::cout << "3: EXIT" << std::endl;
	std::cout << "4: Place ship" << std::endl;
}

void Console::PrintGameCommands()
{
	std::cout << std::setw(32) << std::right << "MENU" << std::endl;
	std::cout << "2: Shoot" << std::endl;
	std::cout << "4: Place ship" << std::endl;
}

std::string Console::PromptString(const std::string& msg)
{
	std::cout << msg << " " << ">> ";
	std::string in;
	std::cin >> in;
	return in;
}

int Console::PromptInt(const std::string& msg)
{
	while (true)
	{
		try
		{
			const auto& str = Console::PromptString(msg);
			return std::stoi(str);
		} catch (const std::exception&)
		{
			std::cout << "invalid value! try again." << std::endl;
		}
	}
}

net::MsgType Console::PromptCommand()
{
	while (true)
	{
		try
		{
			auto cmd = Console::PromptString("Enter command");
			switch (cmd[0])
			{
			case '1':
				return net::MsgType::JOIN;
			case '2':
				return net::MsgType::MOVE;
			case '3':
				return net::MsgType::EXIT;
			case '4':
				return net::MsgType::PLACESHIP;
			default:
				std::cout << "invalid answer! try again" << std::endl;
				continue;
			}
		} catch (const std::exception&)
		{
			std::cout << "invalid answer! try again" << std::endl;
			continue;
		}
	}
}

core::Orientation Console::PromptOrientation()
{
	while (true)
	{
		try
		{
			auto cmd = Console::PromptString("Orientation (1 - Horizontal, 2 - Vertical)");
			switch (cmd[0])
			{
			case '1':
				return core::Orientation::HORIZONTAL;
			case '2':
				return core::Orientation::VERTICAL;
			default:
				std::cout << "invalid answer! try again" << std::endl;
				continue;
			}
		} catch (const std::exception&)
		{
			std::cout << "invalid answer! try again" << std::endl;
			continue;
		}
	}
}

core::ShipType Console::PromptShipType()
{
	while (true)
	{
		try
		{
			auto cmd = Console::PromptString("Enter ship length (range 1-4)");
			switch (cmd[0])
			{
			case '1':
				return core::ShipType::BOAT;
			case '2':
				return core::ShipType::DESTROYER;
			case '3':
				return core::ShipType::CRUISER;
			case '4':
				return core::ShipType::BATTLESHIP;
			default:
				std::cout << "invalid answer! try again" << std::endl;
				continue;
			}
		} catch (const std::exception&)
		{
			std::cout << "invalid answer! try again" << std::endl;
			continue;
		}
	}
}

int Console::LetterToInt(const char letter)
{
	return letter - 'A' + 1;
}

std::pair<int, int> Console::PromptCoordinates(const std::string& msg)
{
	while (true)
	{
		try
		{
			auto coords = Console::PromptString(msg);
			int x = LetterToInt(coords[0]);
			int y = std::stoi(coords.substr(1));
			if (x <= 0 || y <= 0 || x > 10 || y > 10)
				throw std::exception();
			return { x - 1, y - 1 };
		} catch (const std::exception&)
		{
			std::cout << "invalid answer! try again" << std::endl;
			continue;
		}
	}
}

net::Ship Console::PromptShip()
{
	while (true)
	{
		try
		{
			std::pair<int, int> coords = Console::PromptCoordinates("Enter left top coordinates of your ship ( A1, B3 )");
			core::ShipType type = Console::PromptShipType();
			core::Orientation orientation;
			if (type == core::ShipType::BOAT)
			{
				orientation = core::Orientation::UNKNOWN;
			} else
			{
				orientation = Console::PromptOrientation();
			}
			return { type,orientation,coords };
		} catch (const std::exception&)
		{
			std::cout << "invalid answer! try again" << std::endl;
			continue;
		}
	}
}
