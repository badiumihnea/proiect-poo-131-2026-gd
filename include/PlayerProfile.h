#ifndef OOP_PLAYERPROFILE_H
#define OOP_PLAYERPROFILE_H

#include <string>
#include <SFML/Graphics.hpp>
#include "Icon.h"

class PlayerProfile {
    std::string m_username;
    Icon m_icon;
public:
    PlayerProfile();

    explicit PlayerProfile(Icon icon);

    [[nodiscard]] const Icon& getIcon() const;

    void setIcon (const Icon& icon);

    [[nodiscard]] std::string getUsername() const;

    void setUsername(const std::string& username);

    friend std::ostream& operator<<(std::ostream& os, const PlayerProfile& profile);
};
#endif //OOP_PLAYERPROFILE_H