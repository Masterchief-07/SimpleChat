#pragma once

#include <asio.hpp>
#include <list>
#include <queue>

class Client
{
	public:
		Client();
		bool connect(std::string const& username, std::string const& ip, unsigned short port);
		void send(std::string const& message);
		void receive();
		
		const std::string getUsername() const{return username_;}

	private:
		//-------METHODES-------
		void do_send();

		//--------ATTRIBUTS-------
		asio::io_context io_;
		asio::ip::tcp::socket socket_;
		asio::ip::tcp::endpoint endpoint_;

		std::string username_;
		std::list<std::pair<std::string, std::string>> messagesReceive_; //username and message
		std::queue<std::string>messagesSend_;
};
