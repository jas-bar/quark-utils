#include "collidablebox.h"

#define ORDER_X 0
#define ORDER_Y 1
#define ORDER_Z 2

Collidable3DBox::Collidable3DBox()
{
    for(int i = 0; i < 3; ++i){
        intervals.push_back(Interval());
    }
}

float Collidable3DBox::getMinX()
{
    return intervals[ORDER_X].getMin();
}

float Collidable3DBox::getMaxX()
{
    return intervals[ORDER_X].getMax();
}

void Collidable3DBox::setMinX(float v)
{
    intervals[ORDER_X].setMin(v);
}

void Collidable3DBox::setMaxX(float v)
{
    intervals[ORDER_X].setMax(v);
}

float Collidable3DBox::getMinY()
{
    return intervals[ORDER_Y].getMin();
}

float Collidable3DBox::getMaxY()
{
    return intervals[ORDER_Y].getMax();
}

void Collidable3DBox::setMinY(float v)
{
    intervals[ORDER_Y].setMin(v);
}

void Collidable3DBox::setMaxY(float v)
{
    intervals[ORDER_Y].setMax(v);
}

float Collidable3DBox::getMinZ()
{
    return intervals[ORDER_Z].getMin();
}

float Collidable3DBox::getMaxZ()
{
    return intervals[ORDER_Z].getMax();
}

void Collidable3DBox::setMinZ(float v)
{
    intervals[ORDER_Z].setMin(v);
}

void Collidable3DBox::setMaxZ(float v)
{
    intervals[ORDER_Z].setMax(v);
}

Collidable3DBox::~Collidable3DBox()
{

}

