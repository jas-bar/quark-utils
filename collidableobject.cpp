#include "collidableobject.h"

CollidableObject::CollidableObject()
{

}

std::vector<float> CollidableObject::getProjectionVector(CollidableObject *other)
{
    std::vector<float> projectionVector;
    for(int i = 0; i < intervals.size(); i++){
        Interval i1 = getInterval(i);
        Interval i2 = other->getInterval(i);
        projectionVector.push_back(i1.calculateIntersection(&i2));
    }
    return projectionVector;
}

Interval CollidableObject::getInterval(int axis)
{
    intervals.at(axis);
}

CollidableObject::~CollidableObject()
{

}

