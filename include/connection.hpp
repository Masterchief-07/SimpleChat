#pragma once
#include<memory>
#include<string>
#include <asio.hpp>
/*
 * its takes care of the connection betwen client and server
 *
 */

class Connection
{
	public:
		Connection(asio::ip::tcp::socket socket, asio::io_context& io_ctx);

	private:
		void read(std::shared_ptr<asio::ip::tcp::socket> socket_);
		void write(std::shared_ptr<asio::ip::tcp::socket> socket_);
		void broadcast();

		asio::io_context& io_ctx;
		asio::ip::tcp::socket socket_;
};
