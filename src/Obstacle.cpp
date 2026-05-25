#include "Obstacle.h"

Obstacle::Obstacle(std::string id, float x, float y, int layer): m_obsId(id), m_x(x), m_y(y), m_layer(layer) {}

std::string Obstacle::getObsId() const {
    return m_obsId;
}

float Obstacle::getX() const {
    return m_x;
}

void Obstacle::setX(float x) {
    this->m_x = x;
}

float Obstacle::getY() const {
    return m_y;
}

void Obstacle::setY(float y) {
    this->m_y = y;
}

int Obstacle::getLayer() const {
    return m_layer;
}

void Obstacle::setLayer(int layer) {
    this->m_layer = layer;
}

void Obstacle::draw(sf::RenderWindow &window) const {
    sf::ConvexShape spike;
    spike.setPointCount(3);
    spike.setPoint(0, {0.f, -30.f});
    spike.setPoint(1, {20.f, 10.f});
    spike.setPoint(2, {-20.f, 10.f});
    spike.setFillColor(sf::Color(220, 50, 50));
    spike.setPosition({m_x, m_y});
    window.draw(spike);
}

Obstacle::Obstacle(const Obstacle &other): m_obsId(other.m_obsId), m_x(other.m_x), m_y(other.m_y), m_layer(other.m_layer) {
    std::cout<<"[Obstacle]: "<<m_obsId<<" copied using copy constructor\n";
}

Obstacle & Obstacle::operator=(const Obstacle &other) {
    if (this == &other) {
        return *this;
    }
    m_obsId = other.m_obsId;
    m_x = other.m_x;
    m_y = other.m_y;
    m_layer = other.m_layer;
    std::cout<<"[Obstacle]: "<<m_obsId<<" assigned using operator=\n";
    return *this;
}

Obstacle::~Obstacle() {
    std::cout<<"[Obsstacle]:"<<m_obsId<<" Destroyed\n";
}

std::ostream & operator<<(std::ostream &os, const Obstacle &obs) {
    os<<"[Obstacle]\n";
    os<<"ID: "<<obs.m_obsId<<"\n";
    os<<"Coordinates: ("<<obs.m_x<<", "<<obs.m_y<<")\n";
    os<<"Layer: #"<<obs.m_layer<<"\n\n";
    return os;
}
