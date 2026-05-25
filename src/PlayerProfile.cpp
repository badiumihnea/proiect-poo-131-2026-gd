#include "PlayerProfile.h"

PlayerProfile::PlayerProfile(): m_username("GUEST") ,m_icon (0, sf::Color(80, 200, 120),
                                                             sf::Color(0, 120, 255), false, sf::Color(255, 255, 255)) {}

PlayerProfile::PlayerProfile(Icon icon):m_username("GUEST"), m_icon(icon) {}

const Icon & PlayerProfile::getIcon() const {
    return m_icon;
}

void PlayerProfile::setIcon(const Icon &icon) {
    m_icon = icon;
}

std::string PlayerProfile::getUsername() const {
    return m_username;
}

void PlayerProfile::setUsername(const std::string &username) {
    this->m_username = username;
}

std::ostream & operator<<(std::ostream &os, const PlayerProfile &profile) {
    os<<"[PlayerProfile]\n";
    os<<"Username: "<<profile.m_username<<"\n";
    os<<profile.m_icon;
    return os;
}
