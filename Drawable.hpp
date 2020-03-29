#ifndef DRAWABLE_H
#define DRAWABLE_H

#include <Magick++.h>
#include <cmath>

const double PI = 3.14159265358979;
class Drawable : public Magick::DrawableCompositeImage
{
protected:
	/* data */
	double	pivot_x = 0;
	double	pivot_y = 0;
	double	radius = 0;
	double	theta = 0;
public:
	Drawable();
	Drawable(double x_, double y_, const Magick::Image &image_);
	void	prepare_arc(int x, int y, double r);
	double	get_pivot_x() const;
	double	get_pivot_y() const;
	double	get_radius () const;
	double	get_height() const;
	double	get_width() const;
	double	get_x() const;
	double	get_y() const;
	double	get_theta() const;
	Magick::Image	get_image() const;
	void	set_theta_rad(double theta);
	void	set_theta_deg(double theta);
	void	set_theta(double y, double x);
	void	set_x(double x);
	void	set_y(double y);
	void	set_radius(double r);
	void	set_height(double h);
	void	set_width(double w);
	void	set_image(Magick::Image image);
};

#endif
