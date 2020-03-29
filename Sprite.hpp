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
virtual	void	move_up();
virtual	void	move_down();
virtual	void	move_right();
virtual	void	move_left();
virtual	void	move();
virtual	void	move_arc();
virtual	void	change_direction();
};

#endif
