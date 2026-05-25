#ifndef OOP_ICONSELECTSTATE_H
#define OOP_ICONSELECTSTATE_H

#include "Button.h"
#include "State.h"
#include "Icon.h"
#include "Constants.h"

class IconSelectState : public State {
    std::vector<Icon> m_icons;
    int m_selected = 0;
    sf::Text m_title;
    std::unique_ptr<Button> m_backButton;
    std::pair<float, float> iconPosition(int i) const {
        int n = static_cast<int>(m_icons.size());
        float spacing = 130.f;
        float totalW = spacing * static_cast<float>((n-1));
        float startX = Constants::WINDOW_WIDTH / 2.f - totalW /2.f;
        float cy = Constants::WINDOW_HEIGHT/2.f - 20.f;
        return {startX + spacing * static_cast<float>(i), cy};
    }
public:
    explicit IconSelectState(Game* game);

    void handleEvents(sf::RenderWindow& /*window*/, const sf::Event& event) override;

    void update() override;

    void render(sf::RenderWindow& window) override;

    std::string stateName() const override;
};
#endif //OOP_ICONSELECTSTATE_H