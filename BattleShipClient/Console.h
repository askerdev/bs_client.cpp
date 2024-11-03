#pragma once
#include "Packet.h"
#include <string>
#include <utility>

class Console
{
public:
	static void PrintCommands();
	static void PrintGameCommands();
	static std::string PromptString(const std::string& msg = "");
	static int PromptInt(const std::string& msg = "");
	static net::MsgType PromptCommand();
	static core::Orientation PromptOrientation();
	static core::ShipType PromptShipType();
	static std::pair<int, int> PromptCoordinates(const std::string& msg = "Enter coordinates ( A1, B3 )");
	static net::Ship PromptShip();
	static int LetterToInt(const char);
};

