#include "MainMenuState.h"
#include "Game.h"
#include "PlayState.h"
#include "IconSelectState.h"
#include "SettingsState.h"
#include "Constants.h"

MainMenuState::MainMenuState(Game *game): m_title(game->getResources().getFont()),
                                          m_subtitle(game->getResources().getFont()) {
    m_game = game;
    const sf::Font& font = game->getResources().getFont();
    float cx = Constants::WINDOW_WIDTH / 2.f - Constants::BUTTON_WIDTH / 2.f;
    float startY = 280.f;
    float spacing = 75.f;
    m_buttons.emplace_back(cx, startY + spacing * 0, Constants::BUTTON_WIDTH,
                           Constants::BUTTON_HEIGHT, "PLAY!", font);
    m_buttons.emplace_back(cx, startY + spacing * 1, Constants::BUTTON_WIDTH,
                           Constants::BUTTON_HEIGHT, "ICON MENU", font);
    m_buttons.emplace_back(cx, startY + spacing * 2, Constants::BUTTON_WIDTH,
                           Constants::BUTTON_HEIGHT, "SETTINGS", font);
    m_buttons.emplace_back(cx, startY + spacing * 3, Constants::BUTTON_WIDTH,
                           Constants::BUTTON_HEIGHT, "EXIT :(", font);

    m_title.setString("GEOMETRY DASH");
    m_title.setCharacterSize(50u);
    m_title.setFillColor(Constants::COLOR_ACC);
    m_title.setStyle(sf::Text::Style::Bold);
    {
        sf::FloatRect tb = m_title.getLocalBounds();
        m_title.setOrigin({tb.size.x / 2.f, tb.size.y / 2.f});
    }
    m_title.setPosition({Constants::WINDOW_WIDTH / 2.f, 160.f});
    m_subtitle.setString("Unibuc OOP Edition :)");
    m_subtitle.setCharacterSize(20u);
    m_subtitle.setFillColor(Constants::COLOR_ACC2);
    {
        sf::FloatRect sb = m_subtitle.getLocalBounds();
        m_subtitle.setOrigin({sb.size.x / 2.f, sb.size.y / 2.f});
    }
    m_subtitle.setPosition({Constants::WINDOW_WIDTH / 2.f, 230.f});
}

std::string MainMenuState::stateName() const {
    return "Main Menu State";
}

void MainMenuState::handleEvents(sf::RenderWindow& window, const sf::Event& event) {
    if (m_buttons[0].handleEvent(event)) {
        m_game->changeState(std::make_unique<PlayState>(m_game));
    }
    if (m_buttons[1].handleEvent(event)) {
        m_game->changeState(std::make_unique<IconSelectState>(m_game));
    }
    if (m_buttons[2].handleEvent(event)) {
        m_game->changeState(std::make_unique<SettingsState>(m_game));
    }
    if (m_buttons[3].handleEvent(event)) {
        window.close();
    }
}

void MainMenuState::update() {
    sf::Vector2i mp = sf::Mouse::getPosition(m_game->getWindow());
    for (auto& button : m_buttons) {
        button.update(mp);
    }
}

void MainMenuState::render(sf::RenderWindow& window) {
    window.clear(Constants::COLOR_BG);
    sf::RectangleShape band({static_cast<float>(Constants::WINDOW_WIDTH), 120.f});
    band.setFillColor(sf::Color(0, 0, 0, 80));
    band.setPosition({0.f, 100.f});
    window.draw(band);
    window.draw(m_title);
    window.draw(m_subtitle);
    for (auto& button : m_buttons) {
        button.draw(window);
    }
}
