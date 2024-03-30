// vim: tabstop=4 shiftwidth=4 noexpandtab
#if !defined(__CONSTANTS_H__)
#define __CONSTANTS_H__

#include <cmath>
#include <cstdlib>
#include <limits>
#include <memory>

const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

// 180* = pi
inline double deg_to_rad(double deg)
{
    return deg*(pi/180.0);
}

inline double random_double()
{
    return rand() / (RAND_MAX+1.0);
}

inline double random_double(double min, double max)
{
    return min + (max-min)*random_double();
}

#endif // __CONSTANTS_H__