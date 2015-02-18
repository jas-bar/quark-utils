#ifndef COLLIDABLEOBJECT_H
#define COLLIDABLEOBJECT_H

#include "interval.h"
#include <vector>

class CollidableObject
{
private:
    std::vector<Interval> intervals;
public:
    CollidableObject();
    std::vector<float> getProjectionVector(CollidableObject* other);
    Interval getInterval(int axis);
    ~CollidableObject();
};

#endif // COLLIDABLEOBJECT_H
