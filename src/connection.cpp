#include <connection.hpp>

void Connection::read(std::shared_ptr<tcp::socket> socket_)
{
	asio::async_read_until(*socket_, asio::dynamic_buffer(message_), '\n', [this, socket_](asio::error_code ec, size_t transfered)
			{
				if(message_[0] == 'S' && message_[1] == 'T'&& message_[2] == 'O'&& message_[3] == 'P')
				{
					return ;
				}
				else if(ec)
				{
					std::cout<<"error reading"<<"\n";
					this->read(socket_);
				}
				else
				{
					std::cout<<message_;
					this->write(socket_);
				}
			});
}

void Connection::write(std::shared_ptr<tcp::socket> socket_)
{
	asio::error_code ec;
	asio::async_write(*socket_, asio::buffer(message_), [this, socket_](asio::error_code ec, size_t transfered)
			{
				if(ec)
				{
					std::cerr<<"ERROR WRITING\n";
				}
				message_.clear();
				this->read(socket_);
			});
}
