#include <connection.hpp>

Connection::Connection(asio::ip::tcp::socket socket):socket_{std::move(socket)}
{
	
}

void Connection::read()
{
	asio::async_read_until(socket_, asio::dynamic_buffer(message_), '\n', [self=shared_from_this()](asio::error_code ec, size_t transfered)
			{
				if(self->message_[0] == 'S' && self->message_[1] == 'T'&& self->message_[2] == 'O'&& self->message_[3] == 'P')
				{
					return ;
				}
				else if(ec)
				{
					std::cout<<"error reading"<<"\n";
					self->read();
				}
				else
				{
					std::cout<<self->message_;
					self->write();
				}
			});
}

void Connection::write()
{
	asio::async_write(socket_, asio::buffer(message_), [self=shared_from_this()](asio::error_code ec, size_t transfered)
			{
				if(ec)
				{
					std::cerr<<"ERROR WRITING\n";
				}
				self->message_.clear();
				self->read();
			});
}
