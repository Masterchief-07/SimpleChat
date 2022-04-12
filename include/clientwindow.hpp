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

class ClientWindow
{
	public:
		ClientWindow(Client& client);
		~ClientWindow();
		void render();
	private:
		void addNewMsg();
		bool verifieState();
		int msgSize=0;	
		ftxui::Component messageReceived_;
		std::string message_;
		Client &client_;
};

