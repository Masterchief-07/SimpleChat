#include <window.hpp>

Window::Window()
{
	initscr();
	start_color();
	m_win = stdscr;
	getmaxyx(m_win, m_sizeX, m_sizeY);
	refresh();
	getch();
}

Window::~Window()
{
	endwin();
}

Welcome::Welcome(WINDOW* parent,int maxY, int maxX):m_sizeX{maxX/2}, m_sizeY{maxY/2} 
{
	m_win = subwin(parent, m_sizeY/2, m_sizeX/2, m_sizeY, m_sizeX);
	init_pair(1, COLOR_WHITE, COLOR_RED);
	bkgd(COLOR_PAIR(1));
}
