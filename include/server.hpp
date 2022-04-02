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

	private:
		void read();
		void write();
		void broadcast();
		asio::io_context ioCtx_;
		asio::ip::tcp::acceptor acceptor_;
		asio::ip::tcp::socket socket_;
		std::string message_;

};
