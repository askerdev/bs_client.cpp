#pragma once
#include "Client.h"
#include "Packet.h"
#include "types.h"
#include <mutex>
#include <utility>
#include <vector>

class Application : public Client
{
public:
	Application();
	void Main();

	virtual void Worker() override;
	virtual void OnConnect() override;
	virtual void OnMessage(net::Packet) override;
	virtual void OnDisconnect() override;

	void Render(std::pair<std::vector<Cell>, std::vector<Cell>>);
};

