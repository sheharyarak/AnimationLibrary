#ifndef SPRITE_H
#define SPRITE_H

#include "Drawable.hpp"

class Sprite : public Drawable
{
private:
	double v;
public:
	Sprite();
	Sprite(double x_, double y_, double v_, const Magick::Image &image_);
	double	get_v() const;
	void	set_v(double v);
	void	move_up();
	void	move_down();
	void	move_right();
	void	move_left();
	void	move();
};

#endif
