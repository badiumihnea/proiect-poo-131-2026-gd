#include "Button.h"
#include "Constants.h"

Button::Button(float x, float y, float w, float h, const std::string &label, const sf::Font &font):
    m_text(font), m_label(label) {
    m_shape.setSize({w, h});
    m_shape.setPosition({x, y});
    m_shape.setFillColor(Constants::COLOR_BTN_IDLE);
    m_shape.setOutlineThickness(2.f);
    m_shape.setOutlineColor(Constants::COLOR_ACC3);
    m_text.setString(label);
    m_text.setCharacterSize(22u);
    m_text.setFillColor(Constants::COLOR_TEXT);
    centerText(x, y, w, h);
}

void Button::update(sf::Vector2i mousePos) {
    m_hovered = m_shape.getGlobalBounds().contains(sf::Vector2f(static_cast<float>(mousePos.x),
                                                                static_cast<float>(mousePos.y)));
    m_shape.setFillColor(m_hovered ? Constants::COLOR_BTN_HOVER : Constants::COLOR_BTN_IDLE);
    m_shape.setOutlineColor(m_hovered ? Constants::COLOR_ACC : Constants::COLOR_ACC3);
}

bool Button::handleEvent(const sf::Event &event) {
    if (const auto* e = event.getIf<sf::Event::MouseButtonReleased>()) {
        if (e->button == sf::Mouse::Button::Left && m_hovered) {
            return true;
        }
    }
    return false;
}

void Button::draw(sf::RenderWindow &window) const {
    window.draw(m_shape);
    window.draw(m_text);
}

void Button::setLabel(const std::string &label) {
    m_label = label;
    m_text.setString(label);
    auto pos = m_shape.getPosition();
    auto size = m_shape.getSize();
    centerText(pos.x, pos.y, size.x, size.y);
}

bool Button::isHovered() const {
    return m_hovered;
}

std::ostream & operator<<(std::ostream &os, const Button &btn) {
    auto pos = btn.m_shape.getPosition();
    auto size = btn.m_shape.getSize();
    os<<"[Button]\n";
    os<<"Label: "<<btn.m_label<<"\n";
    os<<"Position: "<<pos.x<<", "<<pos.y<<"\n";
    os<<"Size: "<<size.x<<", "<<size.y<<"\n\n";
    return os;
}
