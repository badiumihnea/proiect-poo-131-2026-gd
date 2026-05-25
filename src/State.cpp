#include "State.h"
#include "Game.h"

std::ostream & operator<<(std::ostream &os, const State &s) {
    os<<"[State]\n";
    os<<"Name: "<<s.stateName()<<"\n\n";
    return os;
}

void State::onEnter() {}

void State::onExit() {}
