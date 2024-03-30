// vim: tabstop=4 shiftwidth=4 noexpandtab

#include "renderer.h"
#include "sphere.h"
#include "material.h"

#define __IMAGE_WIDTH 1024

int main(int argc, char** argv)
{
	renderer r(__IMAGE_WIDTH, 16.0/9.0);

	std::shared_ptr<material> mat_ground = std::make_shared<lambertian>(color(0.0, 0.8, 0.0));
	std::shared_ptr<material> mat_centre = std::make_shared<lambertian>(color(0.5, 0.5, 0.5));
	std::shared_ptr<material> mat_left = std::make_shared<metal>(color(0.8, 0.8, 0.8), 0.3);
	std::shared_ptr<material> mat_right = std::make_shared<metal>(color(0.8, 0.6, 0.2), 1.0);

	r.add_object(std::make_shared<sphere>(point3( 0.0, -100.5, -1.0), 100.0, mat_ground));
    r.add_object(std::make_shared<sphere>(point3( 0.0,    0.0, -1.0),   0.5, mat_centre));
    r.add_object(std::make_shared<sphere>(point3(-1.0,    0.0, -1.0),   0.5, mat_left));
    r.add_object(std::make_shared<sphere>(point3( 1.0,    0.0, -1.0),   0.5, mat_right));

	r.render();
	r.save("hello.ppm");

	return 0;
}
