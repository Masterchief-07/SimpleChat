#include <server.hpp>
using asio::ip::tcp;

Server::Server() noexcept :ioCtx_{}, acceptor_{ioCtx_,{tcp::v4(), 60000}}, socket_{ioCtx_}
{

}

void Server::start()
{
	asio::error_code ec;
	acceptor_.accept(socket_,ec);
	if(ec)
	{
		std::cout<<"error accepting"<<std::endl;
		this->start();
	}
	else
	{
		this->read();
	}
}

void Server::read()
{
	asio::error_code ec;
	asio::read_until(socket_, asio::dynamic_buffer(message_), '\n', ec);
	if(message_[0] == 'S' && message_[1] == 'T'&& message_[2] == 'O'&& message_[3] == 'P')
	{
		return ;
	}
	else if(ec)
	{
		std::cout<<"error reading"<<"\n";
		this->read();
	}
	else
	{
		std::cout<<message_;
		this->write();
	}
}

void Server::write()
{
	asio::error_code ec;
	asio::write(socket_, asio::buffer(message_), ec);
	if(ec)
	{
		std::cerr<<"ERROR WRITING\n";
	}
	message_.clear();
	this->read();
}
