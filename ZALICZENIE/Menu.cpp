#include "Menu.h"


Menu::Menu(double width, double height) {
	if (!font.loadFromFile("ARIAL.ttf")) {
		std::cerr << "Blad przy wczytywaniu czcionki.\n";
	}

	const wchar_t* options[] = { L"Graj", L"Opcje", L"WyjdŸ" }; /* dostepne opcje */
	for (int i = 0; i < NUM_ITEMS; i++) {
		menu[i].setFont(font);
		if (i == 0)
			menu[i].setFillColor(sf::Color::Red);
		else
			menu[i].setFillColor(sf::Color::White);
		menu[i].setString(options[i]);
		menu[i].setPosition(sf::Vector2f(width / 2.0 - menu[i].getGlobalBounds().width / 2.0, 
				height / (NUM_ITEMS + 1.0) * (i + 1.0)));
	}
	selectedItemIndex = 0;
}

Menu::~Menu() { };

void Menu::draw(sf::RenderWindow& window) {
	for (const auto& option : menu)
		window.draw(option);
}

void Menu::MoveUp() {
	if (selectedItemIndex > 0) {
		menu[selectedItemIndex].setFillColor(sf::Color::White);
		selectedItemIndex--;
		menu[selectedItemIndex].setFillColor(sf::Color::Red);
	}
}

void Menu::MoveDown() {
	if (selectedItemIndex < NUM_ITEMS - 1) {
		menu[selectedItemIndex].setFillColor(sf::Color::White);
		selectedItemIndex++;
		menu[selectedItemIndex].setFillColor(sf::Color::Red);
	}
}

int Menu::isMouseOver(sf::RenderWindow& window, int item) {
	double mouseX = sf::Mouse::getPosition(window).x; 
	double mouseY = sf::Mouse::getPosition(window).y;

	double btnPosX = menu[item].getPosition().x; 
	double btnPosY = menu[item].getPosition().y;

	double btnPosXWidth = btnPosX + menu[item].getLocalBounds().width;
	double btnPosYHeight = btnPosY + menu[item].getLocalBounds().height;

	if (mouseX >= btnPosX && mouseX <= btnPosXWidth && mouseY >= btnPosY && mouseY <= btnPosYHeight) {
		return item;
	}

	return -1;
}
