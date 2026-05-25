#ifndef OOP_PLAYSTATE_H
#define OOP_PLAYSTATE_H

#include "State.h"
#include "MainMenuState.h"

class PlayState : public State {
    float m_playerX;
    float m_playerY;
    float m_velocityY;
    bool m_onGround;
    float m_rotation;
    sf::RectangleShape m_ground;
    sf::Text m_jumpHint;
    int m_jumpHintAlpha = 0;
    bool m_returnPending = false;

    void tryJump();

    void drawPlayerWithRotation(sf::RenderWindow& window);

public:
    explicit PlayState(Game* game);

    void handleEvents(sf::RenderWindow& /*window*/, const sf::Event& event) override;

    void update() override;

    void render(sf::RenderWindow& window) override;

    std::string stateName() const override;
};
#endif //OOP_PLAYSTATE_H