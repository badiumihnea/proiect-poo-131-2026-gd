#ifndef OOP_RESOURCEMANAGER_H
#define OOP_RESOURCEMANAGER_H
#include <iostream>
#include <SFML/Graphics.hpp>

class ResourceManager {
    sf::Font m_mainFont;
public:
    bool loadAll();
    const sf::Font& getFont() const;

    friend std::ostream& operator<<(std::ostream& os, const ResourceManager& rm);
};
#endif //OOP_RESOURCEMANAGER_H