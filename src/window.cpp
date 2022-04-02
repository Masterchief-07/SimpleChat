#include <window.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/component/component.hpp>
using namespace ftxui;

Window::Window()
{
	this->selectionWindow();
	//this->configServer();
	//this->configClient();
}

Window::~Window()
{}

void Window::selectionWindow()
{
	auto screen = ScreenInteractive::Fullscreen();
	Component server_btn = Button("SERVER",[&]{this->configServer();});
	Component client_btn = Button("CLIENT",[&]{this->configClient();});
	Component settings_btn = Button("SETTING", []{});
	Component quit_btn = Button("QUIT", screen.ExitLoopClosure());

	auto select_container = Container::Vertical({
			server_btn,
			client_btn,
			//settings_btn,
			quit_btn
			});
	
	auto render = Renderer(select_container, [&]{ return
			vbox({
				hbox({ text("SIMPLE CHAT") | bold }) | border |center,
				hbox({
					vbox({
						server_btn->Render(),
						client_btn->Render(),
					//	settings_btn->Render(),
						quit_btn->Render(),
						}) | border,
				}) | center,
			}) | center;
		});

	screen.Loop(render);
}

//CONFIGURATION DU SERVER
//PRINT IF THE CREATION OF THE SERVER IS OK
//PRINT THE SERVER IP AND PORT
void Window::configServer()
{	
	auto screen = ScreenInteractive::Fullscreen();
	std::string server_ip;
	std::string server_port;

	Component ip_input = Input(&server_ip, "127.0.0.1");
	Component port_input = Input(&server_port, "60000");
	Component create_btn = Button("CREATE", []{});
	Component cancel_btn = Button("CANCEL", screen.ExitLoopClosure());

	auto container = Container::Vertical({
			ip_input,
			port_input,
			Container::Horizontal({
				create_btn, cancel_btn,}),
			});

	auto render = Renderer(container, [&]{ return
		vbox({
			hbox({
				vbox({
					text("SERVER") | bold,
					hbox({text("IP: "), separator(), ip_input->Render()}),
					hbox({text("PORT: "), separator(), port_input->Render()}),
					hbox({create_btn->Render(), cancel_btn->Render()}),
				}) | border,
			}) | center,
		}) | center;
	});
	
	screen.Loop(render);

}

void Window::configClient()
{	
	auto screen = ScreenInteractive::Fullscreen();
	std::string username;
	std::string server_ip;
	std::string server_port;

	Component username_input = Input(&username, " ");
	Component ip_input = Input(&server_ip, "127.0.0.1");
	Component port_input = Input(&server_port, "60000");
	Component create_btn = Button("CREATE", [this]{this->errorMessage("error");});
	Component cancel_btn = Button("CANCEL", screen.ExitLoopClosure());

	auto container = Container::Vertical({
			username_input,
			ip_input,
			port_input,
			Container::Horizontal({
				create_btn, cancel_btn,}),
			});

	auto render = Renderer(container, [&]{ return
		vbox({
			hbox({
				vbox({
					text("SERVER") | bold,
					hbox({text("Username: "), separator(), username_input->Render()}),
					hbox({text("IP: "), separator(), ip_input->Render()}),
					hbox({text("PORT: "), separator(), port_input->Render()}),
					hbox({create_btn->Render(), cancel_btn->Render()}),
				}) | border,
			}) | center,
		}) | center;
	});
	
	screen.Loop(render);

}

void Window::clientWindow(std::string const& username, std::string const& ip, std::string const& port)
{	
	ClientWindow client(username, ip, port);
	
	if(client.Connect())
		client.display();
	else
		this->errorMessage(client.error());
}
void Window::errorMessage(std::string const& ec)
{
	auto screen = ScreenInteractive::Fullscreen();
	auto container = Container::Horizontal({
		Button("OK", screen.ExitLoopClosure()),
		});
	auto render = Renderer(container, [&]{ return
			hbox({
				vbox({
					text(ec) | bold,
					container->Render(),
					}) | center,
				}) | center;
			});

	screen.Loop(render);
}


ClientWindow::ClientWindow(std::string const& username, std::string const& ip, std::string const& port):m_username{username}, m_ip{ip}, m_port{port}
{

}

bool ClientWindow::Connect()
{
	return true;
}

void ClientWindow::display()
{

}

std::string ClientWindow::error()
{
	return " ";
}



