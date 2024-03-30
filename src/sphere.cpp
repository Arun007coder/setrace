// vim: tabstop=4 shiftwidth=4 noexpandtab

#include "sphere.h"

bool sphere::hit(const ray &r, interval ray_t, hit_record& rec) const
{
    vec3 oc = r.origin() - centre;
    double a = r.direction().length_squared();
    double h_b = 2.0 * dot(oc, r.direction());
    double c = oc.length_squared() - (radius*radius);

    double d = ((h_b)*(h_b)) - 4*(a*c);
    if(d < 0)
        return false;

    double d_sqrt = sqrt(d);

    double root = (-h_b - d_sqrt) / (2.0*a);
    
    if(!ray_t.surrounds(root))
    {
        root = (-h_b + d_sqrt) / (2.0*a);
        if(!ray_t.surrounds(root))
            return false;
    }

    rec.t = root;
    rec.p = r.at(root);
    vec3 outward_normal = (rec.p - centre) / radius;
    rec.set_face_normal(r, outward_normal);
    rec.mat = mat;
    return true;
}