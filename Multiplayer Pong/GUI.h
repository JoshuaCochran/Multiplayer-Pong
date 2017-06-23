#ifndef _GUI_H
#define _GUI_H

#include <TGUI/TGUI.hpp>
#include <SFML/Main.hpp>
#include "Server.h"

enum GUIType {
	hostMenu, joinMenu
};

class GUI
{
public:
	GUI(sf::RenderWindow& window, Server* server, GUIType type);
	void HandleEvent(sf::Event event);
	void Draw();

private:
	tgui::Gui* _gui;
	sf::RenderWindow* _window;
	Server* _server;
	

	GUIType _type;

	void runHost(tgui::EditBox::Ptr ip);
	void runJoin(tgui::EditBox::Ptr ip, tgui::EditBox::Ptr port);
	
	void loadHostMenu();
	void loadJoinMenu();
};

#endif
