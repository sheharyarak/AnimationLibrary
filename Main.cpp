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
	anim.set_canvas(Canvas(argv[1], argv[2]));
	anim.set_path("animation.gif");
	anim.set_frame_cnt(100);
	anim.initialize_frames();
	std::cout << anim.get_frames() << std::endl;
	std::cout << anim.get_frames()->size() << std::endl;
	Timer t("render time");
	anim.create_frames_threaded();
	Sprite s;
	anim.animate();
}
