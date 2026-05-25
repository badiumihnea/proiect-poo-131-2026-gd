#ifndef OOP_OTHEROBJ_H
#define OOP_OTHEROBJ_H

#include <iostream>

class OtherObj {
    std::string m_objId;
    float m_x;
    float m_y;
    int m_layer;

public:
    OtherObj(std::string obj_id, float x, float y, int layer);

    [[nodiscard]] std::string getObjId() const;

    void setObjId(const std::string &id);

    [[nodiscard]] float getX() const;

    void setX(float x);

    [[nodiscard]] float getY() const;

    void setY(float y);

    [[nodiscard]] int getLayer() const;

    void setLayer(int layer);

    friend std::ostream& operator<<(std::ostream& os, const OtherObj& obj);
};
#endif //OOP_OTHEROBJ_H