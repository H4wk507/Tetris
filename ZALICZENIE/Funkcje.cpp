#include "Funkcje.h"
#include "Tetromino.h"



// update the state of tetrominos
void update(vector<Tetromino>& minos, vector<vector<int>>& matrix) {
	for (auto& a : matrix)
		fill(a.begin(), a.end(), 0);
	for (auto& mino : minos)
		mino.update_matrix(matrix);
}

void startSinglePlayer(sf::RenderWindow& window) {
	sf::RectangleShape cell(sf::Vector2f(CELL_SIZE - 1, CELL_SIZE - 1));
	vector<vector<int>> matrix(ROWS + 1,  vector<int>(COLUMNS + 1, 0));

	double timer = 0;
	double delay = 0.3;
	sf::Clock clock;
	srand(time(nullptr));

	vector<Tetromino> minos; // minos that have LANDED
	Tetromino tmp(rand() % NUM_SHAPES);

	while (window.isOpen()) {
		double time = clock.getElapsedTime().asSeconds();
		clock.restart();
		timer += time;

		sf::Event event;
		while (window.pollEvent(event)) {
			switch (event.type) {
			case sf::Event::KeyPressed:
				switch (event.key.code) {
				case sf::Keyboard::Left:
					tmp.move_left(matrix);
					update(minos, matrix);
					break;
				case sf::Keyboard::Right:
					tmp.move_right(matrix); 
					update(minos, matrix);
					break;
				}
			}
		}
		window.clear();

		for (int y = 0; y < ROWS; y++) {
			for (int x = 0; x < COLUMNS; x++) {
				cell.setPosition(1.0 * CELL_SIZE * x, 1.0 * CELL_SIZE * y);
				
				if (matrix[y][x] != 1) // if field not occupied
					cell.setFillColor(sf::Color(1, 3, 50));

				for (auto& a : tmp.get_minos()) 
					if (x == a.x && y == a.y) 
						cell.setFillColor(sf::Color(255, 0, 0));
				if (matrix[y][x] == 1)
					cell.setFillColor(sf::Color(255, 0, 0));

				if (timer > delay) {
					if (!tmp.move_down(matrix)) {
						minos.push_back(tmp);
						tmp = Tetromino(rand() % NUM_SHAPES);
					}

					// 2 tablice, prev state i curr state
					// jesli curr state najezdza na blok
					// to zatrzymaj prev state
					// else zapisz do prev state curr state
					// int test = minos.back().move_down(matrix);
					update(minos, matrix);

					timer = 0; // reset timer
				}
				window.draw(cell);
			}
		}
		window.display();
	}
}