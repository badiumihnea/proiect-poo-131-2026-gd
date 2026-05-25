#include "SettingsState.h"
#include "Game.h"
#include "Constants.h"

std::string SettingsState::fullscreenLabel() const {
    return m_game->isFullscreen() ? "Fullscreen : ON" : "Fullscreen : OFF";
}

SettingsState::SettingsState(Game *game): m_title(game->getResources().getFont()), m_volumeLabel(game->getResources().getFont()),
                                          m_debugTip(game->getResources().getFont()) {
    m_game = game;
    const sf::Font& font = game->getResources().getFont();
    m_title.setString("Settings");
    m_title.setCharacterSize(42u);
    m_title.setFillColor(Constants::COLOR_ACC);
    {
        sf::FloatRect tb = m_title.getLocalBounds();
        m_title.setOrigin({tb.size.x/2.f, tb.size.y/2.f});
    }
    m_title.setPosition({Constants::WINDOW_WIDTH / 2.f, 120.f});
    float cx = Constants::WINDOW_WIDTH/2.f - Constants::BUTTON_WIDTH/2.f;
    m_fullscreenButton = std::make_unique<Button>(cx, 240.f, Constants::BUTTON_WIDTH,
                                                  Constants::BUTTON_HEIGHT, fullscreenLabel(), font);

    m_volumeLabel.setString("Volume (Under construction)");
    m_volumeLabel.setCharacterSize(20u);
    m_volumeLabel.setFillColor(sf::Color(200, 200, 200));
    {
        sf::FloatRect vb = m_volumeLabel.getLocalBounds();
        m_volumeLabel.setOrigin({vb.size.x/2.f, vb.size.y/2.f});
    }
    m_volumeLabel.setPosition({Constants::WINDOW_WIDTH/2.f, 360.f});

    m_sliderTrack.setSize({360.f, 8.f});
    m_sliderTrack.setFillColor(sf::Color(80, 80, 120));
    m_sliderTrack.setPosition({Constants::WINDOW_WIDTH/2.f-180.f, 390.f});
    m_sliderThumb.setRadius(12.f);
    m_sliderThumb.setFillColor(Constants::COLOR_ACC);
    m_sliderThumb.setOrigin({12.f, 12.f});
    m_sliderThumb.setPosition({Constants::WINDOW_WIDTH/2.f, 394.f});

    m_backButton = std::make_unique<Button>(cx, 500.f, Constants::BUTTON_WIDTH,
                                            Constants::BUTTON_HEIGHT, "Back", font);

    m_debugTip.setString("Tip: Press F3 for debug info in console :)");
    m_debugTip.setCharacterSize(20u);
    m_debugTip.setFillColor(sf::Color(200, 200, 200));
    {
        sf::FloatRect db = m_debugTip.getLocalBounds();
        m_debugTip.setOrigin({db.size.x/2.f, db.size.y/2.f});
    }
    m_debugTip.setPosition({Constants::WINDOW_WIDTH/2.f, 420.f});
}

void SettingsState::handleEvents(sf::RenderWindow &, const sf::Event &event) {
    if (m_fullscreenButton->handleEvent(event)) {
        m_game->toggleFullscreen();
        m_fullscreenButton->setLabel(fullscreenLabel());
    }
    if (m_backButton->handleEvent(event)) {
        m_game->changeState(std::make_unique<MainMenuState>(m_game));
        return;
    }
    if (const auto* e = event.getIf<sf::Event::KeyPressed>()) {
        if(e->code == sf::Keyboard::Key::Escape) {
            m_game->changeState(std::make_unique<MainMenuState>(m_game));
        }
    }
}

void SettingsState::update() {
    sf::Vector2i mp = sf::Mouse::getPosition(m_game->getWindow());
    m_fullscreenButton->update(mp);
    m_backButton->update(mp);
}

std::string SettingsState::stateName() const {
    return "Settings State";
}

void SettingsState::render(sf::RenderWindow& window) {
    window.clear(Constants::COLOR_BG);
    for (int i=0; i<8; ++i) {
        sf::RectangleShape line({static_cast<float>(Constants::WINDOW_WIDTH), 1.f});
        line.setFillColor(sf::Color(60, 60, 100, 60));
        line.setPosition({0.f, static_cast<float>(i*100)});
        window.draw(line);
    }

    window.draw(m_title);
    m_fullscreenButton->draw(window);
    window.draw(m_volumeLabel);
    window.draw(m_sliderTrack);
    window.draw(m_sliderThumb);
    window.draw(m_debugTip);
    m_backButton->draw(window);
}
