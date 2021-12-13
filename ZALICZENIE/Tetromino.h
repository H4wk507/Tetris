#pragma once

#include <SFML/Graphics.hpp>
#include "Constants.h"
#include <vector>
#include <iostream>
using namespace std;


static vector<sf::Color> cell_color{
	sf::Color(1, 3, 50),
	sf::Color(255, 255, 0),
	sf::Color(0, 255, 255),
	sf::Color(0, 0, 255),
	sf::Color(255, 165, 0),
	sf::Color(0, 128, 0),
	sf::Color(128, 0, 128),
	sf::Color(255, 0, 0),
};

class Tetromino
{
private:
	vector<sf::Vector2i> minos; // vector of points
	sf::Color color;
	int shape;
public:
	Tetromino(int shape, vector<vector<int>>& i_matrix);
	bool move_down(const vector<vector<int>>& i_matrix);
	void move_left(const vector<vector<int>>& i_matrix);
	void move_right(const vector<vector<int>>& i_matrix);
	bool reset(vector<vector<int>>& i_matrix);
	void update_matrix(vector<vector<int>>& i_matrix);

	vector<sf::Vector2i> get_minos();
	sf::Color get_color();
	int get_shape();

	void set_mino(int idx, int _x, int _y);
};

