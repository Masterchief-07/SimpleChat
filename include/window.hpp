#include <iostream>
#include <vector>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/dom/table.hpp>
#include <ftxui/component/component.hpp>
#include <thread>
#include <client.hpp>
#include <server.hpp>
#include <clientwindow.hpp>
#include <serverwindow.hpp>

class Window
{
	public:
		Window();
		~Window();
	
	private:
		//attribut
		asio::io_context io_;
		std::thread ioThr_;
		//methodes
		void selectionWindow();
		void configServer();
		void configClient();
		void clientConnect(std::string const& username,  std::string const& ip, std::string const& port);
		void serverConnect(std::string const& ip, std::string const& port);
		void errorMessage(std::string const& ec);

};



