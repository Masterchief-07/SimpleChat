#pragma once
#include <string>
#include <ncurses.h>

class Window
{
	public:
		Window();
		~Window();

	private:
		WINDOW* m_win;
		int m_sizeX;
		int m_sizeY;
};

//welcome display
class Welcome
{
	public:
		Welcome(WINDOW *parent, int maxY, int maxX);
		~Welcome();
		show();
		selection();

	
	private:
		int m_sizeX, m_sizeY;
		WINDOW* m_win;
		unsigned short m_selection;
		std::string const m_menu[4] = {
			"Server",
			"Client",
			"Quit",
			"Help",
		};
};
