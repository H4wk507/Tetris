#include "Menu.h"

Menu::Menu(double width, double height) {
	m_menu.resize(NUM_ITEMS);
	font_texture.loadFromFile("Font.png");

	double char_x = width;
	double char_y = height;
	double char_width = font_texture.getSize().x / 96;
	
	const std::vector<std::string> options = { "Graj", "Info", "Wyjdz" }; /* dostepne opcje */
	sf::Sprite char_sprite;
	size_t ITEM_SIZE;

	for (int i = 0; i < NUM_ITEMS; i++) {
		ITEM_SIZE = options[i].size();
		m_menu[i].resize(ITEM_SIZE);
		for (size_t j = 0; j < ITEM_SIZE; j++) {
			char_sprite.setTexture(font_texture);
			char_sprite.setPosition(char_x, char_y);
			char_sprite.setTextureRect(sf::IntRect(char_width * (static_cast<double>(options[i][j]) - 32), 0, char_width, font_texture.getSize().y));
			char_sprite.setColor((i == 0) ? sf::Color::Red : sf::Color::White);

			char_x += char_width;
			m_menu[i][j] = char_sprite;
		}
		char_x = width; // reset x
		char_y += 2.0 * font_texture.getSize().y; // przenieœ y do nowej lini
	}
	selectedItemIndex = 0;
}

Menu::~Menu() { };

void Menu::draw(sf::RenderWindow& window) const {
	for (const auto& option : m_menu)
		for (const auto& letter : option)
			window.draw(letter);
}

void Menu::MoveUp() {
	if (selectedItemIndex > 0) {
		for (auto& letter : m_menu[selectedItemIndex])
			setColor(letter, sf::Color::White);
		selectedItemIndex--;
		for (auto& letter : m_menu[selectedItemIndex])
			setColor(letter, sf::Color::Red);
	}
}

void Menu::MoveDown() {	
	if (selectedItemIndex < NUM_ITEMS - 1) {
		for (auto& letter : m_menu[selectedItemIndex])
			setColor(letter, sf::Color::White);
		selectedItemIndex++;
		for (auto& letter : m_menu[selectedItemIndex])
			setColor(letter, sf::Color::Red);
	}
}

void Menu::setColor(sf::Sprite& letter, sf::Color color) {
	letter.setColor(color);
}