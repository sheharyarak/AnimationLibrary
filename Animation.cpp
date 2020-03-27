#include "Animation.hpp"

void	Animation(){}
void	Animation(std::string name_, int frame_cnt_, Canvas canvas_)
{
	name = name_; frame_cnt = frame_cnt_; canvas = canvas_;
	frames = new std::vector<Magick::Image*>(frame_cnt);
	initialize_frames();
}
static	void	set_frame(int i)
{
	(*frames)[i] = new Image(canvas.get_dimensions(), canvas.get_color());
}
void	Animation::initialize_frames()
{
	for(int i = 0; i < frames.size(); i++)
		future_frames.push_back(std::shared_future<void>(std::async(std::launch::async, set_frame, i)));
}
void	Animation::track(Drawable *obj)
{
	objects.push_back(obj);
}
void	Animation::inc_frames(int fc)
{
	for(int i = 0; i < fc; i++)
		frames.push_back(canvas.get_image());
}
void	Animation::dec_frames(int fc)
{
	ready();
	for(int i = 0; i < fc; i++)
		frames.pop_back();
}
void	Animation::add_frame()
{
	std::vector<Magick::DrawableCompositeImage> drawings(objects.begin(), objects.end());
	future_frames[index].get();
	frames[index]->draw(drawings);
}
void	Animation::animate()
{
	ready();
	writeImages(frames.begin(), frames.end(), path);
}
void	Animation::ready()
{
	for(auto future: future_frames)
		future.get();
}

static	std::vector<Drawable*> objects;
static	std::vector<Magick::Image*> *frames;
static	std::mutex anim_mutex;
static	std::vector<shared_future<void>> future_frames;
static	Canvas canvas;
