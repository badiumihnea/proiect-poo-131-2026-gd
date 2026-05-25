#ifndef OOP_STATE_H
#define OOP_STATE_H

#include <string>
#include <SFML/Graphics.hpp>

class Game;
class State {
public:
    virtual ~State() = default;

    virtual void onEnter();

    virtual void onExit();

    [[nodiscard]] virtual std::string stateName() const = 0;

    virtual void handleEvents(sf::RenderWindow& window, const sf::Event& event) = 0;
    virtual void update() = 0;
    virtual void render(sf::RenderWindow& window) = 0;

    friend std::ostream& operator<<(std::ostream& os, const State& s);

protected:
    Game* m_game = nullptr;
};
#endif //OOP_STATE_H