#include <connection.hpp>
Connection::Connection(asio::ip::tcp::socket socket, Server& server):socket_{std::move(socket)}, server_{server}, isConnected_{true}
{
}

Connection::~Connection()
{
	this->close();
}

void Connection::connect()
{
	this->readUsername();
}

//get the username from client
void Connection::readUsername()
{
	asio::async_read_until(socket_, asio::dynamic_buffer(username_), '\n', [this,self=shared_from_this()]
			(asio::error_code ec, size_t transfered)
			{
				if(ec)
				{
					std::cerr<<"USERNAME ERROR"<<std::endl;
					self->close();
				}
				std::cout<<"USERNAME: "<<username_<<std::endl;
				this->read();
			});
}

void Connection::read()
{
	asio::async_read_until(socket_, asio::dynamic_buffer(message_), '\n', [this, self=shared_from_this()](asio::error_code ec, size_t transfered)
			{
				if(self->message_[0] == 'S' && self->message_[1] == 'T'&& self->message_[2] == 'O'&& self->message_[3] == 'P')
				{
					self->close();
					return ;
				}
				else if(ec)
				{
					//std::cout<<"error reading"<<"\n";
					self->close();
					return;
				}
				else
				{
					//std::cout<<self->message_;
					std::string msg = this->username_+": "+self->message_;
					this->server_.addMsg(msg);
					this->server_.sendToAll(msg);
				}
				self->message_.clear();
				self->read();
			});
}

void Connection::write(std::string message)
{
	asio::async_write(socket_, asio::buffer(message), [self=shared_from_this()](asio::error_code ec, size_t transfered)
			{
				if(ec)
				{
					std::cerr<<"CONNECTIONS::ERROR WRITTING\n";
				}

			});
}

void Connection::close()
{
	this->isConnected_ = false;
	this->socket_.close();
	this->server_.leave(shared_from_this());
}


