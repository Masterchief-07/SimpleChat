#include <window.hpp>
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
	Component create_btn = Button("CREATE", [&]{this->serverWindow(server_ip, server_port);});
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

void Window::serverWindow(std::string const& ip, std::string const& port)
{
	auto screen = ScreenInteractive::Fullscreen();
		auto messageList = Container::Vertical({
			Renderer([]{return hbox({text("jonathan"),filler(), text("HELLO WORLD")});}),
			Renderer([]{return hbox({text("jonathan"),filler(), text("HELLO WORLD")});}),
			Renderer([]{return hbox({text("jonathan"),filler(), text("HELLO WORLD")});}),
			Renderer([]{return hbox({text("jonathan"),filler(), text("HELLO WORLD")});}),
			});

	std::string wintitle = "message";

	Component button = Button("ADD", [&]{ messageList->Add(Renderer([]{return hbox({text("jonathan"),filler(), text("HELLO WORLD")});}));
						});

	auto textScreen = Renderer([&]{
			return window(text(wintitle), messageList->Render() | vscroll_indicator |frame| size(HEIGHT, LESS_THAN, 20))
				| size(WIDTH, EQUAL, 80);
			});
	auto textScreen2 = Renderer([&]{
			return window(text("CLIENTS"), text("text screen") | center) | flex;
			});
	

	screen.Loop(Container::Horizontal({textScreen, textScreen2, button}));
	


}

void Window::clientWindow(std::string const& username, std::string const& ip, std::string const& port)
{	
	

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



ClientWindow::ClientWindow():screen_{ftxui::ScreenInteractive::Fullscreen()}, message_{}
{
	this->render();

}

void ClientWindow::render()
{

	MenuOption option = MenuOption::VerticalAnimated();
	std::vector<std::string> messages_ = {"hello world", "hello you"};
	int selector=0;
	messageReceived_ = Menu(&messages_, &selector, option);	
	//list of differents elements
	sendButton_ = Button("SEND", [&]{messages_.push_back("add");});
	exitButton_ = Button("EXIT", screen_.ExitLoopClosure());
	textInput_ = Input(this->message_, "TAPE YOUR TEXT");
	

	//organise the differents elements
	Component layouts = Container::Vertical({
			messageReceived_,
			textInput_,
			Container::Horizontal({
					sendButton_, exitButton_})
			});

	messageRender_ = Renderer(layouts,[this]{ return
				vbox({
					messageReceived_->Render() | flex | vscroll_indicator | frame,
					textInput_->Render() | border,
					hbox({
						sendButton_->Render(),
						exitButton_->Render(),
					}) | center,
				}) | flex;
			});

	screen_.Loop(messageRender_);

}
