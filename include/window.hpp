#include <iostream>
#include <vector>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/dom/table.hpp>
#include <ftxui/component/component.hpp>
#include <thread>
#include <client.hpp>
#include <server.hpp>

class ClientWindow
{
	public:
		ClientWindow(Client& client);
		~ClientWindow(){}
		void render();
	private:
		void addNewMsg();
		int msgSize=0;	
		ftxui::ScreenInteractive screen_;
		ftxui::Component messageRender_;
		ftxui::Component messageReceived_;
		ftxui::Component sendButton_;
		ftxui::Component exitButton_;
		ftxui::Component textInput_;
		std::string message_;
		Client &client_;

};


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
		void serverWindow(std::string const& ip, std::string const& port);
		void clientWindow(std::string const& username, std::string const& ip, std::string const& port);
		void errorMessage(std::string const& ec);

};



