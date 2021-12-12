#pragma once

#include <SFML/Graphics.hpp>
#include "Constants.h"
#include <vector>
#include <iostream>
using namespace std;


class Tetromino
{
private:
	vector<sf::Vector2i> minos; // vector of points
	sf::Color color;
public:
	Tetromino(int shape, vector<vector<int>>& i_matrix);
	bool move_down(const vector<vector<int>>& i_matrix);
	void move_left(const vector<vector<int>>& i_matrix);
	void move_right(const vector<vector<int>>& i_matrix);
	bool reset(int shape, vector<vector<int>>& i_matrix);
	void update_matrix(vector<vector<int>>& i_matrix);

	vector<sf::Vector2i> get_minos();
	sf::Color get_color();
};

