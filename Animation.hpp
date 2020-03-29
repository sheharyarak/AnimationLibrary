#ifndef ANIMATION_H
#define ANIMATION_H

#include "Drawable.hpp"
#include "Canvas.hpp"
#include <vector>
#include <future>
#include <mutex>
#include <list>
#include <deque>


class	Animation
{
private:
std::vector<Drawable*>					objects;
std::vector<Magick::Image*>*			frames;
std::mutex								mutex;
std::deque<std::shared_future<void>>	futures;
int										frame_cnt;
int										curr_frame = 0;
Canvas									canvas;
std::string								path;
static	bool							init;
bool						threaded = false;

public:
Animation();
static	Animation& 						getInstance();
void									define
										(std::string path_, int frame_cnt_, Canvas canvas_);
std::vector<Magick::Image*>*			get_frames();
void									set_frames
										(std::vector<Magick::Image*> *new_frames);
void									set_objects
										(std::vector<Drawable*> &objs);
std::vector<Drawable*>&					get_objects();
std::deque<std::shared_future<void>>&	get_futures();
void									set_futures
										(std::deque<std::shared_future<void>> &futures);
void									set_canvas(Canvas c);
Canvas									get_canvas();
void									set_path(std::string p);
std::string								get_path();
void									set_frame_cnt(int fc);
int										get_frame_cnt();
void									track(Drawable *obj);
void									inc_frames(int fc);
void									dec_frames(int fc);
void									add_frame();
void									animate();
void									ready();
static	void	linkImages(std::vector<Magick::Image*>::iterator first_,
std::vector<Magick::Image*>::iterator last_ );
static	void	unlinkImages(std::vector<Magick::Image*>::iterator first_,
 std::vector<Magick::Image*>::iterator last_ );
static	void	writeImages( std::vector<Magick::Image*>::iterator first_,
 std::vector<Magick::Image*>::iterator last_,
const std::string &imageSpec_, bool adjoin_ = true );
static		Animation start(std::string path, int fc, Canvas c);
void		initialize_frames();
void		create_frames_threaded();
void		create_frames_in_order();
void		set_threaded(bool b);
void		create_frames();
void		to_string();
};
void	render_frame(int i, Canvas canvas, std::vector<Magick::Image*> *frames);
void	render_objects(Magick::Image *image, std::list<Magick::Drawable> drawables, std::deque<std::shared_future<void>> *futures, int index, std::mutex *mutex);

#endif
