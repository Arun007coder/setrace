// vim: tabstop=4 noexpandtab shiftwidth=4

#include "frame.h"
#include <cstdint>
#include <cstring>
#include <fstream>
#include <ostream>
#include <iostream>

framebuffer::framebuffer(int width, int height)
{
	this->width = width;
	this->height = height;

	this->size = (this->height*this->width)*sizeof(uint32_t);

	this->buffer = new uint32_t[this->size];
}

framebuffer::~framebuffer()
{
	delete this->buffer;
}

void framebuffer::putpixel(int x, int y, uint32_t color)
{
	if((x < width) && (y < height))
		buffer[x+(y*width)] = color;
}

void framebuffer::putpixel(int x, int y, int r, int g, int b)
{
	r &= 0xFF;
	g &= 0xFF;
	b &= 0xFF;
	uint32_t color = (((r << 16) & 0x00FF0000) | ((g << 8) & 0x0000FF00) | (b & 0x000000FF));

	if((x < width) && (y < height))
		buffer[x+(y*width)] = color;
	//std::cout << "color (" << x << ',' << y << ") = {" << r << ',' << g << ',' << b << "}\n";
}

void framebuffer::clear()
{
	memset(buffer, 0, size);
}

uint32_t &framebuffer::operator()(int x, int y)
{
	if((x < width) && (y < height))
		return buffer[x+(y*width)];
	return buffer[0];
}

void framebuffer::save(std::string name)
{
	std::ofstream of(name);

	of << "P3\n" << width << ' ' << height << "\n255\n";

	for(int i = 0; i < height; i++)
		for(int j = 0; j < width; j++)
		{
			uint32_t color = buffer[j+(i*width)];

			int r = (color >> 16) & 0xFF;
			int g = (color >> 8) & 0xFF;
			int b = (color) & 0xFF;

			of << r << ' ' << g << ' ' << b << '\n';
			//std::cout << r << ' ' << g << ' ' << b << ' ' << ((int)color) << '\n';
		}

	of.flush();
	of.close();
}

int framebuffer::w()
{
	return this->width;
}

int framebuffer::h()
{
	return this->height;
}

uint32_t framebuffer::sz()
{
	return this->size;
}
