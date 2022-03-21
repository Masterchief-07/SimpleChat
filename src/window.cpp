#include <window.hpp>

Window::Window()
{
	initscr();
	mywin = stdscr;
	getch();

}

Window::~Window()
{
	endwin();
}
