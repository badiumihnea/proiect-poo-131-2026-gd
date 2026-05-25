#ifndef OOP_SETTINGSSTATE_H
#define OOP_SETTINGSSTATE_H

#include "State.h"
#include "Button.h"
#include "MainMenuState.h"

class SettingsState : public State {
    sf::Text m_title;
    std::unique_ptr<Button> m_fullscreenButton;
    std::unique_ptr<Button> m_backButton;
    sf::Text m_volumeLabel;
    sf::RectangleShape m_sliderTrack;
    sf::CircleShape m_sliderThumb;
    sf::Text m_debugTip;

    std::string fullscreenLabel() const;

public:
    explicit SettingsState(Game* game);

    void handleEvents(sf::RenderWindow& /*window*/, const sf::Event& event) override;

    void update() override;

    void render(sf::RenderWindow& window) override;

    std::string stateName() const override;
};
#endif //OOP_SETTINGSSTATE_H