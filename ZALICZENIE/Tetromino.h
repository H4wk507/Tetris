#pragma once

#include <SFML/Graphics.hpp>
#include "Constants.h"

extern std::vector<sf::Color> cell_color;

class Tetromino
{
private:
	std::vector<sf::Vector2i> minos; // vector czterech punktów
	sf::Color m_color;
	size_t m_shape;
public:
	Tetromino(size_t shape, std::vector<std::vector<int>>& i_matrix);
	bool move_down(const std::vector<std::vector<int>>& i_matrix);
	void move_left(const std::vector<std::vector<int>>& i_matrix);
	void move_right(const std::vector<std::vector<int>>& i_matrix);
	bool reset(const std::vector<std::vector<int>>& i_matrix);
	bool rotate(const std::vector<std::vector<int>>& i_matrix);
	void hard_drop(const std::vector<std::vector<int>>& i_matrix);
	void update_matrix(std::vector<std::vector<int>>& i_matrix) const;
	
	static bool isValidRotate(int x, int y, const std::vector<std::vector<int>>& i_matrix);

	std::vector<sf::Vector2i> get_minos() const;
	std::vector<sf::Vector2i> get_ghost_minos(const std::vector<std::vector<int>> &i_matrix) const;
	size_t get_shape() const;
};

