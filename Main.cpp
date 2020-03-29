#include <Magick++.h>
#include "Animation.hpp"
#include "Sprite.hpp"
#include "Timer.h"
#include <iostream>
#include <bits/stdc++.h>
int main (int argc, char *argv[])
{
	if(argc == 1) return 0;

	Magick::InitializeMagick(nullptr);
	Animation anim;
	int width = std::stoi(argv[1]);
	int height = std::stoi(argv[2]);
	std::string dim = std::to_string(width) + "x" + std::to_string(height);
	std::cout << "w: " << width << std::endl;
	std::cout << "h: " << height << std::endl;
	std::cout << "d: " << dim << std::endl;
	anim.set_canvas(Canvas(argv[1], argv[3]));
	anim.set_path("animation.gif");
	anim.set_frame_cnt(100);
	anim.initialize_frames();
	std::cout << anim.get_frames() << std::endl;
	std::cout << anim.get_frames()->size() << std::endl;
	Timer t("render time");
	anim.create_frames_threaded();
	Sprite a(width/2, height/2, 1, Magick::Image("Icons/Riolu.png"));
	anim.track(&a);
	Sprite b(width/2, height/2, 1, Magick::Image("Icons/Riolu_shiny.png"));
	anim.track(&b);
	Sprite c(width/2, height/2, 1, Magick::Image("Icons/Lucario.png"));
	anim.track(&c);
	Sprite d(width/2, height/2, 1, Magick::Image("Icons/Lucario_shiny.png"));
	anim.track(&d);

	std::cout << "a.width: " << a.width() << " a.height: " << a.height() << std::endl;
	std::cout << "a.image.width: " << a.get_image().columns() << " a.image.height: " << a.get_image().rows() << std::endl;
	//~ int i = 100;
	while(((a.get_y() < height) and (a.get_y() > 0)))
	{
		a.move_up();
		b.move_down();
		c.move_left();
		d.move_right();
		anim.add_frame();
		//~ std::cout << "i: " << i << " a.y: " << a.get_y() << std::endl;
		//~ if(i < 0)	break;
		//~ i--;
	}
	anim.animate();
}
