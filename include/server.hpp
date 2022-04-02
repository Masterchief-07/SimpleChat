#pragma once
#define ASIO_STANDALONE
#define BOOST_ASIO_STANDALONE
#include <asio.hpp>
#include <iostream>

class Server
{
	public:
		Server() noexcept;
		void start();
		void run();

	private:
		void accept();
		void read(std::shared_ptr<asio::ip::tcp::socket> socket_);
		void write(std::shared_ptr<asio::ip::tcp::socket> socket_);
		void broadcast();
		asio::io_context io_;
		asio::ip::tcp::acceptor acceptor_;
		std::string message_;

};
