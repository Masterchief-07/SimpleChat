#include <server.hpp>
using asio::ip::tcp;

Server::Server(asio::io_context& io) noexcept :io_{io},strand_{io_}, acceptor_{io_}
{

}

bool Server::start(std::string const& ip, unsigned short port)
{
	try
	{
		asio::ip::tcp::endpoint endpoint{asio::ip::make_address(ip), port};
		acceptor_.open(endpoint.protocol());
		acceptor_.bind(endpoint);
	}
	catch(std::exception& ec)
	{
		return false;
	}
	this->accept();
	return true;
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
			auto newconnect = std::make_shared<Connection>(std::move(socket), *this);
			newconnect->connect();
			connectSet_.insert(std::move(newconnect));
		});
}

void Server::sendTo(std::string message, ConnectionPtr connect)
{
	if(connect->isConnected())
	{
		connect->write(message);
	}
}

void Server::sendToAll(std::string message)
{
	for(auto& connected: connectSet_)
	{
		//connected->write(connected->getUsername()+'\n');
		connected->write(message+'\n');
	}
}

void Server::leave(ConnectionPtr connect)
{
	this->connectSet_.erase(connect);		
}

void Server::addMsg(std::string const& msg)
{
	strand_.post([this, &msg]{this->messages_.push_back(msg);});
}
