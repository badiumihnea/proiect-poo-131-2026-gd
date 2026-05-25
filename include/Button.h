#ifndef OOP_BUTTON_H
#define OOP_BUTTON_H

#include <SFML/Graphics.hpp>

class Button {
    sf::RectangleShape m_shape;
    sf::Text m_text;
    std::string m_label;
    bool m_hovered = false;
    void centerText(float x, float y, float w, float h) {
        sf::FloatRect tb = m_text.getLocalBounds();
        m_text.setOrigin({tb.size.x/2.f , tb.size.y/2.f});
        m_text.setPosition({x + w/2.f, y + h/2.f});
    }
public:
    Button(float x, float y, float w, float h, const std::string& label, const sf::Font& font);

    void update(sf::Vector2i mousePos);

    bool handleEvent(const sf::Event& event);

    void draw(sf::RenderWindow& window) const;

    void setLabel(const std::string& label);

    bool isHovered() const;

    friend std::ostream& operator<<(std::ostream& os, const Button& btn);
};
#endif //OOP_BUTTON_H