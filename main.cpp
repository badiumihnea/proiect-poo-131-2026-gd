// This also works if you do not want `include/`, but some editors might not like it
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <string>
#include <memory>
#include <utility>
#include <vector>
#include <functional>
#include <cmath>
#include <cstdint>
#include <ostream>

#include "../include/Constants.h"
#include "../include/ResourceManager.h"
#include "../include/Icon.h"
#include "../include/PlayerProfile.h"
#include "../include/Button.h"
#include "../include/State.h"
#include "../include/Game.h"
#include "../include/MainMenuState.h"
#include "../include/IconSelectState.h"
#include "../include/SettingsState.h"
#include "../include/PlayState.h"
#include "../include/Obstacle.h"
#include "../include/OtherObj.h"
#include "../include/Level.h"

int main() {
    Game game;
    game.run();
    return 0;
}
