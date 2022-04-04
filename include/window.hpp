#include <iostream>
#include <vector>

class Window
{
	public:
		Window();
		~Window();
	
	private:
		void selectionWindow();
		void configServer();
		void configClient();
		void serverWindow(std::string const& ip, std::string const& port);
		void clientWindow(std::string const& username, std::string const& ip, std::string const& port);
		void errorMessage(std::string const& ec);

};



