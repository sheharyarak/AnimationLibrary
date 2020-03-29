#include <Magick++.h>
#include "Animation.hpp"
#include "Sprite.hpp"
#include "Timer.h"
#include <iostream>
#include <bits/stdc++.h>
int main (int argc, char *argv[])
{
	Timer xyz("Total runtime");
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
	int fc = 100;
	if(argc > 6)
		fc = std::stoi(argv[6]);
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
	anim.set_frame_cnt(fc);
	anim.initialize_frames();
	Timer t("render time");
	anim.create_frames();
	anim.ready();
	t.age("Blank Frames");
	anim.to_string();
	//	setup	end
	std::vector<Sprite> sprites;
	sprites.push_back(Sprite(width/2, height/2, 1, Magick::Image("Icons/Riolu20.png")));
	sprites.push_back(Sprite(width/2, height/2, 1, Magick::Image("Icons/Riolu_shiny20.png")));
	sprites.push_back(Sprite(width/2, height/2, 1, Magick::Image("Icons/Lucario20.png")));
	sprites.push_back(Sprite(width/2, height/2, 1, Magick::Image("Icons/Lucario_shiny20.png")));
	for(unsigned int i = 0; i < sprites.size(); i++)
		anim.track(&sprites[i]);
	sprites[0].set_v(1);
	sprites[1].set_v(-1);
	sprites[2].set_v(1);
	sprites[3].set_v(-1);
	sprites[0].set_theta(height, width);
	sprites[1].set_theta(height, width);
	sprites[2].set_theta_deg(0);
	sprites[3].set_theta_deg(90);
	for(auto a: sprites)
	{
		a.x(a.x()-(a.get_width()/2)); a.y(a.y()-(a.get_height()/2));
	}
	t.reset();
	for(int i = 0; i < fc; i++)
	{
		for(auto obj: anim.get_objects())
		{
			obj->move();
			if(	obj-> x() < 0 or
				obj->x() > anim.get_canvas().get_width() or
				obj->y() < 0 or
				obj->y() > anim.get_canvas().get_height()
				)
				obj->change_direction();
		}
		//~ std::cout<< i <<std::endl;
		anim.add_frame();
	}
	t.age("render objects");
	std::cout<<anim.get_futures().size()<<std::endl;
	anim.animate();
	std::cout<<std::endl;
}
