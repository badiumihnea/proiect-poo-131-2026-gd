#include "Game.h"
#include "State.h"
#include "Constants.h"
#include "MainMenuState.h"
#include "Level.h"

sf::RenderWindow & Game::getWindow() {
    return m_window;
}

ResourceManager & Game::getResources() {
    return m_resources;
}

PlayerProfile & Game::getProfile() {
    return m_profile;
}

bool Game::isFullscreen() const {
    return m_fullscreen;
}

std::string Game::getStateName() const {
    return m_currentState ? m_currentState->stateName() : "None";
}

std::ostream & operator<<(std::ostream &os, const Game &game) {
    os<<"===============\nDEBUG INFO DUMP\n===============\n\n";
    os<<"[Game]\n";
    os<<"Window Mode: "<<(game.m_fullscreen ? "Fullscreen\n\n" : "Windowed\n\n");
    os<<game.m_resources;
    os<<game.m_profile;
    return os;
}

void Game::changeState(std::unique_ptr<State> newState) {
    m_pendingState = std::move(newState);
}

void Game::applyWindowSettings(bool fullscreen) {
    if (fullscreen) {
        m_window.create(sf::VideoMode::getDesktopMode(), "Geometry Dash: OOP Edition", sf::State::Fullscreen);
    }
    else {
        m_window.create(sf::VideoMode({Constants::WINDOW_WIDTH, Constants::WINDOW_HEIGHT}),
            "Geometry Dash: OOP Edition", sf::State::Windowed);
    }
    m_window.setFramerateLimit(Constants::FPS);
}

void Game::toggleFullscreen() {
    m_fullscreen= !m_fullscreen;
    applyWindowSettings(m_fullscreen);
}

Game::Game() {
    applyWindowSettings(false);
    m_resources.loadAll();
    m_currentState = std::make_unique<MainMenuState>(this);
    m_currentState->onEnter();
}

void Game::run() {
    while (m_window.isOpen()) {
        if (m_pendingState) {
            if (m_currentState) {
                m_currentState->onExit();
            }
            m_currentState = std::move(m_pendingState);
            m_pendingState = nullptr;
            m_currentState->onEnter();
        }

        while (const std::optional<sf::Event> event = m_window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                m_window.close();
                continue;
            }
            if (m_currentState) {
                m_currentState->handleEvents(m_window, *event);
            }
            if (const auto* e = event->getIf<sf::Event::KeyPressed>()) {
                if (e->code == sf::Keyboard::Key::F3) {
                    std::cout<<*this<<"\n";
                    if (m_currentState) {
                        std::cout<<*m_currentState;
                    }
                    std::cout<<"Obstacles - Showcase of copy constructor, assign operator, destructor\n";
                    Obstacle obs1("spike", 400.f, 550.f, 0);
                    std::cout<<obs1;
                    Obstacle obs2 = obs1;
                    obs2.setX(500.f);
                    std::cout<<obs2;
                    Obstacle obs3("temp", 0.f, 0.f, 0);
                    obs3=obs1;
                    std::cout<<obs3;
                    OtherObj deco("y_orb", 300.f, 200.f, 1);
                    std::cout<<deco<<"\n";
                    Level testLevel("debug_lvl", { Obstacle("spike", 100.f, 580.f, 0), Obstacle("spike", 200.f, 580.f, 0)}, {OtherObj("y_orb", 150.f, 400.f, 0)});
                    std::cout<<testLevel<<"\n";
                }
            }
        }

        if (m_currentState) {
            m_currentState->update();
        }
        if (m_currentState) {
            m_currentState->render(m_window);
        }
        m_window.display();
    }
}