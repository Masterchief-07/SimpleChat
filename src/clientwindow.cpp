#include <clientwindow.hpp>
#include <sstream>
using namespace ftxui;
//-------------------------CLIENT-----------------------------------------------

ClientWindow::ClientWindow(Client& client):screen_{ftxui::ScreenInteractive::Fullscreen()}, message_{}, client_{client}
{
	this->render();

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

void ClientWindow::render()
{
	int selector=0;
	messageReceived_ = Container::Vertical({}, &selector);
	//list of differents elements
		//send message by the client app
	sendButton_ = Button("SEND",[this]{
			this->client_.send(this->message_);
			this->message_.clear();
			});
	exitButton_ = Button("EXIT", screen_.ExitLoopClosure());
	textInput_ = Input(&this->message_, "TAPE YOUR TEXT");
	

	//organise the differents elements
	Component layouts = Container::Vertical({
			messageReceived_,
			textInput_,
			Container::Horizontal({
					sendButton_, exitButton_})
			});

	messageRender_ = Renderer(layouts,[this]{ 
				this->addNewMsg();
				return
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
