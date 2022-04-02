#include <server.hpp>
using asio::ip::tcp;

Server::Server() noexcept :io_{}, acceptor_{io_,{tcp::v4(), 60000}}
{

}

void Server::start()
{
	this->accept();
	this->run();
}

void Server::run()
{
	//ioThr_ = std::make_unique<std::thread>([this](){this->io_.run();});
	io_.run();
}

void Server::accept()
{
	acceptor_.async_accept([this](asio::error_code ec, tcp::socket socket)
		{
			this->accept();
			//connectList_.push_back(std::make_shared<Connection>(std::move(socket)));
			if(ec)
			{
				std::cerr<<"ACCEPTOR ERROR\n";
				return;
			}
			std::make_shared<Connection>(std::move(socket))->read();
			

		});
}



