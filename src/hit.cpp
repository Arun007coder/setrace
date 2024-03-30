// vim: tabstop=4 shiftwidth=4 noexpandtab

#include "hit.h"

void hit_record::set_face_normal(const ray& r, const vec3& outward_normal)
{
    front_face = (dot(r.direction(), outward_normal) < 0);
    normal = front_face ? outward_normal : (-outward_normal);
}

hittable_list::hittable_list()
{

}

hittable_list::hittable_list(std::shared_ptr<hittable> object)
{
    objects.push_back(object);
}


void hittable_list::clear()
{
    objects.clear();
}

void hittable_list::add(std::shared_ptr<hittable> object)
{
    objects.push_back(object);
}

bool hittable_list::hit(const ray& r, interval ray_t, hit_record &rec) const 
{
    hit_record temp_rec;
    bool hit_anything = false;
    double closest_so_far = ray_t.max;

    for (const std::shared_ptr<hittable>& object : objects)
    {
        if(object->hit(r, interval(ray_t.min, closest_so_far), temp_rec))
        {
            hit_anything = true;
            closest_so_far = temp_rec.t;
            rec = temp_rec;
        }
    }

    return hit_anything;
}