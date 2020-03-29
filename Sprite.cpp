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
	x(x()+v*std::sin(theta*(PI/180)));
	y(y()+v*std::cos(theta*(PI/180)));
}
void	Sprite::move_arc()
{
	x(pivot_x + radius*std::cos(theta*(PI/180)));
	y(pivot_y - radius*std::sin(theta*(PI/180)));
	theta += v;
}
double	Sprite::get_v() const
{
	return v;
}
void	Sprite::set_v(double v)
{
	this->v = v;
}
void	Sprite::change_direction()
{
	this->v *= -1;
}
