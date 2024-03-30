// vim: tabstop=4 shiftwidth=4 noexpandtab
#include "renderer.h"
#include "constants.h"
#include "material.h"

// w/h = a > w = a*h
renderer::renderer(int width, double aspect_ratio)
{
	int ih = static_cast<int>(width/aspect_ratio);
	ih = (ih < 1) ? 1 : ih;
	fb = new framebuffer(width, ih);
	this->aspect_ratio = aspect_ratio;

	focal_length = 1.0;
	sample_size = 100;
	viewport_height = 2.0;

	viewport_width = viewport_height * (aspect_ratio);

	std::cout << "Image Width: " << width << "px\nImage Height: " << ih << "px\nAspect ratio: " << aspect_ratio << "\nViewport width: " << viewport_width << "px\nViewport height: " << viewport_height << "px\n";

	camera_center = point3(0, 0, 0);

	viewport_u = vec3(viewport_width, 0, 0);
	viewport_v = vec3(0, -viewport_height, 0);

	pixel_delta_u = viewport_u / fb->w();
	pixel_delta_v = viewport_v / fb->h();

	viewport_upper_left = camera_center - vec3(0, 0, focal_length) - (viewport_u/2) - (viewport_v/2);

	pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);
}

renderer::~renderer()
{
	delete fb;
}

color ray_color(const ray& r, int depth, const hittable& world)
{
	if(depth <= 0)
	{
		return color(0, 0, 0);
	}

	hit_record rec;
	if(world.hit(r, interval(0, infinity), rec))
	{
		ray scattered;
		color attenuation;
		if(rec.mat->scatter(r, rec, attenuation, scattered))
			return attenuation * ray_color(scattered, depth-1, world);
		return color(0, 0, 0);
	}

	vec3 unit_direction = unit_vector(r.direction());
	auto a = 0.5*(unit_direction.y() + 1.0);

	return (1.0-a)*color(1.0, 1.0, 1.0) + a*color(0.5, 0.7, 1.0);
}

ray renderer::get_ray(int x, int y) const
{
	auto pixel_center = pixel00_loc + (x*pixel_delta_u) + (y*pixel_delta_v);
	auto pixel_sample = pixel_center + pixel_sample_square();

	auto ray_direction = pixel_sample - camera_center;

	return ray(camera_center, ray_direction);
}

vec3 renderer::pixel_sample_square() const
{
	double px = -0.5 + random_double();
	double py = -0.5 + random_double();

	return (px * pixel_delta_u) + (py * pixel_delta_v);
}

void renderer::render()
{
	for(int y = 0; y < fb->h(); ++y)
	{
        // std::clog << "\rScanlines remaining: " << (fb->h() - y) << ' ' << std::flush;
		for(int x = 0; x < fb->w(); ++x)
		{
			color c = color(0, 0, 0);
			for(int sample = 0; sample < sample_size; ++sample)
			{
				ray r = get_ray(x, y);
				c += ray_color(r, max_depth, world);
			}

			fb->putpixel(x, y, vec3ToColor(c, sample_size));
		}
	}
	std::clog << '\n';
}

void renderer::save(std::string name)
{
	fb->save(name);
}

void renderer::add_object(std::shared_ptr<hittable> object)
{
	world.add(object);
}

void renderer::clear()
{
	world.clear();
}
