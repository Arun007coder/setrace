// vim: tabstop=4 shiftwidth=4 noexpandtab

#if !defined(__INTERVAL_H__)
#define __INTERVAL_H__

#include "constants.h"

class interval 
{
public:
    double min;
    double max;
    interval() : min(+infinity), max(-infinity) {}
    interval(double _min, double _max) : min(_min), max(_max) {}

    bool contains(double x) const;
    bool surrounds(double x) const;
    double clamp(double x) const;

    static const interval empty;
    static const interval universe;
};

const static interval empty(+infinity, -infinity);
const static interval universe(-infinity, +infinity);

#endif // __INTERVAL_H__
