#include "interval.h"

Interval::Interval()
{

}

Interval::Interval(float aMin, float aMax)
{
    min = aMin;
    max = aMax;
}

float Interval::getMin()
{
    return min;
}

float Interval::getMax()
{
    return max;
}

float Interval::getSize()
{
    return max - min;
}


#define MAX(A,B) (A > B ? A : B)
#define MIN(A, B) (A < B ? A : B)

float Interval::calculateIntersection(Interval *other)
{
    float max2 = other->getMax();
    float min2 = other->getMin();

    float unionBounds = MAX(max2, max) - MIN(min2, min);
    float sizeSum = other->getSize() + getSize();
    float intersectionSize = unionBounds - sizeSum;
    return intersectionSize;
}

Interval::~Interval()
{

}

