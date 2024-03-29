#pragma once

#include <SFML/Graphics.hpp>
#include "Constants.h"
#include <random>

void drawText(sf::RenderWindow& window, double x, double y, const std::wstring& text);
void openInfo(sf::RenderWindow& window);
void restartGame(std::vector<std::vector<int>>& i_matrix, bool& game_over, int& lines_cleared, int& level);
void startSinglePlayer(sf::RenderWindow& window);
