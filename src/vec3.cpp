// vim: tabstop=4 shiftwidth=4 noexpandtab

#include "vec3.h"
#include "interval.h"

#define __GAMMA_CORRECTION 1

uint32_t vec3ToColor(color v, int samples_per_pixel)
{
	double r = v.x();
	double g = v.y();
	double b = v.z();

	double scale = 1.0/samples_per_pixel;
	r *= scale;
	g *= scale;
	b *= scale;

#if __GAMMA_CORRECTION
	r = linear_to_gamma(r);
	g = linear_to_gamma(g);
	b = linear_to_gamma(b);
#endif

	static const interval intensity(0.000, 0.999);

	int ir = static_cast<int>(256 * intensity.clamp(r));
	int ig = static_cast<int>(256 * intensity.clamp(g));
	int ib = static_cast<int>(256 * intensity.clamp(b));
	
	uint32_t color = (((ir & 0xFF) << 16) & 0x00FF0000) | (((ig & 0xFF) << 8) & 0x0000FF00) | ((ib & 0xFF) & 0x000000FF);

	return color;
}

vec3 reflect(const vec3& v, const vec3& n)
{
    return v - 2*dot(v,n)*n;
}