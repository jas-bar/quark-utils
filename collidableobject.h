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
    std::vector<float> getProjectionVector();
    ~CollidableObject();
};

#endif // COLLIDABLEOBJECT_H
