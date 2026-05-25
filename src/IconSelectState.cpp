#include "IconSelectState.h"
#include "Game.h"
#include "MainMenuState.h"
#include "Constants.h"

IconSelectState::IconSelectState(Game *game): m_title(game->getResources().getFont()) {
    m_game = game;
    const sf::Font& font = game->getResources().getFont();
    m_icons = {
        Icon(0, sf::Color(80, 200, 120), sf::Color(0, 120, 255), false),
        Icon(1, sf::Color(80, 200, 120), sf::Color(0, 120, 255), false),
        Icon(2, sf::Color(80, 200, 120), sf::Color(0, 120, 255), false),
        Icon(3, sf::Color(80, 200, 120), sf::Color(0, 120, 255), false),
        Icon(4, sf::Color(80, 200, 120), sf::Color(0, 120, 255), true, sf::Color(255, 0, 144)),
    };
    m_selected = game->getProfile().getIcon().getIconId();
    m_title.setString("Select Icon");
    m_title.setCharacterSize(40u);
    m_title.setFillColor(Constants::COLOR_ACC);
    {
        sf::FloatRect tb = m_title.getLocalBounds();
        m_title.setOrigin({tb.size.x/2.f, tb.size.y/2.f});
    }
    m_title.setPosition({Constants::WINDOW_WIDTH / 2.f, 120.f});
    float bx = Constants::WINDOW_WIDTH / 2.f - 100.f;
    m_backButton = std::make_unique<Button>(bx, 500.f, Constants::BUTTON_WIDTH, Constants::BUTTON_HEIGHT, "Back", font);
}

void IconSelectState::handleEvents(sf::RenderWindow &, const sf::Event &event) {
    if (m_backButton->handleEvent(event)) {
        m_game->changeState(std::make_unique<MainMenuState>(m_game));
        return;
    }

    if (const auto* e = event.getIf<sf::Event::MouseButtonReleased>()) {
        if (e->button == sf::Mouse::Button::Left) {
            for (int i=0; i<static_cast<int>(m_icons.size()); ++i) {
                auto [cx, cy] = iconPosition(i);
                float half = Constants::ICON_DISPLAY_SIZE / 2.f;
                sf::FloatRect slot({cx - half, cy-half}, {Constants::ICON_DISPLAY_SIZE,
                                       Constants::ICON_DISPLAY_SIZE});
                if (slot.contains(sf::Vector2f(static_cast<float>(e->position.x), static_cast<float>(e->position.y)))) {
                    m_selected = i;
                    m_game->getProfile().setIcon(m_icons[i]);
                }
            }
        }
    }

    if (const auto* e = event.getIf<sf::Event::KeyPressed>()) {
        if (e->code == sf::Keyboard::Key::Escape) {
            m_game->changeState(std::make_unique<MainMenuState>(m_game));
        }
    }
}

void IconSelectState::update() {
    sf::Vector2i mp = sf::Mouse::getPosition(m_game->getWindow());
    m_backButton->update(mp);
}

std::string IconSelectState::stateName() const {
    return "Icon Select State";
}

void IconSelectState::render(sf::RenderWindow& window) {
    window.clear(Constants::COLOR_BG);
    window.draw(m_title);
    for (int i=0; i<static_cast<int>(m_icons.size()); ++i) {
        auto [cx, cy] = iconPosition(i);
        float size = Constants::ICON_DISPLAY_SIZE;

        if (i==m_selected) {
            sf::RectangleShape highlight({size + 16.f, size+ 16.f});
            highlight.setFillColor(sf::Color(0, 0, 0));
            highlight.setOutlineThickness(3.f);
            highlight.setOutlineColor(sf::Color(0, 0, 0));
            highlight.setOrigin({(size + 16.f)/2.f, (size + 16.f)/2.f});
            highlight.setPosition({cx, cy});
            window.draw(highlight);
        }
        m_icons[i].draw(window, cx, cy, size);
    }
    sf::Text previewLabel(m_game->getResources().getFont());
    previewLabel.setString("Selected:");
    previewLabel.setCharacterSize(20u);
    previewLabel.setFillColor(sf::Color(200, 200, 200));
    previewLabel.setPosition({Constants::WINDOW_WIDTH/2.f -120.f, Constants::WINDOW_HEIGHT/2.f - 120.f});
    window.draw(previewLabel);

    m_icons[m_selected].draw(window, Constants::WINDOW_WIDTH/2.f + 60.f, Constants::WINDOW_HEIGHT/2.f - 100.f, 50.f);
    m_backButton->draw(window);
}