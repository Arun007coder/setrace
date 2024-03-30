// vim: tabstop=4 shiftwidth=4 noexpandtab

#ifndef __RENDERER_H__
#define __RENDERER_H__

#include "vec3.h"
#include "frame.h"
#include "ray.h"
#include "hit.h"
#include <string>

class renderer {
private:
	double aspect_ratio;
	framebuffer* fb;
	double focal_length;
	
	double viewport_width;
	double viewport_height;

	point3 camera_center;

	vec3 viewport_u;
	vec3 viewport_v;

	vec3 pixel_delta_u;
	vec3 pixel_delta_v;

	vec3 viewport_upper_left;

	vec3 pixel00_loc;

	int sample_size = 10;
	int max_depth = 10;

	hittable_list world;

	ray get_ray(int x, int y) const;
	vec3 pixel_sample_square() const;
public:
	renderer(int width, double aspect_ratio);
	~renderer();

	void render();
	void add_object(std::shared_ptr<hittable> object);
	void clear();
	void save(std::string name);
};

#endif // !__RENDERER_H__
