#include <window.hpp>

/* -----------------------MENU--------------------- */
Menu::Menu(int maxY, int maxX):m_sizeX{maxX/2}, m_sizeY{maxY/2}, m_selection{0}
{
	m_parent = newwin(0,0,0,0);
	m_win = subwin(m_parent, m_sizeY, m_sizeX, m_sizeY/2, m_sizeX/2);
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
	wbkgd(m_win,COLOR_PAIR(2));
	box(m_win, 0,0);
	keypad(m_win, true);
	
	for(int i=0; i < NBMENU; i++)
	{
		if(i==m_selection)
			wattron(m_win, A_REVERSE);
		mvwaddstr(m_win, m_menuPos[i][0], m_menuPos[i][1], m_menu[i].c_str());
		wattroff(m_win, A_REVERSE);
	}
	touchwin(m_win);
	wrefresh(m_win);
	
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
	delwin(m_parent);
}

/* -----------------------CLIENTWIN--------------------- */

ClientWin::ClientWin(int sizeY, int sizeX): m_size1Y{sizeY - static_cast<int>(0.3*sizeY)}, m_size1X{sizeX}, m_size2Y{static_cast<int>(0.3 * sizeY)}, m_size2X{sizeX}
{
	m_parent = newwin(0,0,0,0);
	wbkgd(m_parent, COLOR_PAIR(1));
	m_winAff = subwin(m_parent, m_size1Y, m_size1X, 0, 0);
	m_winText = subwin(m_parent, m_size2Y, m_size2X, m_size1Y, 0);
}

void ClientWin::display()
{
	wbkgd(m_winAff, COLOR_PAIR(2));
	wbkgd(m_winText, COLOR_PAIR(3));

	wrefresh(m_winAff);
	wrefresh(m_winText);
	getch();
}

void ClientWin::launch()
{
	int ch=0;
	do
	{
		this->display();
	}while((ch = getch()) != '\n');

}

ClientWin::~ClientWin()
{
	delwin(m_winAff);
	delwin(m_winText);
	delwin(m_parent);
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
	erase();
	Menu m_menu(m_sizeY, m_sizeX);
	ClientWin m_clientWin(m_sizeY, m_sizeX);
		
	int select = 0;
	while((select = m_menu.selection()) != m_menu.NBMENU - 1)
	{
		switch(select)
		{
			case 0:
				m_clientWin.launch();
				//mvaddstr(0,0,"select Server:");
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
}


