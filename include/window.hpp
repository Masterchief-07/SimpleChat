#pragma once

#include <ncurses.h>

class Window
{
	public:
		Window();
		~Window();

	private:
		WINDOW* mywin;
};

