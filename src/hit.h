// vim: tabstop=4 shiftwidth=4 noexpandtab

#if !defined(__HIT_H__)
#define __HIT_H__

#include "ray.h"
#include "interval.h"

#include <memory>
#include <vector>

class material;

class hit_record
{
public:
    point3 p;
    vec3 normal;
    std::shared_ptr<material> mat;
    bool front_face;
    double t;

    void set_face_normal(const ray& r, const vec3& outward_normal);
};

class hittable
{
public:
    virtual ~hittable() = default;
    virtual bool hit(const ray& r, interval ray_t, hit_record& rec) const = 0;
};

class hittable_list : public hittable
{
public:
    std::vector<std::shared_ptr<hittable>> objects;

    hittable_list();
    hittable_list(std::shared_ptr<hittable> object);

    void clear();
    void add(std::shared_ptr<hittable> object);

    bool hit(const ray& r, interval ray_t, hit_record &rec) const override;
};

#endif // __HIT_H__
