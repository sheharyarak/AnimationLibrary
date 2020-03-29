#include <Magick++.h>
#include "Animation.hpp"
#include "Sprite.hpp"
#include "Timer.h"
#include <iostream>
#include <bits/stdc++.h>
int main (int argc, char *argv[])
{
	if(argc < 5)
	{
		std::cout << "Error: Invalid Arguments!" << std::endl
		<< "Usage: ./program width height color out_path" << std::endl;
		return 0;
	}
	//only compatible with linux for now
	Magick::InitializeMagick(nullptr);

	int width = std::stoi(argv[1]);
	int height = std::stoi(argv[2]);
	int padding = 60;
	std::string dim = std::to_string(width+padding) + "x" + std::to_string(height+padding);
//	start	setup
	Animation anim;
	if(argc > 5)
	{
		if(argv[5][0] == 't')
			anim.set_threaded(true);
		else
			anim.set_threaded(false);
	}
	anim.set_canvas(Canvas(dim, argv[3]));
	anim.set_path(argv[4]);
	anim.set_frame_cnt(360);
	anim.initialize_frames();
	Timer t("render time");
	anim.create_frames();
	t.age();
	anim.to_string();
//	end		setup
	Sprite a(width/2, height/2, 1, Magick::Image("Icons/Riolu20.png"));
	anim.track(&a);
	Sprite b(width/2, height/2, 1, Magick::Image("Icons/Riolu_shiny20.png"));
	anim.track(&b);
	Sprite c(width/2, height/2, 1, Magick::Image("Icons/Lucario20.png"));
	anim.track(&c);
	Sprite d(width/2, height/2, 1, Magick::Image("Icons/Lucario_shiny20.png"));
	anim.track(&d);
	a.prepare_arc(0, 0, 50 , 180);
	b.prepare_arc(0, 0, 50 , 0);
	c.prepare_arc(0, 0, 50, 90);
	d.prepare_arc(0, 0, 50, 270);

	//~ std::cout << "a.width: " << a.width() << " a.height: " << a.height() << std::endl;
	//~ std::cout << "a.image.width: " << a.get_image().columns() << " a.image.height: " << a.get_image().rows() << std::endl;
	//~ int i = 100;
	for(int i = 0; i < 360; i++)
	{
		a.move_arc();
		b.move_arc();
		c.move_arc();
		d.move_arc();
		anim.add_frame();
	}

	anim.animate();
}
