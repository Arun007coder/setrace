// vim: tabstop=4 shiftwidth=4 noexpandtab

#if !defined(__SPHERE_H__)
#define __SPHERE_H__

#include "hit.h"

class sphere : public hittable
{
private:
    point3 centre;
    double radius;
    std::shared_ptr<material> mat;
public:
    sphere(point3 _centre, double _radius, std::shared_ptr<material> _mat) : centre(_centre), radius(_radius), mat(_mat)
    {
    }

    bool hit(const ray &r, interval ray_t, hit_record& rec) const override;
};


#endif // __SPHERE_H__
