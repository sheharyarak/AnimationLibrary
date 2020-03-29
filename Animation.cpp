#include "Animation.hpp"

//~ Animation::Animation(){}
//~ void	Animation::define(std::string path_, int frame_cnt_, Canvas canvas_)
//~ {
	//~ path = path_; frame_cnt = frame_cnt_; canvas = canvas_;
	//~ frames = new std::vector<Magick::Image*>(frame_cnt);
	//~ initialize_frames();
//~ }
//~ static	void	Animation::set_frame(int i)
//~ {
	//~ (*frames)[i] = new Image(canvas.get_dimensions(), canvas.get_color());
//~ }
//~ void	Animation::initialize_frames()
//~ {
	//~ for(int i = 0; i < frames.size(); i++)
		//~ future_frames.push_back(std::std::shared_future<void>(std::async(std::launch::async, set_frame, i)));
//~ }
//~ void	Animation::track(Drawable *obj)
//~ {
	//~ objects.push_back(obj);
//~ }
//~ void	Animation::inc_frames(int fc)
//~ {
	//~ for(int i = 0; i < fc; i++)
		//~ frames.push_back(canvas.get_image());
//~ }
//~ void	Animation::dec_frames(int fc)
//~ {
	//~ ready();
	//~ for(int i = 0; i < fc; i++)
		//~ frames.pop_back();
//~ }
//~ void	Animation::add_frame()
//~ {
	//~ std::vector<Magick::DrawableCompositeImage> drawings(objects.begin(), objects.end());
	//~ future_frames[index].get();
	//~ frames[index]->draw(drawings);
//~ }
//~ void	Animation::animate()
//~ {
	//~ ready();
	//~ writeImages(frames.begin(), frames.end(), path);
//~ }
//~ void	Animation::ready()
//~ {
	//~ for(auto future: future_frames)
		//~ future.get();
//~ }

//~ static	std::vector<Drawable*> objects;
//~ static	std::vector<Magick::Image*> *frames;
//~ static	std::mutex anim_mutex;
//~ static	std::vector<std::shared_future<void>> future_frames;
//~ static	Canvas canvas;

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
	//~ writeImages(frames->begin(), frames->end(), path.c_str());
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
