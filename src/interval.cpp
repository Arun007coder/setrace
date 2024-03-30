// vim: tabstop=4 shiftwidth=4 noexpandtab

#include "interval.h"

bool interval::contains(double x) const
{
    return (x >= min) && (x <= max);
}

bool interval::surrounds(double x) const
{
    return (x > min) && (x < max);
}

double interval::clamp(double x) const
{
    if(x < min)
        return min;
    if(x > max)
        return max;

    return x;
}