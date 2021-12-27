#include "Funkcje.h"
#include "Tetromino.h"

/*
* wprowadz wallkicka
* 
* 
* 
*/

/* color of certain cell */
std::vector<sf::Color> cell_color{
	sf::Color(1, 3, 50), // 
	sf::Color(255, 255, 0),
	sf::Color(0, 255, 255),
	sf::Color(0, 0, 255),
	sf::Color(255, 165, 0),
	sf::Color(0, 128, 0),
	sf::Color(128, 0, 128),
	sf::Color(255, 0, 0),
	sf::Color(127, 127, 127), // szary
};

void drawText(sf::RenderWindow& window, float x, float y, const std::string& text) {
	float char_x = x;
	float char_y = y;

	sf::Sprite char_sprite;
	sf::Texture font_texture;
	font_texture.loadFromFile("Font.png");

	int char_width = font_texture.getSize().x / 96;
	char_sprite.setTexture(font_texture);

	for (const char& letter : text) {
		if (letter == '\n') {
			char_x = x;
			char_y += font_texture.getSize().y;
			continue;
		}

		char_sprite.setPosition(char_x, char_y);
		char_sprite.setTextureRect(sf::IntRect(char_width * (letter - 32), 0, char_width, font_texture.getSize().y));
		char_sprite.setColor(sf::Color(255, 255, 255));
		char_x += char_width;
		window.draw(char_sprite);
	}
}

void openInfo(sf::RenderWindow& window) {
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			switch (event.type) {
			case sf::Event::KeyPressed:
				switch (event.key.code) {
				case sf::Keyboard::Q:
				case sf::Keyboard::Escape:
				case::sf::Keyboard::Enter:
					return;
				}
			}
		}
		window.clear(sf::Color(1, 3, 50));
		drawText(window, 0.005f * CELL_SIZE * COLUMNS, 0.005f * CELL_SIZE * ROWS, "test");

		window.display();
	}
}

void restartGame(std::vector<std::vector<int>>& i_matrix, bool& game_over, int& lines_cleared, int& level) {
	game_over = lines_cleared = 0;
	level = 1;
	for (auto& row : i_matrix)
		fill(row.begin(), row.end(), 0);
}

