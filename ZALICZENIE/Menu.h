#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Constants.h"

class Menu
{
public:
	Menu(double width, double height);
	~Menu();

	void draw(sf::RenderWindow& window);
	void MoveUp();
	void MoveDown();
	int getPressedItem() { return selectedItemIndex; }
	int isMouseOver(sf::RenderWindow& window, int item);

private:
	int selectedItemIndex;
	sf::Font font;
	sf::Text menu[NUM_ITEMS];
};

