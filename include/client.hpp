#pragma once

#include <asio.hpp>
#include <list>
#include <queue>

class Client
{
	public:
		Client(asio::io_context& io);
		bool connect(std::string const& username, std::string const& ip, unsigned short port);
		void send(std::string const& message);
		void receive();
		void close();
	
		const std::string getServerIp() const{return socket_.remote_endpoint().address().to_string();}
		const std::string getUsername() const{return username_;}
		const std::vector<std::string>getMessages() const{ return messagesReceive_;}
		const bool getState() const {return state;}

	private:
		//-------METHODES-------
		void doSend();
		void doSend(std::string const& msg);
		void sendUsername();

		//--------ATTRIBUTS-------
		asio::io_context& io_;
		asio::io_context::strand strand_;
		asio::ip::tcp::socket socket_;
		asio::ip::tcp::endpoint endpoint_;
		bool state{false};
		std::thread thread_;
		std::string username_;
		std::string message_;
		std::vector<std::string> messagesReceive_; //username and message
		std::queue<std::string>messagesSend_;
};
