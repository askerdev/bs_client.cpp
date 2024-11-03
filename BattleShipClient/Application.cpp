#include "Application.h"
#include "CircularBuffer.h"
#include "Client.h"
#include "Console.h"
#include "Packet.h"
#include "Socket.h"
#include <iomanip>
#include <iostream>
#include <mutex>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>


Application::Application()
	: Client(net::Socket())
{}

void Application::Main()
{
	std::cout << "Input server ip: ";
	std::string host;
	std::getline(std::cin, host);
	try
	{
		Start(host);
	} catch (const std::exception&)
	{
		std::cout << "Server on that ip is not available" << std::endl;
	}
}

void Application::Render(std::pair<std::vector<Cell>, std::vector<Cell>> boards)
{
	system("cls");
	std::vector<std::vector<core::CellState>> lmatrix{
		10,
		std::vector<core::CellState>(10, core::CellState::FREE),
	};
	for (auto& cell : boards.first)
	{
		lmatrix[cell.y][cell.x] = cell.state;
	}
	std::vector<std::vector<core::CellState>> rmatrix{
		10,
		std::vector<core::CellState>(10, core::CellState::FREE),
	};
	for (auto& cell : boards.second)
	{
		rmatrix[cell.y][cell.x] = cell.state;
	}


	for (int c = 0; c < 2; c++)
	{
		std::cout << std::setw(3) << "";
		for (char letter = 'A'; letter < 'A' + 10; letter++)
		{
			std::cout << letter << " ";
		}
		std::cout << " ";
	}
	std::cout << std::endl;

	for (int y = 0; y < 10; y++)
	{
		std::cout << std::setw(2) << y + 1 << " ";
		for (int x = 0; x < 10; x++)
		{
			core::CellState cell = lmatrix[y][x];
			switch (cell)
			{
			case core::CellState::FREE:
				std::cout << "_";
				break;
			case core::CellState::BLOWN:
				std::cout << "X";
				break;
			case core::CellState::HIT:
				std::cout << "#";
				break;
			case core::CellState::MISS:
				std::cout << "o";
				break;
			case core::CellState::SHIP:
				std::cout << "s";
				break;
			}
			std::cout << " ";
		}
		std::cout << " ";
		std::cout << std::setw(2) << y + 1 << " ";
		for (int x = 0; x < 10; x++)
		{
			core::CellState cell = rmatrix[y][x];
			switch (cell)
			{
			case core::CellState::FREE:
				std::cout << "_";
				break;
			case core::CellState::BLOWN:
				std::cout << "X";
				break;
			case core::CellState::HIT:
				std::cout << "#";
				break;
			case core::CellState::MISS:
				std::cout << "o";
				break;
			case core::CellState::SHIP:
				std::cout << "s";
				break;
			}
			std::cout << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

void Application::Worker()
{
	while (true)
	{
		auto cmd = Console::PromptCommand();
		if (cmd == net::MsgType::JOIN)
		{
			auto id = Console::PromptInt("Enter game id");
			sock << net::Marshal({
				cmd,
				std::to_string(id),
				});
		} else if (cmd == net::MsgType::MOVE)
		{
			auto coords = Console::PromptCoordinates();
			sock << net::Marshal({
				cmd,
				std::to_string(coords.first) + std::to_string(coords.second),
				});
		} else if (cmd == net::MsgType::PLACESHIP)
		{
			auto ship = Console::PromptShip();
			sock << net::Marshal({
				cmd,
				std::to_string(ship.orientation) + std::to_string(ship.type) + std::to_string(ship.coords.first) + std::to_string(ship.coords.second),
				});
		}
	}
}

void Application::OnConnect()
{
	system("cls");
	Console::PrintCommands();
}

void Application::OnMessage(net::Packet packet)
{
	switch (packet.type)
	{
	case net::MsgType::STATE:
		Render(net::ParseState(packet));
		Console::PrintGameCommands();
		break;
	case net::MsgType::INFO:
		std::cout << "INFO: " << packet.body << std::endl;
		break;
	}
}

void Application::OnDisconnect()
{
	std::cout << "disconnected" << std::endl;
}

