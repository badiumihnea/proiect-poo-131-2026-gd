#ifndef OOP_LEVEL_H
#define OOP_LEVEL_H

#include "Obstacle.h"
#include "OtherObj.h"

class Level {
    std::string m_lvlId;
    std::vector<Obstacle> m_layout={};
    std::vector<OtherObj> m_otherObjs={};
public:
    Level(std::string lvl_id, const std::vector<Obstacle> &layout, const std::vector<OtherObj> &other_objs);

    friend std::ostream& operator<<(std::ostream& os, const Level& lvl);

    void draw(sf::RenderWindow& window) const;

    [[nodiscard]] int objectCount() const;
};
#endif //OOP_LEVEL_H