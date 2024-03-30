// vim: tabstop=4 shiftwidth=4 noexpandtab

#ifndef __FRAMEBUFFER_H__
#define __FRAMEBUFFER_H__

#include <cstdint>
#include <string>

class framebuffer {
private:
	uint32_t* buffer;
	uint32_t size;
	int width;
	int height;
	double aspect_ratio;
public:
	framebuffer(int width, int height);
	~framebuffer();

	void putpixel(int x, int y, uint32_t color);
	void putpixel(int x, int y, int r, int g, int b);

	void clear();
	void save(std::string file);

	int w();
	int h();
	uint32_t sz();

	uint32_t &operator()(int x, int y);
};

#endif // !__FRAMEBUFFER_H__
