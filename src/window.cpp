#include <window.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/dom/table.hpp>
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
	int counter=0;

	std::vector<std::vector<std::string>> messageContent = {
			{"Version", "Marketing name", "Release date", "API level", "Runtime"},
			      {"2.3", "Gingerbread", "February 9 2011", "10", "Dalvik 1.4.0"},
			      {"4.0", "Ice Cream Sandwich", "October 19 2011", "15", "Dalvik"},
			      {"4.1", "Jelly Bean", "July 9 2012", "16", "Dalvik"},
			      {"4.2", "Jelly Bean", "November 13 2012", "17", "Dalvik"},
			      {"4.3", "Jelly Bean", "July 24 2013", "18", "Dalvik"},
			      {"4.4", "KitKat", "October 31 2013", "19", "Dalvik and ART"},
			      {"5.0", "Lollipop", "November 3 2014", "21", "ART"},
			      {"5.1", "Lollipop", "March 9 2015", "22", "ART"},
			      {"6.0", "Marshmallow", "October 5 2015", "23", "ART"},
			      {"7.0", "Nougat", "August 22 2016", "24", "ART"},
			      {"7.1", "Nougat", "October 4 2016", "25", "ART"},
			      {"8.0", "Oreo", "August 21 2017", "26", "ART"},
			      {"8.1", "Oreo", "December 5 2017", "27", "ART"},
			      {"9", "Pie", "August 6 2018", "28", "ART"},
			      {"10", "10", "September 3 2019", "29", "ART"},
			      {"11", "11", "September 8 2020", "30", "ART"},	
			      };
	messageContent.push_back({"new", "new", "new", "new","new"});
	Table messageTable = Table(messageContent);
	std::string wintitle = "message";

	auto messageTableRender = messageTable.Render();	
	Component button = Button("ADD", [&]{messageContent.push_back({"new", "new", "new", "new","new"}); 
						counter+=1;
						wintitle+=" hi";});

	auto textScreen = Renderer(button, [&]{
			return vbox({window(text(wintitle  + std::to_string(counter)),  messageTableRender ),
					button->Render()}) | size(WIDTH, EQUAL, 80);
			});
	auto textScreen2 = Renderer([&]{
			return window(text("CLIENTS"), text("text screen") | center) | flex;
			});
	

	screen.Loop(Container::Horizontal({textScreen, textScreen2}));
	


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




