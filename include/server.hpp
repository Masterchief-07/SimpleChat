#pragma once
//#define ASIO_STANDALONE
//#define BOOST_ASIO_STANDALONE
#include <connection.hpp>
#include <asio.hpp>
#include <set>
#include <iostream>

class Connection;
typedef std::shared_ptr<Connection> ConnectionPtr ;
typedef std::set<ConnectionPtr> ConnectionSet;
class Server
{
	public:
		Server() noexcept;
		void start();
		void sendTo(std::string message, ConnectionPtr connect);
		void sendToAll(std::string message);
		void leave(ConnectionPtr connect);

	private:
		void run();
		void accept();
		asio::io_context io_;
		asio::ip::tcp::acceptor acceptor_;
		//std::string message_;
		//std::unique_ptr<std::thread> ioThr_;
		ConnectionSet connectSet_;


};
