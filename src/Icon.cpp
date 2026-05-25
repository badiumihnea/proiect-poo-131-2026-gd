#include "Icon.h"

Icon::Icon(int id, sf::Color col1, sf::Color col2, bool glow, sf::Color glow_col) :
m_icon_id(id), m_col1(col1), m_col2(col2), m_glow(glow), m_glow_col(glow_col) {}

int Icon::getIconId() const {
    return m_icon_id;
}

sf::Color Icon::getCol1() const {
    return m_col1;
}

sf::Color Icon::getCol2() const {
    return m_col2;
}

bool Icon::isGlow() const {
    return m_glow;
}

sf::Color Icon::getGlowCol() const {
    return m_glow_col;
}

void Icon::set_m_icon_id(int icon_id) {
    this->m_icon_id = icon_id;
}

void Icon::set_m_col1(const sf::Color &col1) {
    this->m_col1 = col1;
}

void Icon::set_m_col2(const sf::Color &col2) {
    this->m_col2 = col2;
}

void Icon::set_m_glow(bool glow) {
    this->m_glow = glow;
}

void Icon::set_m_glow_col(const sf::Color &glow_col) {
    this->m_glow_col = glow_col;
}

void Icon::draw(sf::RenderWindow &window, float cx, float cy, float size) const {
    float half=size/2.f;
    sf::RectangleShape body(sf::Vector2f(size, size));
    body.setFillColor(m_col1);
    body.setOutlineColor(m_col1);
    body.setOutlineThickness(2.f);
    body.setOrigin({half, half});
    body.setPosition({cx, cy});
    window.draw(body);

    switch (m_icon_id % 5) {
        case 0: {
            sf::ConvexShape diamond;
            diamond.setPointCount(4);
            float d = size * 0.25f;
            diamond.setPoint(0, {0.f, -d});
            diamond.setPoint(1, {d, 0.f});
            diamond.setPoint(2, {0.f, d});
            diamond.setPoint(3, {-d, 0.f});
            diamond.setFillColor(m_col2);
            diamond.setPosition({cx, cy});
            window.draw(diamond);
            break;
        }
        case 1: {
            float t = size*0.12f;
            sf::RectangleShape horizontal(sf::Vector2f(size * 0.7f, t));
            horizontal.setFillColor(m_col2);;
            horizontal.setOrigin({size * 0.35f, t/2.f});
            horizontal.setPosition({cx, cy});
            window.draw(horizontal);
            sf::RectangleShape vertical(sf::Vector2f(t, size * 0.7f));
            vertical.setFillColor(m_col2);
            vertical.setOrigin({t/2.f, size*0.35f});
            vertical.setPosition({cx, cy});
            window.draw(vertical);
            break;
        }
        case 2: {
            sf::CircleShape circle(size * 0.22f);
            circle.setFillColor(m_col2);
            circle.setOrigin({size * 0.22f, size * 0.22f});
            circle.setPosition({cx, cy});
            window.draw(circle);
            break;
        }
        case 3: {
            for (int rot:{0, 45}) {
                sf::RectangleShape square(sf::Vector2f(size * 0.4f, size* 0.4f));
                square.setFillColor((m_col2));
                square.setOrigin({size * 0.2f, size * 0.2f});
                square.setPosition({cx, cy});
                square.setRotation(sf::degrees(static_cast<float>(rot)));
                window.draw(square);
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
            arrow.setFillColor(m_col2);
            arrow.setPosition({cx, cy});
            window.draw(arrow);
            break;
        }
    }
}

std::ostream & operator<<(std::ostream &os, const Icon icon) {
    auto colorToStr = [](sf::Color c) -> std::string {
        return std::to_string(c.r) + "," + std::to_string(c.g) + "," + std::to_string(c.b);
    };
    os<<"[Icon]\n";
    os<<"Icon ID: "<< icon.m_icon_id <<"\n";
    os<<"Main Color: "<<colorToStr(icon.m_col1)<<"\n";
    os<<"Accent Color: "<<colorToStr(icon.m_col2)<<"\n";
    os<<"Glow: "<<(icon.m_glow ? "ON" : "OFF")<<"\n";
    os<<"Glow Color: "<<(icon.m_glow ? colorToStr(icon.m_glow_col) : "None")<<"\n";
    return os;
}
