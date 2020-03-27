#include "Canvas.hpp"

Canvas::Canvas()
{
	bg = Magick::Image("100x100", "white"); 
	this->dimensions = "100x100";
	this->color = "white";
}
Canvas::Canvas(std::string dimensions, std::string color)
{
	this->dimensions = dimensions;
	this->color = color;
	bg = Magick::Image(dimensions, color);
}
int		Canvas::get_width() const
{
	return	bg.columns();
}
int		Canvas::get_height() const
{
	return bg.rows();
}
Magick::Image	Canvas::get_background() const
{
	return bg;
}
void	Canvas::set_background(Magick::Background background)
{
	bg = background;
}
std::string	get_dimensions() const
{
	return dimensions;
}
std::string	get_color() const
{
	return color;
}