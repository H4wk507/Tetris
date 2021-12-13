#include "Tetromino.h"


bool Tetromino::move_down(const vector<vector<int>>& i_matrix) {

	for (auto& mino : minos) {
		if (ROWS == mino.y + 1)
			return 0;
		if (i_matrix[1 + static_cast<size_t>(mino.y)][mino.x] > 0)
			return 0;
	}

	for (auto& mino : minos) {
		mino.y++;
	}

	return 1;
}

void Tetromino::move_left(const vector<vector<int>>& i_matrix) {

	for (auto& mino : minos) {
		if (mino.x <= 0 || mino.y < 0)
			return;

		if (i_matrix[mino.y][static_cast<size_t>(mino.x) - 1] > 0)
			return;
	}

	for (auto& mino : minos) {
		mino.x--;
	}
}

void Tetromino::move_right(const vector<vector<int>>& i_matrix) {
	for (auto& mino : minos) {
		if (mino.x >= COLUMNS - 1 || mino.y < 0)
			return;

		if (i_matrix[mino.y][static_cast<size_t>(mino.x) + 1] > 0)
			return;
	}

	for (auto& mino : minos) {
		mino.x++;
	}
}

bool Tetromino::reset(vector<vector<int>>& i_matrix) {
	static const char* options = "OIJLSTZ";
	char option = options[shape];

	switch (option) {
	case 'O': // square
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
		minos[0] = {COLUMNS / 2 - 2, 1};
		minos[1] = {COLUMNS / 2 - 1, 0};
		minos[2] = {COLUMNS / 2 - 1, 1};
		minos[3] = {COLUMNS / 2, 0};
		break;
	case 'T':
		minos[0] = {COLUMNS / 2 - 2, 0};
		minos[1] = {COLUMNS / 2 - 1, 0};
		minos[2] = {COLUMNS / 2 - 1, 1};
		minos[3] = {COLUMNS / 2, 0};
		break;
	case 'Z':
		minos[0] = {COLUMNS / 2 - 2, 0};
		minos[1] = {COLUMNS / 2 -1, 0};
		minos[2] = {COLUMNS / 2 - 1, 1};
		minos[3] = {COLUMNS / 2, 1};
		break;
	default:
		cerr << "Incorrect shape!\n";
		break;
	}

	for (auto& mino : minos)
		if (i_matrix[mino.y][mino.x]) return 0;

	return 1;
}

void Tetromino::update_matrix(vector<vector<int>>& i_matrix) {
	for (auto& mino : minos) {
		if (mino.y < 0)
			continue;

		i_matrix[mino.y][mino.x] = 1 + shape;
	}
}
 
Tetromino::Tetromino(int i_shape, vector<vector<int>>& i_matrix) {
	static const char* options = "OIJLSTZ";
	char option = options[i_shape];
	shape = i_shape;

	switch (option) {
	case 'O':
	case 'I': 
	case 'L': 
	case 'J': 
	case 'S': 
	case 'T':
	case 'Z':
		minos.resize(4);
		color = cell_color[static_cast<size_t>(shape) + 1];
		break;
	default:
		break;

	}
}

vector<sf::Vector2i> Tetromino::get_minos() {
	return minos;
}

sf::Color Tetromino::get_color() {
	return color;
}

int Tetromino::get_shape() {
	return shape;
}

void Tetromino::set_mino(int idx, int _x, int _y) {
	minos[idx].x = _x;
	minos[idx].y = _y;
} 
