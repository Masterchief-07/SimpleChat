#pragma once
#include<memory>
#include<string>
#include <asio.hpp>
#include <iostream>
/*
 * its takes care of the connection betwen client and server
 *
 */

class Connection: public std::enable_shared_from_this<Connection>
{
	public:
		Connection(asio::ip::tcp::socket socket);
		void read();

	private:
		void write();
		void broadcast();
		std::string message_;
		std::string username_;

		asio::ip::tcp::socket socket_;
};