void startSinglePlayer(sf::RenderWindow& window) {
	sf::RectangleShape cell(sf::Vector2f(CELL_SIZE - 1, CELL_SIZE - 1));

	/*** preview border ***/
	sf::RectangleShape preview_border(sf::Vector2f(5 * CELL_SIZE, 5 * CELL_SIZE));
	preview_border.setFillColor(sf::Color(0, 0, 0));
	preview_border.setOutlineThickness(-1);
	preview_border.setPosition(CELL_SIZE * (1.5f * COLUMNS - 2.5f), CELL_SIZE * (0.25f * ROWS - 2.5f));
	
	std::vector<std::vector<int>> matrix(ROWS, std::vector<int>(COLUMNS, 0));
	std::vector<bool> clear_lines(ROWS, false);

	int lines_cleared = 0;
	bool game_over = false;
	bool freeze = false;

	double timer = 0;
	sf::Clock clock;
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int_distribution<int> distr(0, NUM_SHAPES - 1);

	/*** wygeneruj pierwszy blok ***/
	Tetromino tmp(distr(mt), matrix);
	Tetromino next(distr(mt), matrix);
	tmp.reset(matrix);
	next.reset(matrix);
	
	/*** glówna pêtla ***/
	while (window.isOpen()) {
		double time = clock.getElapsedTime().asSeconds();
		clock.restart();
		timer += time;
		int level = 1 + lines_cleared / 10;
		double delay = 0.5 - 0.005 * (level - 1.0);
		bool rotate = 0;
		bool harddrop = 0;

		/*** handle user input ***/
		sf::Event event;
		while (window.pollEvent(event)) {
			switch (event.type) {
			case sf::Event::KeyPressed:
				freeze = false;
				switch (event.key.code) {
				case sf::Keyboard::Left:
					tmp.move_left(matrix);
					break;
				case sf::Keyboard::Right:
					tmp.move_right(matrix); 
					break;
				case sf::Keyboard::Up:
					rotate = true;
					break;
				case sf::Keyboard::Down:
					tmp.move_down(matrix);
					break;
				case sf::Keyboard::Space:
					harddrop = true;
					break;
				case sf::Keyboard::Escape:
				case sf::Keyboard::P:
					freeze = true;
					break;
				case sf::Keyboard::R:
					if (game_over)
						restartGame(matrix, game_over, lines_cleared, level);
					break;
				case sf::Keyboard::Q:
					if (game_over)
						return;
					break;
				}
			}
		}
		window.clear();

		/*** writing minos ***/
		for (int y = 0; y < ROWS; y++) {
			for (int x = 0; x < COLUMNS; x++) {
				if (!clear_lines[y]) {
					cell.setPosition(1.f * CELL_SIZE * x, 1.f * CELL_SIZE * y);
					
					// if game is over, turn every color to gray
					if (game_over && matrix[y][x])
						cell.setFillColor(cell_color[8]);
					else
						cell.setFillColor(cell_color[matrix[y][x]]);

					if (timer > delay) {
						if (!freeze) {
							// jeœli klocek nie mo¿e dalej spadaæ, zaktualizuj macierz
							if (!tmp.move_down(matrix)) {
								tmp.update_matrix(matrix);

								/* check if any line has to be cleared */
								for (int row = 0; row < ROWS; row++) {
									bool line_cleared = true;
									for (int col = 0; col < COLUMNS; col++) {
										if (!matrix[row][col]) {
											line_cleared = false;
											break;
										}
									}

									/* line has to be cleared */
									if (line_cleared) {
										lines_cleared++;
										clear_lines[row] = true;

										/* przenies wszystke bloki z gory na dol */
										for (size_t rr = row; rr > 0; rr--) {
											for (size_t cc = 0; cc < COLUMNS; cc++) {
												matrix[rr][cc] = matrix[rr - 1][cc];
												matrix[rr - 1][cc] = 0;
											}
										}
									}
								}
								
								// wygeneruj nastêpny blok
								if (!game_over) {
									tmp = next;
									next = Tetromino(distr(mt), matrix);
									next.reset(matrix);
								}

								// jeœli nie mo¿emy postawiæ bloku; koniec gry
								if (!tmp.reset(matrix))
									game_over = true;
							}
						}
						timer = 0; // zresetuj timer
					}
					window.draw(cell);
				} // freeze
			} // x
		} // y
		std::fill(clear_lines.begin(), clear_lines.end(), 0); // zresetuj vektor clear_lines

		/* rotacje */
		if (rotate && tmp.get_shape() != 0)
			tmp.rotate(matrix);
		
		cell.setFillColor(cell_color[tmp.get_shape() + 1]);
		if (harddrop)
			tmp.hard_drop(matrix);

		/* narysuj blok widmo */
		cell.setFillColor(cell_color[8]); // szary
		for (const auto& mino : tmp.get_ghost_minos(matrix)) {
			cell.setPosition(CELL_SIZE * mino.x, CELL_SIZE * mino.y);
			window.draw(cell);
		}

		/* narysuj spadaj¹cy blok */
		if (!game_over) {
			cell.setFillColor(cell_color[tmp.get_shape() + 1]);
			for (const auto& mino : tmp.get_minos()) {
				cell.setPosition(CELL_SIZE * mino.x, CELL_SIZE * mino.y);
				window.draw(cell);
			}
		}

		/* narysuj okno z nastêpnym blokiem */
		cell.setFillColor(cell_color[next.get_shape() + 1]);
		cell.setSize(sf::Vector2f(CELL_SIZE - 1, CELL_SIZE - 1));
		window.draw(preview_border);

		for (const auto& mino : next.get_minos()) {
			float x = CELL_SIZE * mino.x + 8.5f * COLUMNS;
			float y = CELL_SIZE * mino.y + ROWS * 1.7f;

			size_t shp = next.get_shape();
			if (shp == 0 || shp == 1) {
				x -= 0.5f * COLUMNS;
			}
			cell.setPosition(x, y);
			window.draw(cell);
		}
		
		drawText(window, CELL_SIZE * (0.5f + COLUMNS), 0.5f * CELL_SIZE * ROWS, 
			"Linie:" + std::to_string(lines_cleared) + "\nLevel:" + std::to_string(level));

		if (game_over)
			drawText(window, CELL_SIZE * (0.5f + COLUMNS), CELL_SIZE * ROWS * 0.5f, 
				"\n\n\n(r)estart\n(q)uit");
		if (freeze)
			drawText(window, CELL_SIZE * 0.25f * COLUMNS, CELL_SIZE * ROWS * 0.5f, "Pause");

		window.display();
	} // window
} // void startSinglePlayer()