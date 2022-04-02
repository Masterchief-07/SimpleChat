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
		void serverWindow();
		void clientWindow(std::string const& username, std::string const& ip, std::string const& port);
		void errorMessage(std::string const& ec);

};


class ClientWindow{
	public:
		ClientWindow(std::string const& username, std::string const& ip, std::string const& port);
		bool Connect();
		void display();
		std::string error();
		

	private:
		std::string m_username, m_ip, m_port;
		std::vector<std::string> m_sendBuffer;
		std::vector<std::string> m_recBuffer;
};
