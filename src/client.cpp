#include <client.hpp>
#include <iostream>

Client::Client(std::string const& username):io_{},socket_{io_},endpoint_{},username_{username}
{

}


bool Client::connect(std::string const& ip, unsigned short port)
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

	});
	this->io_.run();
	return true;
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
				this->send("HELLO\n");
				this->receive();
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
	std::string username;
	asio::async_read_until(socket_,asio::dynamic_buffer(username), '\n',[username](asio::error_code ec, size_t transfered)
			{
				if(ec)
				{
					std::cerr<<"USERNAME NOT RECEIVE"<<std::endl;
					return ;
				}
				std::cout<<username<<": ";
				/*
				std::string message;
				asio::async_read_until(socket_,asio::dynamic_buffer(message), '\n',[message](asio::error_code ec, size_t transfererd)
							{
								if(ec)
								{
									std::cerr<<"MESSAGE NOT RECEIVE"<<std::endl;
									return;
								}
								else
								{
									std::cout<<message<<std::endl;
									//messagesReceive_.push_back({username, message});
								}
							});*/
			});
}






