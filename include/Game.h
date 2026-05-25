#ifndef OOP_GAME_H
#define OOP_GAME_H

#include <SFML/Graphics.hpp>
#include "ResourceManager.h"
#include "PlayerProfile.h"

class State;
class Game {
    sf::RenderWindow m_window;
    ResourceManager m_resources;
    PlayerProfile m_profile;
    std::unique_ptr<State> m_currentState;
    std::unique_ptr<State> m_pendingState;
    bool m_fullscreen=false;
    void applyWindowSettings(bool fullscreen);
public:
    Game();

    void changeState(std::unique_ptr<State> newState);

    sf::RenderWindow& getWindow();

    ResourceManager& getResources();

    PlayerProfile& getProfile();

    bool isFullscreen() const;

    void toggleFullscreen();
    void run();

    std::string getStateName() const;

    friend std::ostream& operator<<(std::ostream& os, const Game& game);
};
#endif //OOP_GAME_H