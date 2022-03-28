#include <window.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/component/component.hpp>
using namespace ftxui;

Window::Window()
{
	this->selectionWindow();
	//this->configServer();
}

Window::~Window()
{}

void Window::selectionWindow()
{
	auto screen = ScreenInteractive::TerminalOutput();
	Component server_btn = Button("SERVER",[&]{this->configServer();});
	Component client_btn = Button("CLIENT",[]{});
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
				hbox({ filler(), text("SIMPLE CHAT") | bold , filler()}) | border,
				hbox({
					filler(),
					vbox({
						server_btn->Render(),
						client_btn->Render(),
					//	settings_btn->Render(),
						quit_btn->Render(),
						}) | border,
					filler(),
				}),
			});
		});

	screen.Loop(render);
}

//CONFIGURATION DU SERVER
//PRINT IF THE CREATION OF THE SERVER IS OK
//PRINT THE SERVER IP AND PORT
void Window::configServer()
{	
	auto screen = ScreenInteractive::TerminalOutput();
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
		hbox({
			filler(),
			vbox({
				text("SERVER") | bold,
				hbox({text("IP: "), separator(), ip_input->Render()}),
				hbox({text("PORT: "), separator(), port_input->Render()}),
				hbox({create_btn->Render(), cancel_btn->Render()}),
			}) | border,
			filler(),
		});
	});
	
	screen.Loop(render);

}
