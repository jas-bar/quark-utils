#ifndef COLLIDABLEBOX_H
#define COLLIDABLEBOX_H

#include "collidableobject.h"

class Collidable3DBox : public CollidableObject
{
public:
    Collidable3DBox();
    float getMinX();
    float getMaxX();
    void setMinX(float v);
    void setMaxX(float v);

    float getMinY();
    float getMaxY();
    void setMinY(float v);
    void setMaxY(float v);

    float getMinZ();
    float getMaxZ();
    void setMinZ(float v);
    void setMaxZ(float v);
    ~Collidable3DBox();
};

#endif // COLLIDABLEBOX_H
