#include "Animation2.hpp"

void	start(
    std::string	path,	// output file path
    Canvas canvas,		// default background
    int frames,			// number frames to render
    bool threaded  = false	// use multithreading ?
)
{
    _path = path;
    _canvas = canvas;
    _frames = new std::deque<Magick::Image*>(frames);
    _threaded = threaded;
    if(threaded)
        create_frames_threaded();
    else
        create_frames_in_order();
}
void	end()
{
    ready();
    Magick::Image *image = (_frames)[0];
    image->adjoin(true);
    MagickLib::ExceptionInfo exceptioInfo;
    MagickLib::GetExceptionInfo(&exceptionInfo);
    int errorStat = MagickLib::WriteImages(
        image->constImageInfo(),
        image->image(),
        _path.c_str(),
        &exceptionInfo
    );
    if ( errorStat != false )
    {
        MagickLib::DestroyExceptionInfo( &exceptionInfo );
        return;
    }
    Magick::throwException( exceptionInfo, (*first_)->quiet() );
}
void	track (Drawable *object)
{
    _objects.push_back(object);
}
void	add_frames (int	n)
{
    for(int i = 0; i < n)
        _frames.push_back(new Magick::Image(_canvas.get_dimensions(), _canvas.get_color()));
}
void	delete_frames (int	n)
{
    ready();
    for(int i = 0; i < n)
        _frames.pop_back();
    //unlink frame
    Magick:::Image *image = _frames[_frames.size()-1];
    MagickLib::Image last = image->image();
    last->next = 0;
}
void	frame ()
{
    std::list<Magick::Drawable> objects;
    Magick::Image *image = (*frames)[_current_frame];
    for(unsigned int i = 0; i < objects.size(); i++)
    {
        drawables.push_back(*(objects[i]));
    }
    if(threaded)
    {
        futures.push_back(std::shared_future<void>(std::async(std::launch::async, render, image, objects, &futures, _current_frame, &mutex)));
    }
    else
    {
        image->draw(objects);
    }
}
void	render (
    int i,	//	index of frame to be rendered
    Canvas *canvas,			//	address of canvas
    std::deque<Magick::Image*> frames,	//deque of frames
    std::deque<std::shared_future<void>> futures //futures
)
{
    Magick::Image *image = (*frames)[i];
    image = new Magick::Image(_canvas.get_dimensions(), _canvas.get_color());
    //	link images
    image->modifyImage();
    MagickLib::Image *curr = image->image();
    futures[i].get();	//wait for previous frame to finish
    MagickLib::Image *prev = i == 0 ? 0 : (frames[i-1])[0]->image();
    curr->previous = prev;
    curr->next = 0;
    curr->scene = i;
    if(prev != 0)
        prev->next = current;
}
void	render (
    Magick::Image *image,	//	address of image onto which objects will be rendered
    std::list<Magick::Drawable> objects,	//	list of objects to be rendered
    std::deque<std::shared_future<void>> *futures,	//	address of futures vector
    int	future_index,	//	index of future
    std::mutex *mutex	// address of mutex
)
{
    (*futures)[future_index].get();	//	ensure that frame is available
    image->draw(objects);
}
void	print()
{
    std::cout << "path: " << _path << std::endl
    << "width: " << _canvas.get_width() << std::endl
    << "height: " << _canvas.get_height() << std::endl
    << "frames: " << _frames.size() << std::endl
    << "multi-threaded: " << std::boolalpha << threaded << std::endl;
}
void	ready()
{
    while(!_futures.empty())
    {
        _futures[0].get();
        _futures.pop_front();
    }
}