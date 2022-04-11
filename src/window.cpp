#include <window.hpp>
#include <sstream>
using namespace ftxui;

Window::Window():io_{}
{
	asio::executor_work_guard<decltype(io_.get_executor())> work{io_.get_executor()};
	ioThr_ = std::thread([this]{this->io_.run();});
	this->selectionWindow();
	//this->configServer();
	//this->configClient();
}

Window::~Window()
{
	this->io_.stop();
	ioThr_.join();	
}


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
	Component create_btn = Button("CREATE", [&]{this->serverConnect(server_ip, server_port);});
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
	Component create_btn = Button("CONNECT", [this, &username, &server_ip, &server_port]{this->clientConnect(username, server_ip, server_port);});
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
//configuration of the client window
void Window::clientConnect(std::string const& username, std::string const& ip, std::string const& port)
{
	Client client{io_};
	std::stringstream ss; ss<<port;
	unsigned short numport; ss>>numport;
	if(ss.fail())
	{
		this->errorMessage("error PORT");
		return;
	}
	if(!client.connect(username, ip, numport))
	{
		this->errorMessage("ERROR CAN'T CONNECT TO THE SERVER");
		return;
	}
	ClientWindow clientwindow{client};
}

void Window::serverConnect(std::string const& ip, std::string const& port)
{
	try
	{
	Server server{io_};	
	std::stringstream ss; ss<<port;
	unsigned short numport; ss>>numport;
	if(ss.fail())
	{
		this->errorMessage("error PORT");
		return;
	}
	if(!server.start(ip, numport))
	{
		this->errorMessage("ERROR CAN'T CREATE THE SERVER");
		return;
	}
		ServerWindow serverWindow{server};
		server.close();
	}
	catch(std::exception& ec)
	{
		std::cerr<<ec.what()<<std::endl;
	}

}

void Window::errorMessage(std::string const& ec)
{
	auto screen = ScreenInteractive::Fullscreen();
	auto button = Button("QUI", screen.ExitLoopClosure());
	auto render = Renderer(button ,[&]{
			return vbox({
			text(ec) | center | border,
			button->Render(),
			});
		});
	screen.Loop(render);
}
