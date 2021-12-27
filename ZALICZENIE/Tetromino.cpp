#include "Tetromino.h"

/* move tetromino by 1 unit down */
bool Tetromino::move_down(const std::vector<std::vector<int>>& i_matrix) {

	for (const auto& mino : minos) {
		if (mino.y >= ROWS - 1 || i_matrix[mino.y + 1.0][mino.x])
			return false;
	}
	for (auto& mino : minos)
		mino.y++;

	return true; // everything's okay, return 1
}

/* move tetromino by 1 unit left */
void Tetromino::move_left(const std::vector<std::vector<int>>& i_matrix) {

	for (const auto& mino : minos) {
		if (mino.x <= 0 || i_matrix[mino.y][mino.x - 1.0])
			return;
	}
	for (auto& mino : minos)
		mino.x--;
}

/* move tetromino by 1 unit right */
void Tetromino::move_right(const std::vector<std::vector<int>>& i_matrix) {
	for (const auto& mino : minos) {
		if (mino.x >= COLUMNS - 1 || i_matrix[mino.y][mino.x + 1.0])
			return;
	}
	for (auto& mino : minos)
		mino.x++;
}

/* reset tetromino's position */
bool Tetromino::reset(const std::vector<std::vector<int>>& i_matrix) {
	static const std::string options = "OIJLSTZ";
	char option = options[m_shape];

	switch (option) {
	case 'O':
		minos[0] = { COLUMNS / 2 - 1, 0 };
		minos[1] = { COLUMNS / 2, 0 };
		minos[2] = { COLUMNS / 2 - 1, 1 };
		minos[3] = { COLUMNS / 2, 1 };
		break;
	case 'I':
		minos[0] = { COLUMNS / 2 - 2, 0 };
		minos[1] = { COLUMNS / 2 - 1, 0 };
		minos[2] = { COLUMNS / 2, 0 };
		minos[3] = { COLUMNS / 2 + 1, 0 };
		break;
	case 'J':
		minos[0] = { COLUMNS / 2 - 2, 0 };
		minos[1] = { COLUMNS / 2 - 1, 0 };
		minos[2] = { COLUMNS / 2, 0 };
		minos[3] = { COLUMNS / 2, 1 };
		break;
	case'L':
		minos[0] = { COLUMNS / 2 - 2, 0 };
		minos[1] = { COLUMNS / 2 - 2, 1 };
		minos[2] = { COLUMNS / 2 - 1, 0 };
		minos[3] = { COLUMNS / 2, 0 };
		break;
	case 'S':
		minos[0] = { COLUMNS / 2 - 2, 1 };
		minos[1] = { COLUMNS / 2 - 1, 0 };
		minos[2] = { COLUMNS / 2 - 1, 1 };
		minos[3] = { COLUMNS / 2, 0 };
		break;
	case 'T':
		minos[0] = { COLUMNS / 2 - 2, 0 };
		minos[1] = { COLUMNS / 2 - 1, 0 };
		minos[2] = { COLUMNS / 2 - 1, 1 };
		minos[3] = { COLUMNS / 2, 0 };
		break;
	case 'Z':
		minos[0] = { COLUMNS / 2 - 2, 0 };
		minos[1] = { COLUMNS / 2 - 1, 0 };
		minos[2] = { COLUMNS / 2 - 1, 1 };
		minos[3] = { COLUMNS / 2, 1 };
		break;
	default:
		break;
	}

	for (const auto& mino : minos) {
		// jeœli tetromino respi siê na zajêtej pozycji
		// gra jest skoñczona
		if (i_matrix[mino.y][mino.x])
			return false;
	}

	return true; // gramy dalej
}

/* update matrix grid with current tetromino */
void Tetromino::update_matrix(std::vector<std::vector<int>>& i_matrix) const {
	for (const auto& mino : minos)
		i_matrix[mino.y][mino.x] = 1 + m_shape;
}
 
Tetromino::Tetromino(size_t shape, std::vector<std::vector<int>>& i_matrix) {
	minos.resize(4);
	m_shape = shape;
	m_color = cell_color[shape + 1];
}

std::vector<sf::Vector2i> Tetromino::get_ghost_minos(const std::vector<std::vector<int>> &i_matrix) const {
	bool fall = true;
	size_t dy = 0;
	std::vector<sf::Vector2i> ghost_minos = minos;
	while (fall) {
		dy++;
		for (const auto& mino : minos) {
			if (mino.y + dy >= ROWS || i_matrix[mino.y + dy][mino.x]) {
				fall = false;
				break;
			}
		}
	}
	for (auto& mino : ghost_minos)
		mino.y += dy - 1; // dy is the position that was invalid so we increase y by dy - 1
	
	return ghost_minos;
}	

bool Tetromino::isValidRotate(int x, int y, const std::vector<std::vector<int>> &i_matrix) {
	return !(x < 0 || y < 0 || y >= ROWS || x >= COLUMNS || i_matrix[y][x]);
}

bool Tetromino::rotate(const std::vector<std::vector<int>> &i_matrix) {
	sf::Vector2i p = minos[1]; // center of rotation point
	std::vector<int> dx(4);
	std::vector<int> dy(4);
	for (int i = 0; i < 4; i++) {
		dx[i] = p.x - minos[i].y + p.y;
		dy[i] = p.y + minos[i].x - p.x;
		if (!isValidRotate(dx[i], dy[i], i_matrix))
			return false;
	}
	for (int i = 0; i < 4; i++)
		minos[i] = { dx[i], dy[i] };

	return true;
}

void Tetromino::hard_drop(const std::vector<std::vector<int>>& i_matrix) {
	minos = get_ghost_minos(i_matrix);
}

/*** getters ***/
std::vector<sf::Vector2i> Tetromino::get_minos() const {
	return minos;
}

size_t Tetromino::get_shape() const {
	return m_shape;
}