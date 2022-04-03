#pragma once
#include<memory>
#include<string>
#include <asio.hpp>
#include <iostream>
#include <server.hpp>
/*
 * its takes care of the connection betwen client and server
 *
 */
class Server;

class Connection: public std::enable_shared_from_this<Connection>
{
	public:
		Connection(asio::ip::tcp::socket socket, Server& server);
		void connect();
		void write(std::string message);
		const bool isConnected() const {return isConnected_;};
		void close();

	private:
		void read();
		void readUsername();
		void broadcast();
		std::string message_;
		std::string username_;

		asio::ip::tcp::socket socket_;
		Server& server_;
		bool isConnected_;
};
