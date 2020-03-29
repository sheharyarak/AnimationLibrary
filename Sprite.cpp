#include "Sprite.hpp"

Sprite::Sprite()
{
	v = 0;
}
Sprite::Sprite(double x_, double y_, double v_, const Magick::Image &image_)
{
	x(x_);
	y(y_);
	v = v_;
	image(image_);
	width(image_.columns());
	height(image_.rows());

}
void	Sprite::move_up()
{
	y(y()-v);
}
void	Sprite::move_down()
{
	y(y()+v);
}
void	Sprite::move_right()
{
	x(x()+v);
}
void	Sprite::move_left()
{
	x(x()-v);
}
void	Sprite::move()
{
	x(x()+v*std::sin(theta));
	y(y()+v*std::cos(theta));
}
