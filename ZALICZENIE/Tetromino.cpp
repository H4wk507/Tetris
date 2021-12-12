#include "Tetromino.h"

int Tetromino::maxY() {
	int best = 0;
	for (const auto& mino : minos) {
		if (mino.y > best) 
			best = mino.y;
	}
	return best;
}

int Tetromino::minX() {
	int best = COLUMNS;
	for (auto& mino : minos) {
		if (mino.x < best)
			best = mino.x;
	}
	return best;
}

int Tetromino::maxX() {
	int best = 0;
	for (auto& mino : minos) {
		if (mino.x > best)
			best = mino.x;
	}
	return best;
}

bool Tetromino::move_down(const vector<vector<int>>& i_matrix) {
	int maxy = Tetromino::maxY();

	for (auto& mino : minos) {
		if (ROWS == mino.y + 1)
			return 0;
		if (i_matrix[1 + static_cast<size_t>(mino.y)][mino.x] == 1)
			return 0;
	}

	for (auto& mino : minos) {
		mino.y++;
	}

	return 1;
}

void Tetromino::move_left(const vector<vector<int>>& i_matrix) {
	int minx = minX();
	for (auto& mino : minos) {
		if (mino.x == 0)
			return;

		if (i_matrix[mino.y][static_cast<size_t>(mino.x) - 1] == 1)
			return;
	}

	for (auto& mino : minos) {
		mino.x--;
	}
}

void Tetromino::move_right(const vector<vector<int>>& i_matrix) {
	int maxx = maxX();
	for (auto& mino : minos) {
		if (mino.x == COLUMNS - 1)
			return;

		if (i_matrix[mino.y][static_cast<size_t>(mino.x) + 1] == 1)
			return;
	}

	for (auto& mino : minos) {
		mino.x++;
	}
}

void Tetromino::reset(char shape) {
	
	switch (shape) {
		// i j l s t z 
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
}

void Tetromino::update_matrix(vector<vector<int>>& i_matrix) {
	for (auto& mino : minos)
		i_matrix[mino.y][mino.x] = 1;
}
 
Tetromino::Tetromino(int shape) {
	static const char* options = "OIJLSTZ";
	char option = options[shape];

	switch (option) {
	case 'O':
	case 'I': 
	case 'L': 
	case 'J': 
	case 'S': 
	case 'T':
	case 'Z':
		minos.resize(4);
		reset(option);
		break;
	default:
		break;

	}
}

vector<sf::Vector2i> Tetromino::get_minos() {
	return minos;
}