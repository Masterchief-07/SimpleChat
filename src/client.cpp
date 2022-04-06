#include <client.hpp>
#include <iostream>

Client::Client(std::string const& username):io_{},socket_{io_},endpoint_{},username_{username}
{

}


void Client::connect(std::string const& ip, unsigned short port)
{
	asio::error_code ec;
	endpoint_.address(asio::ip::make_address(ip));
	endpoint_.port(port);
	socket_.async_connect(endpoint_, [this](asio::error_code ec)
	{
		if(ec)
		{
			std::cerr<<"can't connect to: "<<endpoint_<<std::endl;
			return ;
		}

		this->sendUsername();
		this->receive();
	});
	this->io_.run();
}

void Client::sendUsername()
{
	asio::async_write(socket_, asio::buffer(username_+"\n"), [this](asio::error_code ec, size_t transfererd)
			{
				if(ec)
				{
					std::cerr<<"can't init the connection"<<std::endl;
					return;
				}
				std::cout<<"CONNECTED"<<std::endl;
			});
				
}

void Client::send(std::string const& message)
{
	messagesSend_.push(message);
	this->doSend();
}

void Client::doSend()
{
	if(!messagesSend_.empty())
	{
		asio::async_write(socket_, asio::buffer(messagesSend_.front()), [this](asio::error_code ec, size_t transfered)
				{
					if(ec)
					{
						std::cerr<<"ERROR SENDING"<<std::endl;
					}
					messagesSend_.pop();
					this->doSend();
				});
	}
}



void Client::receive()
{
	asio::async_read_until(socket_,asio::dynamic_buffer(message_), '\n',[this](asio::error_code ec, size_t transfered)
			{
				if(ec)
				{
					std::cerr<<"MESSAGE NOT RECEIVED"<<std::endl;
					return ;
				}
				std::cout<<message_;
				message_.clear();
				this->receive();
			});
}






