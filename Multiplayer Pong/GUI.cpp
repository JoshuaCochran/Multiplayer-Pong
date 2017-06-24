#include "GUI.h"

GUI::GUI(sf::RenderWindow& window, Server* server, GUIType type)
{
	_window = &window;
	_server = server;
	_gui = new tgui::Gui(*_window);

	if (type == GUIType::hostMenu)
		loadHostMenu();
	else if (type == GUIType::joinMenu)
		loadJoinMenu();
}

GUIState GUI::HandleEvent(sf::Event event)
{
	_gui->handleEvent(event);

	return _state;
}

void GUI::Draw()
{
	_gui->draw();
}

void GUI::runHost(tgui::EditBox::Ptr ip)
{
	_server->Initialize(ip->getText().toAnsiString(), 9000, true);
	
	_state = GUIState::hosting;
}

void GUI::runJoin(tgui::EditBox::Ptr ip, tgui::EditBox::Ptr port)
{
	unsigned int _port = std::stoi(port->getText().toAnsiString(), nullptr, 0);
	_server->Initialize(ip->getText().toAnsiString(), _port, false);

	_state = GUIState::joining;
}

void GUI::loadHostMenu()
{
	// Load the black theme
	auto theme = tgui::Theme::create("data/images/GUI/Black.txt");

	// Get a bound version of the window size
	// Passing this to setPosition or setSize will make the widget automatically update when the view of the gui changes
	auto windowWidth = tgui::bindWidth(*_gui);
	auto windowHeight = tgui::bindHeight(*_gui);

	// Create the background image (picture is of type tgui::Picture::Ptr or std::shared_widget<Picture>)
	auto picture = tgui::Picture::create("data/images/GUI/xubuntu_bg_aluminium.jpg");
	picture->setSize(tgui::bindMax(800, windowWidth), tgui::bindMax(600, windowHeight));
	_gui->add(picture);

	// Create the username edit box
	tgui::EditBox::Ptr editBoxUsername = theme->load("EditBox");
	editBoxUsername->setSize(windowWidth * 2 / 3, windowHeight / 8);
	editBoxUsername->setPosition(windowWidth / 6, windowHeight / 6);
	editBoxUsername->setDefaultText("127.0.0.1:9000");
	_gui->add(editBoxUsername, "IpPort");

	// Create the login button
	tgui::Button::Ptr button = theme->load("Button");
	button->setSize(windowWidth / 2, windowHeight / 6);
	button->setPosition(windowWidth / 4, windowHeight * 7 / 10);
	button->setText("Host");
	_gui->add(button);

	// Call the login function when the button is pressed
	button->connect("pressed", &GUI::runHost, this, editBoxUsername);
}

void GUI::loadJoinMenu()
{
	// Load the black theme
	auto theme = tgui::Theme::create("data/images/GUI/Black.txt");

	// Get a bound version of the window size
	// Passing this to setPosition or setSize will make the widget automatically update when the view of the gui changes
	auto windowWidth = tgui::bindWidth(*_gui);
	auto windowHeight = tgui::bindHeight(*_gui);

	// Create the background image (picture is of type tgui::Picture::Ptr or std::shared_widget<Picture>)
	auto picture = tgui::Picture::create("data/images/GUI/background.png");//"data/images/GUI/xubuntu_bg_aluminium.jpg");
	picture->setSize(tgui::bindMax(800, windowWidth), tgui::bindMax(600, windowHeight));
	_gui->add(picture);

	// Create the username edit box
	tgui::EditBox::Ptr editBoxIP = theme->load("EditBox");
	editBoxIP->setSize(windowWidth * 2 / 3, windowHeight / 8);
	editBoxIP->setPosition(windowWidth / 6, windowHeight / 6);
	editBoxIP->setDefaultText("IP");
	_gui->add(editBoxIP, "IpPort");

	// Create the password edit box
	tgui::EditBox::Ptr editBoxPort = theme->load("EditBox");
	editBoxPort->setSize(windowWidth * 2 / 3, windowHeight / 8);
	editBoxPort->setPosition(windowWidth / 6, windowHeight * 5 / 12);
	editBoxPort->setDefaultText("port (e.g. 9000)");
	_gui->add(editBoxPort, "Port");

	// Create the login button
	tgui::Button::Ptr button = theme->load("Button");
	button->setSize(windowWidth / 2, windowHeight / 6);
	button->setPosition(windowWidth / 4, windowHeight * 7 / 10);
	button->setText("Join");
	_gui->add(button);

	// Call the login function when the button is pressed
	button->connect("pressed", &GUI::runJoin, this, editBoxIP, editBoxPort);
}