#include "CircularBuffer.h"
#include "Client.h"
#include "Packet.h"
#include <iomanip>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <thread>
#include <unordered_map>
#include <winsock2.h>
#include <ws2tcpip.h>

#define STDIN 0

Client::Client(net::Socket sock) :
	sock(sock)
{}

void Client::SetupWorker()
{
	this->worker = std::thread(&Client::Worker, this);
}

void Client::Start(const std::string& host)
{
	sock.Connect(host, 8080);

	fd_set master{};
	fd_set read_fds{};

	FD_ZERO(&read_fds);
	FD_ZERO(&master);

	FD_SET(sock.GetFD(), &master);

	OnConnect();
	SetupWorker();

	net::CircularBuffer<char> buf(4101);

	while (true)
	{
		while (packetQueue.size())
		{
			OnMessage(packetQueue.front());
			packetQueue.pop();
		}

		read_fds = master;

		if (select(sock.GetFD() + 1, &read_fds, NULL, NULL, NULL) == -1)
		{
			throw std::invalid_argument("while select");
		}

		if (!FD_ISSET(sock.GetFD(), &read_fds))
		{
			continue;
		}

		try
		{
			std::string data;
			sock >> data;

			for (auto& symbol : data)
			{
				buf << symbol;
				if (symbol == ';')
				{
					std::string chunk;
					do
					{
						chunk += buf.Read();
					} while (chunk.back() != ';');
					try
					{
						packetQueue.push(net::Unmarshal(chunk));
					} catch (const std::exception&)
					{
						continue;
					}
				}
			}

		} catch (const std::exception&)
		{
			OnDisconnect();
			FD_CLR(sock.GetFD(), &master);
			break;
		}
	}
}
