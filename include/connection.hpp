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
		~Connection();
		void connect();
		void write(std::string message);
		void close();
		const bool isConnected() const {return isConnected_;};
		const std::string getUsername()const {return username_;} 

	private:
		void read();
		void readUsername();
		void broadcast();
		bool isSocket;
		std::string message_;
		std::string username_;

		asio::ip::tcp::socket socket_;
		Server& server_;
		bool isConnected_;
};
