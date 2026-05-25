#ifndef OOP_CONSTANTS_H
#define OOP_CONSTANTS_H

#include <SFML/Graphics.hpp>

namespace Constants {
    constexpr unsigned int WINDOW_WIDTH = 1200;
    constexpr unsigned int WINDOW_HEIGHT = 720;
    constexpr unsigned int FPS = 60;

    constexpr float PLAYER_SIZE = 50.f;
    constexpr float GROUND_Y = 580.f;
    constexpr float JUMP_VELOCITY = -14.f;
    constexpr float GRAVITY = 0.7f;

    constexpr float ICON_DISPLAY_SIZE = 80.f;
    constexpr float BUTTON_WIDTH = 300.f;
    constexpr float BUTTON_HEIGHT = 55.f;

    const sf::Color COLOR_BG = sf::Color(20, 20, 40);
    const sf::Color COLOR_ACC = sf::Color(255, 180, 0);
    const sf::Color COLOR_ACC2 = sf::Color(0, 200, 255);
    const sf::Color COLOR_ACC3 = sf::Color(100, 100, 180);
    const sf::Color COLOR_BTN_IDLE = sf::Color(40, 40, 80);
    const sf::Color COLOR_BTN_HOVER = sf::Color(60, 60, 120);
    // const sf::Color COLOR_BTN_ACTIVE = sf::Color(255, 180, 0);
    const sf::Color COLOR_TEXT = sf::Color(255, 255, 255);
    // const sf::Color COLOR_TEXT_DARK = sf::Color(20, 20, 40);
    // Comentate pentru a rezolva erorile de pe MacOS
}
#endif //OOP_CONSTANTS_H