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

	vector<Tetromino> minos;
	Tetromino tmp(rand() % NUM_SHAPES);
	minos.push_back(tmp);

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
					minos.back().move_left(matrix);
					update(minos, matrix);
					break;
				case sf::Keyboard::Right:
					minos.back().move_right(matrix); 
					update(minos, matrix);
					break;
				}
			}
		}
		window.clear();

		for (int y = 0; y < ROWS; y++) {
			for (int x = 0; x < COLUMNS; x++) {
				cell.setPosition(1.0 * CELL_SIZE * x, 1.0 * CELL_SIZE * y);
				
				if (matrix[y][x] == 1)
					cell.setFillColor(sf::Color(255, 0, 0));
				else
					cell.setFillColor(sf::Color(1, 3, 50));

				if (timer > delay) {
					update(minos, matrix);
					if (!minos.back().move_down(matrix)) {
						// if block can't move down; create new one
						Tetromino tmp(rand() % NUM_SHAPES);
						minos.push_back(tmp);
					}	
					timer = 0; // reset timer
				}
				window.draw(cell);
			}
		}
		window.display();
	}
}