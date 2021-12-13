#include "Funkcje.h"
#include "Tetromino.h"

void startSinglePlayer(sf::RenderWindow& window) {
	sf::RectangleShape cell(sf::Vector2f(CELL_SIZE - 1, CELL_SIZE - 1));
	vector<vector<int>> matrix(ROWS, vector<int>(COLUMNS, 0));
	vector<bool> clear_lines(ROWS, 0);

	double timer = 0;
	double delay = 0.07;
	sf::Clock clock;
	srand(time(nullptr));

	int option = rand() % NUM_SHAPES;
	Tetromino tmp(0, matrix);
	tmp.reset(matrix);
		
	while (window.isOpen()) {
		double time = clock.getElapsedTime().asSeconds();
		clock.restart();
		timer += time;
		bool rotate = 0;

		sf::Event event;
		while (window.pollEvent(event)) {
			switch (event.type) {
			case sf::Event::KeyPressed:
				switch (event.key.code) {
				case sf::Keyboard::Left:
					tmp.move_left(matrix);
					break;
				case sf::Keyboard::Right:
					tmp.move_right(matrix); 
					break;
				case sf::Keyboard::Up:
					rotate = 1;
					break;
				}
			}
		}
		window.clear();

		for (int y = 0; y < ROWS; y++) {
			for (int x = 0; x < COLUMNS; x++) {
				if (!clear_lines[y]) {
					cell.setPosition(static_cast<float>(CELL_SIZE * x), static_cast<float>(CELL_SIZE * y));
					cell.setFillColor(cell_color[matrix[y][x]]);

					if (timer > delay) {
						if (!tmp.move_down(matrix)) {
							tmp.update_matrix(matrix);

							int row_num = 0;
							for (int i = 0; i < ROWS; i++) {
								bool line_cleared = 1;
								for (int j = 0; j < COLUMNS; j++) {
									if (matrix[i][j] == 0) {
										line_cleared = 0;
										break;
									}
								}

								if (line_cleared) {
									clear_lines[i] = 1;
									// przenies wszystke bloki z gory na dol
									for (size_t j = row_num; j > 0; j--) {
										for (size_t k = 0; k < COLUMNS; k++) {
											matrix[j][k] = matrix[j - 1][k];
											matrix[j - 1][k] = 0;
										}
									}
								}
								row_num++;
							}
							//fill(clear_lines.begin(), clear_lines.end(), 0);
							// generate next tetromino
							option = rand() % NUM_SHAPES;
							tmp = Tetromino(0, matrix);

							// if we cant place a block; reset the game
							if (!tmp.reset(matrix))
								for (auto& row : matrix)
									fill(row.begin(), row.end(), 0);
						}
						timer = 0; // reset timer
					}
					window.draw(cell);
				}
			} /// x
		}/// y
		fill(clear_lines.begin(), clear_lines.end(), 0);

		// rotate
		if (rotate && tmp.get_shape() != 0) {
			sf::Vector2i p = tmp.get_minos()[1]; // center of rotation point
			for (int i = 0; i < 4; i++) {
				int x = tmp.get_minos()[i].y - p.y;
				int y = tmp.get_minos()[i].x - p.x;
				tmp.set_mino(i, p.x - x, p.y + y); // set_mino(index, new_x, new_y);
			}
		}

		// drawing falling tetromino
		cell.setFillColor(cell_color[1 + static_cast<size_t>(tmp.get_shape())]);
		for (auto& mino : tmp.get_minos()) {
			cell.setPosition(CELL_SIZE * mino.x, CELL_SIZE * mino.y);
			window.draw(cell);
		}
		window.display();
	} /// window
} /// main