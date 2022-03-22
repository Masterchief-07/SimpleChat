#pragma once
#include <string>
#include <ncurses.h>
#include <array>

/* -----------------------MENU--------------------- */
class Menu
{
	public:
		Menu(int maxY, int maxX);
		~Menu();
		void display();
		int selection();
		static const size_t NBMENU = 5;

	
	private:
		int m_sizeX, m_sizeY;
		unsigned short m_selection;
		WINDOW* m_win, *m_parent;
		std::array<std::string, NBMENU> m_menu = {
			"Server",
			"Client",
			"Settings",
			"Help",
			"Quit",
		};
		std::array<std::array<int, 2>,NBMENU> m_menuPos = {{{0},{0}}};

		void init_menu_pos();


};
/* -----------------------CLIENTWIN--------------------- */
class CLient;
class ClientWin
{
	public:
		ClientWin( int sizeY, int sizeX);
		~ClientWin();
		void display();
		void launch();

	private:
		int m_size1Y, m_size1X, m_size2Y, m_size2X;
		WINDOW *m_winAff, *m_winText, *m_parent;

};

/* -----------------------SERVERWIN--------------------- */
class Server;
class ServerWin
{

};

/* -----------------------SETTINGSWIN--------------------- */
class SettingsWin
{

};

/* -----------------------WINDOW--------------------- */
class Window
{
	public:
		Window();
		~Window();
		void display();

	private:
		WINDOW* m_win;
		int m_sizeX;
		int m_sizeY;
};


