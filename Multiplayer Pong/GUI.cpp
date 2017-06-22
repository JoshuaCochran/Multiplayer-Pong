#include <TGUI/TGUI.hpp>

void host(tgui::EditBox::Ptr ip)
{
}

void loadWidgets(tgui::Gui& gui)
{
	// Load the black theme
	auto theme = tgui::Theme::create("TGUI/widgets/Black.txt");

	// Get a bound version of the window size
	// Passing this to setPosition or setSize will make the widget automatically update when the view of the gui changes
	auto windowWidth = tgui::bindWidth(gui);
	auto windowHeight = tgui::bindHeight(gui);

	// Create the background image (picture is of type tgui::Picture::Ptr or std::shared_widget<Picture>)
	auto picture = tgui::Picture::create("xubuntu_bg_aluminium.jpg");
	picture->setSize(tgui::bindMax(800, windowWidth), tgui::bindMax(600, windowHeight));
	gui.add(picture);

	// Create the username edit box
	tgui::EditBox::Ptr editBoxUsername = theme->load("EditBox");
	editBoxUsername->setSize(windowWidth * 2 / 3, windowHeight / 8);
	editBoxUsername->setPosition(windowWidth / 6, windowHeight / 6);
	editBoxUsername->setDefaultText("IP:Port");
	gui.add(editBoxUsername, "IpPort");

	// Create the password edit box
	/*tgui::EditBox::Ptr editBoxPassword = theme->load("EditBox");
	editBoxPassword->setSize(windowWidth * 2 / 3, windowHeight / 8);
	editBoxPassword->setPosition(windowWidth / 6, windowHeight * 5 / 12);
	editBoxPassword->setPasswordCharacter('*');
	editBoxPassword->setDefaultText("Password");
	gui.add(editBoxPassword, "Password");*/

	// Create the login button
	tgui::Button::Ptr button = theme->load("Button");
	button->setSize(windowWidth / 2, windowHeight / 6);
	button->setPosition(windowWidth / 4, windowHeight * 7 / 10);
	button->setText("Host");
	gui.add(button);

	// Call the login function when the button is pressed
	button->connect("pressed", host, editBoxUsername);
}