#pragma once
#define ASIO_STANDALONE
#define BOOST_ASIO_STANDALONE
#include <connection.hpp>
#include <asio.hpp>
#include <iostream>

class Server
{
	public:
		Server() noexcept;
		void start();

	private:
		void run();
		void accept();
		asio::io_context io_;
		asio::ip::tcp::acceptor acceptor_;
		std::string message_;
		std::unique_ptr<std::thread> ioThr_;
		std::list<connection> connectList_;

};
