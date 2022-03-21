#include <window.hpp>

Window::Window()
{
	initscr();
	mywin = stdscr;

}

Window::~Window()
{
	endwin();
}
