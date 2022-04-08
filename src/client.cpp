#include <client.hpp>
#include <iostream>

Client::Client(asio::io_context& io):io_{io},strand_{io_},socket_{io_},endpoint_{}
{
}

Client::~Client()
{
}


bool Client::connect(std::string const& username, std::string const& ip, unsigned short port)
{
	username_ = username;
	asio::error_code ec;
	endpoint_.address(asio::ip::make_address(ip));
	endpoint_.port(port);
	socket_.connect(endpoint_, ec);
	if(ec)
	{
		std::cerr<<"ERROR: "<<ec.message()<<std::endl;
		return false;
	}
	this->sendUsername();
	this->receive();
	return true;
}

void Client::sendUsername()
{
	asio::async_write(socket_, asio::buffer(username_+"\n"), [this](asio::error_code ec, size_t transfererd)
			{
				if(ec)
				{
					std::cerr<<"can't init the connection"<<std::endl;
					close();
					return;
				}
			});
				
}

void Client::send(std::string const& message)
{
	bool state = messagesSend_.empty();
	messagesSend_.push(message);
	if(state)
	{
		asio::post(io_,strand_.wrap( [&](){
			this->doSend();
		}));
	}
}

void Client::doSend()
{
	if(!messagesSend_.empty())
	{
		asio::async_write(socket_, asio::buffer(messagesSend_.front()+"\n"), [this](asio::error_code ec, size_t transfered)
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
					close();
					return ;
				}
				messagesReceive_.push_back(message_);
				message_.clear();
				this->receive();
			});
}


void Client::close()
{
	this->socket_.close();
}



