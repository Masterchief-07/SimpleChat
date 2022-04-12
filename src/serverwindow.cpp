#include<serverwindow.hpp>

using namespace ftxui;

//-------------------------CLIENT-----------------------------------------------

ServerWindow::ServerWindow(Server& server):server_{server}, message_{}, messagesList_{}, clientNameList_{}
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
			messagesList_.push_back(server_.getMessages()[i]);
			//messageReceived_->Add(MenuEntry(server_.getMessages()[i]));
			
	}
	msgSize = actual_size;
}

void ServerWindow::render()
{
	ScreenInteractive screen_{ScreenInteractive::Fullscreen()};
	int selector=0;
	Component messageReceived_= Menu(&messagesList_, &selector);
	//list of differents elements
		//send message by the client app
	Component sendButton_= Button("SEND",[&]{
			this->server_.sendToAll(this->message_);
			this->message_.clear();
			});
	Component exitButton_ = Button("EXIT", screen_.ExitLoopClosure());
	Component textInput_ = Input(&this->message_, "TAPE YOUR TEXT");
	

	//organise the differents elements
	Component layouts = Container::Vertical({
			messageReceived_,
			textInput_,
			Container::Horizontal({
					sendButton_, exitButton_})
			});

	Component messageRender_= Renderer(layouts,[&]{ 
				this->addNewMsg();
				return
				vbox({
					messageReceived_->Render() | flex | vscroll_indicator | frame |border,
					textInput_->Render() | border,
					hbox({
						sendButton_->Render(),
						exitButton_->Render(),
					}) | center,
				}) | flex;
			});

	Component clientMenu_ = Menu(&clientNameList_, &clientSelected_);
	auto clientRender = Renderer(clientMenu_, [&]{
			clientNameList_ = server_.getClientName();
			return window(text("Client " + std::to_string(clientNameList_.size())),clientMenu_->Render());
			});


	screen_.Loop(Container::Horizontal({messageRender_, clientRender}));
	//screen_.Loop(messageRender_);

}

