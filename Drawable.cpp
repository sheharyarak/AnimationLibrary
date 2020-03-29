#include "Drawable.hpp"

Drawable::Drawable(): Magick::DrawableCompositeImage(0, 0, Magick::Image())
{

}

Drawable::Drawable(double x_, double y_, const Magick::Image &image_) : Magick::DrawableCompositeImage (x_, y_, image_)
{

}
void	Drawable::prepare_arc(int x, int y, double r)
{
	pivot_x = x;
	pivot_y = y;
	radius = r;
}
double	Drawable::get_pivot_x() const
{
	return pivot_x;
}
double	Drawable::get_pivot_y() const
{
	return pivot_y;
}
double	Drawable::get_radius () const
{
	return radius;
}
double	Drawable::get_height() const
{
	return height();
}
double	Drawable::get_width() const
{
	return width();
}
Magick::Image	Drawable::get_image() const
{
	return image();
}
double	Drawable::get_x() const
{
	return x();
}
double	Drawable::get_y() const
{
	return y();
}
void	Drawable::set_x(double x)
{
	this->x(x);
}
void	Drawable::set_y(double y)
{
	this->y(y);
}
void	Drawable::set_radius(double r)
{
	radius = r;
}
void	Drawable::set_height(double h)
{
	height(h);
}
void	Drawable::set_width(double w)
{
	width(w);
}
void	Drawable::set_image(Magick::Image image)
{
	this->image(image);
}
double	Drawable::get_theta() const
{
	return theta;
}
void	Drawable::set_theta_rad(double theta)
{
	this->theta = theta;
}
void	Drawable::set_theta_deg(double theta)
{
	this->theta = theta*(PI/180);
}
void	Drawable::set_theta(double y, double x)
{
	this->theta = std::atan2(y, x);
}
