#include<serverwindow.hpp>

using namespace ftxui;

//-------------------------CLIENT-----------------------------------------------

ServerWindow::ServerWindow(Server& server):screen_{ftxui::ScreenInteractive::Fullscreen()}, message_{}, server_{server}
{
	this->render();

}

ServerWindow::~ServerWindow()
{
	this->server_.close();
}

void ServerWindow::addNewMsg()
{
	size_t actual_size = server_.getMessages().size();
	if(msgSize<=actual_size)
	{
		for(auto i=msgSize; i<actual_size; i++)
			messageReceived_->Add(MenuEntry(server_.getMessages()[i]));
	}
	msgSize = actual_size;
}

Component ServerWindow::getClientRender_()
{
	clientMenu_ = Menu(&clientNameList_, &clientSelected_);
	return  Renderer(clientMenu_, [&]{
			clientNameList_ = server_.getClientName();
			return window(text("Client " + std::to_string(clientNameList_.size())),clientMenu_->Render());
			});
	
}

void ServerWindow::render()
{
	int selector=0;
	messageReceived_ = Container::Vertical({}, &selector);
	//list of differents elements
		//send message by the client app
	sendButton_ = Button("SEND",[this]{
			this->server_.sendToAll(this->message_);
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

	clientMenu_ = Menu(&clientNameList_, &clientSelected_);
	auto clientRender = Renderer(clientMenu_, [&]{
			clientNameList_ = server_.getClientName();
			return window(text("Client " + std::to_string(clientNameList_.size())),clientMenu_->Render());
			});


	screen_.Loop(Container::Horizontal({messageRender_, clientRender}));
	//screen_.Loop(messageRender_);

}

