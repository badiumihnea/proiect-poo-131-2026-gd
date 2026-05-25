#ifndef OOP_OBSTACLE_H
#define OOP_OBSTACLE_H

#include <iostream>
#include <SFML/Graphics.hpp>

class Obstacle {
    std::string m_obsId;
    float m_x;
    float m_y;
    int m_layer;
public:
    Obstacle(std::string id, float x, float y, int layer=0);

    [[nodiscard]] std::string getObsId() const;

    [[nodiscard]] float getX() const;

    void setX(float x);

    [[nodiscard]] float getY() const;

    void setY(float y);

    [[nodiscard]] int getLayer() const;

    void setLayer(int layer);

    void draw(sf::RenderWindow& window) const;

    Obstacle(const Obstacle& other);

    Obstacle& operator=(const Obstacle& other);

    ~Obstacle();

    friend std::ostream& operator<<(std::ostream& os, const Obstacle& obs);
};
#endif //OOP_OBSTACLE_H