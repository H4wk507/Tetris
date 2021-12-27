#include <SFML/Graphics.hpp>
#include "Menu.h"
#include "Funkcje.h"

/*
*         ___________       __           .__
*         \__    ___/____ _/  |_ _______ |__|  ______
*           |    | _/ __ \\   __\\_  __ \|  | /  ___/
*           |    | \  ___/ |  |   |  | \/|  | \___ \
*           |____|  \___  >|__|   |__|   |__|/____  >
*                       \/                        \/ 
*/

int main()
{
    /*** wczytaj okno ***/
    sf::RenderWindow window;
    window.create(sf::VideoMode::VideoMode(2 * CELL_SIZE * COLUMNS * SCREEN_RESIZE,
        CELL_SIZE * ROWS * SCREEN_RESIZE), "Tetris", sf::Style::Default);
    window.setView(sf::View(sf::FloatRect(0, 0, 2 * CELL_SIZE * COLUMNS, CELL_SIZE * ROWS)));
    
    /*** wczytaj menu ***/
    Menu menu(0.8 * CELL_SIZE * COLUMNS, 0.25 * CELL_SIZE * ROWS);
    
    /*** główna pętla ***/
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {

            /*** input użytkownika ***/
            switch (event.type) {
            case sf::Event::KeyPressed:
                switch (event.key.code) {
                case sf::Keyboard::Up:
                    menu.MoveUp(); 
                    break;
                case sf::Keyboard::Down:
                    menu.MoveDown(); 
                    break;
                case sf::Keyboard::Q:
                    window.close();
                    break;
                case sf::Keyboard::Enter:
                    switch (menu.getPressedItem()) {
                    case 0:
                        startSinglePlayer(window);
                        break;
                    case 1:
                        openInfo(window);
                        break;
                    case 2:
                        window.close();
                        break;
                    default:
                        break;
                    }
                default:
                    break;
                }
            }
        }
        /*** rysuj na ekran ***/
        window.clear(sf::Color(1, 3, 50)); // ciemnoniebieski
        menu.draw(window);
        window.display();
    }

    return 0;
}