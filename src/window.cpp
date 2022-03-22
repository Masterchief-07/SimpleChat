#include <window.hpp>

/* -----------------------MENU--------------------- */
Menu::Menu(WINDOW* parent,int maxY, int maxX):m_sizeX{maxX/2}, m_sizeY{maxY/2}, m_selection{0}
{
	m_win = subwin(parent, m_sizeY, m_sizeX, m_sizeY/2, m_sizeX/2);
	wbkgd(m_win,COLOR_PAIR(2));
	box(m_win, 0,0);
	keypad(m_win, true);
	this->init_menu_pos();
}

void Menu::init_menu_pos()
{
	for(size_t i=0; i<m_menu.size(); i++)
	{
		// posY and posX
		m_menuPos[i][0] = (m_sizeY - m_menu.size())/2 + i;
		m_menuPos[i][1] = (m_sizeX - m_menu[i].size())/2;
	}
}

void Menu::display()
{
	for(int i=0; i < NBMENU; i++)
	{
		if(i==m_selection)
			wattron(m_win, A_REVERSE);
		mvwaddstr(m_win, m_menuPos[i][0], m_menuPos[i][1], m_menu[i].c_str());
		wattroff(m_win, A_REVERSE);
		wrefresh(m_win);
	}
}

int Menu::selection()
{
	int select = 0;
	do
	{
		if(select == KEY_UP)
			m_selection = (m_selection <= 0) ? 0 : --m_selection;
		else if(select==KEY_DOWN)
			m_selection = (m_selection >= NBMENU-1) ? NBMENU-1 : ++m_selection;
		this->display();
	}while((select=wgetch(m_win)) != '\n');
	return m_selection;
}

Menu::~Menu()
{
	delwin(m_win);
}

ClientWin::ClientWin(WINDOW* parent, int sizeY, int sizeX): m_sizeY{sizeY}, m_sizeX{sizeX}
{
	m_winAff = subwin(parent, m_sizeY,
}

/* -----------------------WINDOW--------------------- */
Window::Window()
{
	initscr();
	start_color();
	noecho();
	m_win = stdscr;
	getmaxyx(m_win, m_sizeY, m_sizeX);
	init_pair(1, COLOR_WHITE, COLOR_BLACK);
	init_pair(2, COLOR_WHITE, COLOR_RED);
	init_pair(3, COLOR_RED, COLOR_WHITE);
	bkgd(COLOR_PAIR(1));
	this->display();
	refresh();
	getch();
}

Window::~Window()
{
	endwin();
}

void Window::display()
{
	Menu m_menu(m_win, m_sizeY, m_sizeX);
		
	int select = m_menu.selection();
	switch(select)
	{
		case 0:
			erase();
			mvaddstr(0,0,"select Server:");
			break;
		case 1:
			mvaddstr(0,0,"select CLient:");
			break;
		case 2:
			mvaddstr(0,0,"setect help");
			break;
		default:

		break;
	}
}


