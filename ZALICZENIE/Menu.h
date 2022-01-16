#pragma once

#include <SFML/Graphics.hpp>
#include "Constants.h"

class Menu {
private:
	int selectedItemIndex{ 0 };
	sf::Texture font_texture;
	std::vector<std::vector<sf::Sprite>> m_menu;
public:
	Menu(double width, double height);
	~Menu();

	void draw(sf::RenderWindow& window) const;
	void MoveUp();
	void MoveDown();

	void setColor(sf::Sprite& letter, sf::Color color);
	int getPressedItem() const { return selectedItemIndex; }
};

