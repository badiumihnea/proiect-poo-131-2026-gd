#ifndef OOP_MAINMENUSTATE_H
#define OOP_MAINMENUSTATE_H

#include "State.h"
#include "Button.h"

class MainMenuState : public State {
    std::vector<Button> m_buttons;
    sf::Text m_title;
    sf::Text m_subtitle;
public:
    explicit MainMenuState (Game* game);

    void handleEvents(sf::RenderWindow& window, const sf::Event& event) override;
    void update() override;
    void render(sf::RenderWindow& window) override;

    std::string stateName() const override;
};
#endif //OOP_MAINMENUSTATE_H