#include <clientwindow.hpp>
#include <sstream>
using namespace ftxui;
//-------------------------CLIENT-----------------------------------------------

ClientWindow::ClientWindow(Client& client): message_{}, client_{client}
{
	this->render();
}

ClientWindow::~ClientWindow()
{
	this->client_.close();
}

void ClientWindow::addNewMsg()
{
	size_t actual_size = client_.getMessages().size();
	if(msgSize<=actual_size)
	{
		for(auto i=msgSize; i<actual_size; i++)
			messageReceived_->Add(MenuEntry(client_.getMessages()[i]));
	}
	msgSize = actual_size;
}

bool ClientWindow::verifieState()
{
	if(!client_.getState())
	{
		//this->screen_.ExitLoopClosure();
		return false;
	}
	return true;
}

void ClientWindow::render()
{
	ftxui::ScreenInteractive screen_{ftxui::ScreenInteractive::Fullscreen()};
	bool state;
	std::string stateText;
	int selector=0;
	messageReceived_ = Container::Vertical({}, &selector);
	//list of differents elements
		//send message by the client app
	Component sendButton_ = Button("SEND",[this]{
			this->client_.send(this->message_);
			this->message_.clear();
			});
	Component exitButton_ = Button("EXIT", screen_.ExitLoopClosure());
	Component textInput_ = Input(&this->message_, "TAPE YOUR TEXT");
	


	//header render
	Component headerRender_ = Renderer([this]{
			return hbox({
					text("USERNAME: "+client_.getUsername()) | color(Color::Palette16::Green) ,
					separator(),
					text("CONNECTED TO: "+client_.getServerIp())
			
				});
			});

	//message render
		//organise the differents elements
	Component layouts = Container::Vertical({
			messageReceived_,
			textInput_,
			Container::Horizontal({
					sendButton_, exitButton_})
			});

	Component messageRender_= Renderer(layouts,[&]{ 
				this->addNewMsg();
				state = this->verifieState();
				stateText = state? "connected":"Disconnected";
				return
				vbox({
					window(text(stateText),
					messageReceived_->Render() | flex | vscroll_indicator | frame),
					textInput_->Render() | border,
					hbox({
						sendButton_->Render(),
						exitButton_->Render(),
					}) | center,
				}) | flex;
			});

	//main container
	Component mainLayouts = Container::Vertical({
					headerRender_,
					messageRender_
					});
	screen_.Loop(mainLayouts);

}
