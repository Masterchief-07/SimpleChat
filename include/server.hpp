#pragma once
//#define ASIO_STANDALONE
//#define BOOST_ASIO_STANDALONE
#include <connection.hpp>
#include <asio.hpp>
#include <set>
#include <iostream>

class Connection;
typedef std::shared_ptr<Connection> ConnectionPtr;
typedef std::set<ConnectionPtr> ConnectionSet;

class ClientInfo
{
	std::string username_;
	ConnectionPtr connection_;
};

class Server
{
	public:
		Server(asio::io_context& io) noexcept;
		bool start(std::string const& ip, unsigned short port);
		void sendTo(std::string message, ConnectionPtr connect);
		void sendToAll(std::string message);
		void leave(ConnectionPtr connect);
		void addMsg(std::string const& msg);
		const std::vector<std::string>& getMessages()const{return messages_;}

	private:
		void run();
		void accept();
		asio::io_context& io_;
		asio::io_context::strand strand_;
		asio::ip::tcp::acceptor acceptor_;
		//std::string message_;
		//std::unique_ptr<std::thread> ioThr_;
		ConnectionSet connectSet_;
		std::vector<std::string> messages_{};


};
