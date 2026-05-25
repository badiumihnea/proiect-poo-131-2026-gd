#include "PlayState.h"
#include "Game.h"
#include "Icon.h"
#include "Constants.h"

void PlayState::tryJump() {
    if (m_onGround) {
        m_velocityY = Constants::JUMP_VELOCITY;
        m_onGround = false;
        m_jumpHintAlpha = 255;
    }
}

void PlayState::drawPlayerWithRotation(sf::RenderWindow &window) {
    const Icon& icon = m_game->getProfile().getIcon();
    float size = Constants::PLAYER_SIZE;
    sf::RectangleShape body({size, size});
    body.setFillColor(icon.getCol1());
    body.setOutlineColor(icon.getCol2());
    body.setOutlineThickness(2.f);
    body.setOrigin({size/2.f, size/2.f});
    body.setPosition({m_playerX, m_playerY});
    body.setRotation(sf::degrees(m_rotation));
    window.draw(body);
    sf::Transform innerT;
    innerT.translate({m_playerX, m_playerY});
    innerT.rotate(sf::degrees(m_rotation));

    switch (icon.getIconId() % 5) {
        case 0: {
            sf::ConvexShape diamond;
            diamond.setPointCount(4);
            float d = size * 0.25f;
            diamond.setPoint(0, {0.f, -d});
            diamond.setPoint(1, {d, 0.f});
            diamond.setPoint(2, {0.f, d});
            diamond.setPoint(3, {-d, 0.f});
            diamond.setFillColor(icon.getCol2());
            window.draw(diamond, innerT);
            break;
        }
        case 1: {
            float t = size*0.12f;
            sf::RectangleShape horizontal(sf::Vector2f(size * 0.7f, t));
            horizontal.setFillColor(icon.getCol2());;
            horizontal.setOrigin({size * 0.35f, t/2.f});
            window.draw(horizontal, innerT);
            sf::RectangleShape vertical(sf::Vector2f(t, size * 0.7f));
            vertical.setFillColor(icon.getCol2());
            vertical.setOrigin({t/2.f, size*0.35f});
            window.draw(vertical, innerT);
            break;
        }
        case 2: {
            sf::CircleShape circle(size * 0.22f);
            circle.setFillColor(icon.getCol2());
            circle.setOrigin({size * 0.22f, size * 0.22f});
            window.draw(circle, innerT);
            break;
        }
        case 3: {
            for (int rot:{0, 45}) {
                sf::RectangleShape square(sf::Vector2f(size * 0.4f, size* 0.4f));
                square.setFillColor(icon.getCol2());
                square.setOrigin({size * 0.2f, size * 0.2f});
                sf::Transform rt=innerT;
                rt.rotate(sf::degrees(static_cast<float>(rot)));
                window.draw(square, rt);
            }
            break;
        }
        case 4: {
            sf::ConvexShape arrow;
            arrow.setPointCount(3);
            float aw = size * 0.35f, ah = size *0.35f;
            arrow.setPoint(0, {-aw, ah/2.f});
            arrow.setPoint(1, {aw, 0.f});
            arrow.setPoint(2, {-aw, -ah/2.f});
            arrow.setFillColor(icon.getCol2());
            window.draw(arrow, innerT);
            break;
        }
    }
}

PlayState::PlayState(Game *game): m_jumpHint(game->getResources().getFont()) {
    m_game = game;
    m_playerX = Constants::WINDOW_WIDTH/2.f;
    m_playerY=Constants::GROUND_Y;
    m_velocityY = 0.f;
    m_onGround=true;
    m_rotation = 0.f;
    m_ground.setSize({static_cast<float>(Constants::WINDOW_WIDTH), 100.f});
    m_ground.setFillColor(Constants::COLOR_ACC2);
    m_ground.setPosition({0.f, Constants::GROUND_Y});
}

void PlayState::handleEvents(sf::RenderWindow &, const sf::Event &event) {
    if (const auto* e = event.getIf<sf::Event::MouseButtonPressed>()) {
        if (e->button == sf::Mouse::Button::Left) {
            tryJump();
        }
    }
    if (const auto* e = event.getIf<sf::Event::KeyPressed>()) {
        if (e->code == sf::Keyboard::Key::Up) {
            tryJump();
        }
        if (e->code == sf::Keyboard::Key::Escape) {
            m_returnPending = true;
        }
    }
}

void PlayState::update() {
    if (m_returnPending) {
        m_game->changeState(std::make_unique<MainMenuState>(m_game));
        return;
    }

    m_velocityY += Constants::GRAVITY;
    m_playerY += m_velocityY;
    if (m_playerY >= Constants::GROUND_Y) {
        m_playerY = Constants::GROUND_Y;
        m_velocityY = 0.f;
        m_onGround = true;
    }
    else {
        m_onGround = false;
    }

    if (!m_onGround) {
        m_rotation += 5.f;
    }
}

void PlayState::render(sf::RenderWindow &window) {
    window.clear(Constants::COLOR_BG);
    window.draw(m_ground);
    drawPlayerWithRotation(window);
}

std::string PlayState::stateName() const {
    return "Play State";
}
