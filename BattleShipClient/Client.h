#pragma once
#include "Packet.h"
#include "Socket.h"
#include <memory>
#include <mutex>
#include <queue>
#include <string>
#include <thread>
#include <utility>

class Client
{
public:
	Client(net::Socket);

	void Start(const std::string& host);
	void SetupWorker();

	virtual void Worker() = 0;
	virtual void OnConnect() = 0;
	virtual void OnMessage(net::Packet) = 0;
	virtual void OnDisconnect() = 0;
protected:
	std::queue<net::Packet> packetQueue;
	net::Socket sock;
private:
	std::thread worker;
};