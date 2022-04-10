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
		~ServerWindow(){}
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
		Server &server_;

};
