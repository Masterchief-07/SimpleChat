#pragma once
#include <string>
#include <ncurses.h>
#include <array>

/* -----------------------MENU--------------------- */
class Menu
{
	public:
		Menu(WINDOW *parent, int maxY, int maxX);
		~Menu();
		void display();
		int selection();

	
	private:
		static const size_t NBMENU = 5;
		int m_sizeX, m_sizeY;
		WINDOW* m_win;
		unsigned short m_selection;
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
		ClientWin(WINDOW* parent, int sizeY, int sizeX);
		~ClientWin();

	private:
		int m_sizeY, m_sizeX;
		WINDOW *m_winAff, *m_winText;

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


