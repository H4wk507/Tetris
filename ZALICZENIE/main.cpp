#include <iostream>
#include <SFML/Graphics.hpp>
#include "Menu.h"
#include "Funkcje.h"

using namespace std;

int main()
{
    /*** load window ***/
    sf::RenderWindow window;
    window.create(sf::VideoMode::VideoMode(CELL_SIZE * COLUMNS * SCREEN_RESIZE,
        CELL_SIZE * ROWS * SCREEN_RESIZE), "Tetris", sf::Style::Default);
    window.setVerticalSyncEnabled(true);
    window.setView(sf::View(sf::FloatRect(0, 0, CELL_SIZE * COLUMNS, CELL_SIZE * ROWS)));

    /*** load cursor ***/
    sf::Cursor cursor;
    if (cursor.loadFromSystem(sf::Cursor::Arrow))
        window.setMouseCursor(cursor);

    /*** load menu ***/
    Menu menu(window.getSize().x, window.getSize().y);
    
    /*** main loop ***/
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {

            /*** handle events ***/
            switch (event.type) {
            case sf::Event::KeyPressed:
                switch (event.key.code) {
                case sf::Keyboard::Up:
                    menu.MoveUp(); break;
                case sf::Keyboard::Down:
                    menu.MoveDown(); break;
                case sf::Keyboard::Return:
                    switch (menu.getPressedItem()) {
                    case 0:
                        startSinglePlayer(window);
                        cout << "Play.\n"; break;
                    case 1:
                        cout << "Options.\n"; break;
                    case 2: // exit
                        window.close(); break;
                    default:
                        break;
                    }
                default:
                    break;
                }
            case sf::Event::MouseButtonReleased:
                for (int option = 0; option < NUM_ITEMS; option++) {
                    switch (menu.isMouseOver(window, option)) {
                    case 0:
                        cout << "Play.\n"; break;
                    case 1:
                        cout << "Options.\n"; break;
                    case 2:
                        window.close(); break;
                    default:
                        break;
                    }
                }
                    

            case sf::Event::Closed:
                //window.close(); break;
            default:
                break;
            }
        }

        /*** draw to screen ***/
        window.clear(sf::Color(100, 100, 255));
        menu.draw(window);
        window.display();
    }

    return 0;
}