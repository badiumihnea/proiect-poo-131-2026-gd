#include "OtherObj.h"

OtherObj::OtherObj(std::string obj_id, float x, float y, int layer): m_objId(std::move(obj_id)),
                                                                     m_x(x),
                                                                     m_y(y),
                                                                     m_layer(layer) {
}

std::string OtherObj::getObjId() const {
    return m_objId;
}

void OtherObj::setObjId(const std::string &id) {
    this->m_objId = id;
}

float OtherObj::getX() const {
    return m_x;
}

void OtherObj::setX(float x) {
    this->m_x = x;
}

float OtherObj::getY() const {
    return m_y;
}

void OtherObj::setY(float y) {
    this->m_y = y;
}

int OtherObj::getLayer() const {
    return m_layer;
}

void OtherObj::setLayer(int layer) {
    this->m_layer = layer;
}

std::ostream & operator<<(std::ostream &os, const OtherObj &obj) {
    os<<"[Other Object]\n";
    os<<"ID: "<<obj.m_objId<<"\n";
    os<<"Coordinates: ("<<obj.m_x<<", "<<obj.m_y<<")\n";
    os<<"Layer: #"<<obj.m_layer<<"\n";
    return os;
}
