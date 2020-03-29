#ifndef CANVAS_H
#define CANVAS_H

#include <Magick++.h>

class Canvas
{
private:
	/* data */
	std::string		color;
	std::string		dimensions;
	Magick::Image	bg;
public:
	Canvas();
	Canvas(std::string dimensions, std::string color);
	Canvas(Magick::Image bg);
	std::string	get_dimensions() const;
	std::string	get_color() const;
	int		get_width() const;
	int		get_height() const;
	Magick::Image	get_background() const;
	void	set_background(Magick::Image);
};

#endif
