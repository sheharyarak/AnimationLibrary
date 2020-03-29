#include "Animation.hpp"

Animation::Animation()
{

}
Animation& Animation::getInstance()
{
	static	Animation anim;
	return anim;
}
void						Animation::define
										(std::string path_, int frame_cnt_, Canvas canvas_)
{
	this->path = path_;
	this->frame_cnt = frame_cnt_;
	this->canvas = canvas_;

}
std::vector<Magick::Image*>*	Animation::get_frames()
{
	return frames;
}
void						Animation::set_frames
										(std::vector<Magick::Image*>* frames)
{
	this->frames = frames;
}
void						Animation::set_objects
										(std::vector<Drawable*> &objs)
{
	this->objects = objects;
}
std::vector<Drawable*>&		Animation::get_objects()
{
	return objects;
}
std::vector<std::shared_future<void>>&	Animation::get_futures()
{
	return futures;
}
void	Animation::track(Drawable *obj)
{
	objects.push_back(obj);
}
void	Animation::inc_frames(int fc)
{
	for(int i = 0; i < fc; i++)
	{
		frames->push_back(new Magick::Image(canvas.get_dimensions(), canvas.get_color()));
		frame_cnt++;
	}
}
void	Animation::dec_frames(int fc)
{
	for(int i = 0; i < fc; i++)
	{
		frames->pop_back();
		fc--;
	}
}
void	Animation::add_frame()
{
	//~ std::vector<Magick::Drawable> drawings;
	//~ for(int i = 0; i < objects.size(); i++)
	//~ {
		//~ drawings.push_back(*(objects[i]));
	//~ }
	//~ futures[curr_frame].get();
	//~ ((*frames)[curr_frame])->draw(drawings);
	futures[curr_frame].get();
	for(int i = 0; i < objects.size(); i++)
	{
		((*frames)[curr_frame])->draw(*(objects[i]));
	}
}
void	Animation::animate()
{
	ready();
	writeImages(frames->begin(), frames->end(), path.c_str());
}
void	Animation::ready()
{
	for(auto future: futures)
		future.get();
}
void	Animation::initialize_frames()
{
	frames = new std::vector<Magick::Image*>(frame_cnt);
}
void					Animation::set_canvas(Canvas c)
{
	canvas = c;
}
Canvas					Animation::get_canvas()
{
	return canvas;
}
void					Animation::set_path(std::string p)
{
	path = p;
}
std::string				Animation::get_path()
{
	return path;
}
void					Animation::set_frame_cnt(int fc)
{
	frame_cnt = fc;
}
int						Animation::get_frame_cnt()
{
	return frame_cnt;
}
void	Animation::create_frames_threaded()
{
	for(int i = 0; i < frames->size(); i++)
		futures.push_back(std::shared_future<void>(std::async(std::launch::async, render, i, canvas, frames)));
}
void	render(int i, Canvas canvas, std::vector<Magick::Image*> *frames)
{
	(*frames)[i] = new Magick::Image(canvas.get_dimensions(), canvas.get_color());
}
void	Animation::create_frames_in_order()
{
	for(int i = 0; i < frames->size(); i++)
		(*frames)[i] = new Magick::Image(canvas.get_dimensions(), canvas.get_color());
}
void	Animation::track(Drawable *obj)
{
	objects.push_back(obj);
}
