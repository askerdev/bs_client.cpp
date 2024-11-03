#pragma once
#include "Packet.h"
#include <memory>
#include <string>
#include <winsock2.h>

namespace net
{
	class Socket
	{
	public:
		Socket() = default;
		Socket(SOCKET);
		~Socket();

		void Listen(const int&);
		void Connect(const std::string&, const int&);

		std::shared_ptr<net::Socket> Accept();
		SOCKET GetFD();

		friend net::Socket& operator<<(net::Socket&, const std::string&);
		friend net::Socket& operator>>(net::Socket&, std::string&);
	private:
		SOCKET fd;
	};
}