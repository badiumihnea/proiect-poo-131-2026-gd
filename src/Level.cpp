#include "Level.h"

Level::Level(std::string lvl_id, const std::vector<Obstacle> &layout, const std::vector<OtherObj> &other_objs): m_lvlId(std::move(lvl_id)),
    m_layout(layout),
    m_otherObjs(other_objs) {
}

void Level::draw(sf::RenderWindow &window) const {
    for (const auto& obs:m_layout) {
        obs.draw(window);
    }
}

int Level::objectCount() const {
    return static_cast<int>(m_layout.size() + m_otherObjs.size());
}

std::ostream & operator<<(std::ostream &os, const Level &lvl) {
    os<<"[Level]\n";
    os<<"ID: "<<lvl.m_lvlId<<"\n";
    os<<"Object Count: "<<lvl.objectCount()<<"\n";
    if (lvl.objectCount() >= 1000) {
        os<<"WARNING! Large amount of items. This might cause slower performance on some devices.\n";
    }
    return os;
}
