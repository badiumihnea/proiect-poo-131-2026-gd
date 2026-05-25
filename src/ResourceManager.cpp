#include "ResourceManager.h"

bool ResourceManager::loadAll() {
    std::string fontPath = "assets/PUSABFONT.otf";
    if (m_mainFont.openFromFile(fontPath)) {
        std::cout<<"[Resource Manager] Font loaded\n";
        return true;
    }
    std::cout<<"[Resource Manager] WARNING: Font not loaded\n";
    return false;
}

const sf::Font& ResourceManager::getFont() const {
    return m_mainFont;
}

std::ostream& operator<<(std::ostream& os, const ResourceManager& rm)  {
    os<<"[ResourceManager]\n";
    os<<"Font: "<<rm.m_mainFont.getInfo().family<<"\n\n";
    return os;
}