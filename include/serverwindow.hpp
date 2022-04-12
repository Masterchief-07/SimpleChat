#pragma once
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


class ServerWindow
{
	public:
		ServerWindow(Server& server);
		~ServerWindow();
		void render();
	private:
		void addNewMsg();
		int msgSize{0};	
		Server &server_;
		std::string message_;
		std::vector<std::string> messagesList_;
		//--------client list------
		std::vector<std::string> clientNameList_;
		int clientSelected_{0};
		
};
