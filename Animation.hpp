#ifndef ANIMATION_H
#define ANIMATION_H

#include "Drawable.hpp"
#include "Canvas.hpp"
#include "WriteImages.hpp"
#include <vector>
#include <future>
#include <mutex>

class Animation
{
private:
	static	std::vector<Drawable*> objects;
	static	std::vector<Magick::Image*> *frames;
	static	std::mutex anim_mutex;
	static	std::vector<shared_future<void>> future_frames;
	static	Canvas canvas;
	int	frame_cnt = 0;
	int index = 0;
	bool	init = false;
	std::string name = "animation.gif";
	void	initialize_frames();
	static	void	set_frame(int i);
public:
	void	Animation();
	void	Animation(std::string name_, int frame_cnt_, Canvas canvas_);
	void	track(Drawable *obj);
	void	inc_frames(int fc);
	void	dec_frames(int fc);
	void	add_frame();
	void	animate();
	void	ready();
};

#endif
