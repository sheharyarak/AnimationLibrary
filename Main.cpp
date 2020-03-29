#include <Magick++.h>
#include "Animation.hpp"
#include "Sprite.hpp"
#include <iostream>
#include <bits/stdc++.h>
int main ()
{
	Magick::InitializeMagick(nullptr);
	Animation anim;
	anim.set_canvas(Canvas("100x100", "white"));
	anim.set_path("animation.gif");
	anim.set_frame_cnt(100);
	anim.initialize_frames();
	std::cout << anim.get_frames() << std::endl;
	std::cout << anim.get_frames()->size() << std::endl;
	anim.create_frames_in_order();
}
