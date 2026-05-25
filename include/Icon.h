#ifndef OOP_ICON_H
#define OOP_ICON_H

#include <SFML/Graphics.hpp>

class Icon {
    int m_icon_id;
    sf::Color m_col1;
    sf::Color m_col2;
    bool m_glow;
    sf::Color m_glow_col;
public:
    explicit Icon(int id=0, sf::Color col1 = sf::Color(80, 200, 120),
        sf::Color col2=sf::Color(0, 120, 255), bool glow=false,
        sf::Color glow_col= sf::Color(255, 255, 255));

    [[nodiscard]] int getIconId() const;

    [[nodiscard]] sf::Color getCol1() const;

    [[nodiscard]] sf::Color getCol2() const;

    [[nodiscard]] bool isGlow() const;

    [[nodiscard]] sf::Color getGlowCol() const;

    void set_m_icon_id(int icon_id);

    void set_m_col1(const sf::Color &col1);

    void set_m_col2(const sf::Color &col2);

    void set_m_glow(bool glow);

    void set_m_glow_col(const sf::Color &glow_col);

    void draw(sf::RenderWindow& window, float cx, float cy, float size) const;

    friend std::ostream& operator<<(std::ostream& os, const Icon icon);
};
#endif //OOP_ICON_H