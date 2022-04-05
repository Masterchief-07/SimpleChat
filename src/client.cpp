#include <client.hpp>
#include <iostream>

Client::Client():io_{},socket_{io_},endpoint_{}
{

}


bool Client::connect(std::string const& username, std::string const& ip, unsigned short port)
{
	asio::error_code ec;
	endpoint_.address(asio::ip::make_address(ip));
	endpoint_.port(port);
	socket_.connect(endpoint_, ec);
	if(ec)
	{
		std::cerr<<"can't connect to: "<<endpoint_<<std::endl;
		return false;
	}
	asio::write(socket_, asio::buffer(username_+"\n"), ec);
	if(ec)
	{
		std::cerr<<"can't init the connection"<<std::endl;
		return false;
	}
	else
		std::cout<<"CONNECTED"<<std::endl;
	this->receive();
	return true;
}
void Client::send(std::string const& message)
{
	messagesSend_.push(message);
	this->do_send();
}

void Client::do_send()
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
					this->do_send();
				});
	}
}



void Client::receive()
{
	std::string username, message;
	asio::async_read_until(socket_,asio::dynamic_buffer(username), '\n',[this, username, &message](asio::error_code ec, size_t transfered)
			{
				this->receive();
				if(ec)
				{
					std::cerr<<"USERNAME NOT RECEIVE"<<std::endl;
					return ;
				}
				else
				{
					asio::async_read_until(socket_,asio::dynamic_buffer(message), '\n',[this, username, message](asio::error_code ec, size_t transfererd)
							{
								if(ec)
								{
									std::cerr<<"MESSAGE NOT RECEIVE"<<std::endl;
									return;
								}
								else
								{
									messagesReceive_.push_back({username, message});

								}
							});
				}
			});
}






