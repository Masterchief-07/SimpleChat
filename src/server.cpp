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
	ioThr_ = std::make_unique<std::thread>([this](){this->io_.run();});
}

void Server::accept()
{
	acceptor_.async_accept([this](asio::error_code ec, tcp::socket socket)
			{
				std::shared_ptr<tcp::socket> socket_ = std::make_shared<tcp::socket>(std::move(socket));
				this->accept();
				if(ec)
				{
					std::cout<<"error accepting"<<std::endl;
					this->accept();
				}
				else
				{
					this->read(socket_);
				}
			});
}



