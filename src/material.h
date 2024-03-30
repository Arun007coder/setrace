// vim: tabstop=4 shiftwidth=4 noexpandtab

#if !defined(__MATERIAL_H__)
#define __MATERIAL_H__

#include "hit.h"

class hit_record;

class material
{
public:
    virtual ~material() = default;
    virtual bool scatter(const ray& r_in, const hit_record& rec, color &attenuation, ray& scattered) const = 0;
};

class lambertian : public material
{
private:
    color albedo;
public:
    lambertian(color a) : albedo(a) {}
    bool scatter(const ray& r_in, const hit_record& rec, color &attenuation, ray& scattered) const override;
};

class metal : public material
{
private:
    color albedo;
	double fuzz;
public:
    metal(const color a, double f) : albedo(a), fuzz(f < 1 ? f : 1) {}
    bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const override;
};

#endif // __MATERIAL_H__
