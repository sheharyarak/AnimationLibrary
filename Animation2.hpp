#ifndef ANIMATION_H
#define ANIMATION_H

#include <Magick++.h>
#include "Drawable.hpp"
#include "Canvas.hpp"
#include <vector>
#include <future>
#include <mutex>
#include <list>
#include <deque>
#include <iostream>

namespace   Animation
{
	/*
	 * Created an anonymous namespace.
	 * Everything within this namespace acts as a private member
	 * of a hypothetical 'Animation Class'.
	 * Everything outside the anonymous namespace
	 * but with the Animation namespace
	 * behaves as a public member of a hypothetical 'Animation Class'.
	 */
	namespace	// anonymous namepace
	{
		//	attributes
		std::deque<Magick::Image*>				*_frames;
		std::deque<std::shared_future<void>>	_futures;
		std::deque<Drawable*>					_objects;
		Canvas									_canvas;
		std::string								_path;
		bool									_init;
		bool									_threaded;
		int										_current_frame = 0;
		std::mutex								_mutex;
		//	functions
		void	create_frames_in_order()
		{
			MagickLib::Image *prev = 0;
			for(unsigned int i = 0; i < _frames->size(); i++)
			{
				Magick::Image *image = (*_frames)[i];
				image = new Magick::Image(_canvas.get_dimensions(), _canvas.get_color());
				//link frames
				image->modifyImage();
				MagickLib::Image *curr = image->image();
				curr->previous = prev;
				curr->next = 0;
				curr->scene = i;
			}
		}
		void	create_frames_threaded()
		{
			for(unsigned int i = 0; i < _frames->size(); i++)
			{
				_futures.push_back(std::shared_future<void>(std::async(std::launch::async, render, i, _canvas, _frames, _futures)));
			}
		}
	}
	void	start(
		std::string	path,	// output file path
		Canvas canvas,		// default background
		int frames,			// number frames to render
		bool threaded  = false	// use multithreading ?
	);
	void	end();
	void	track (Drawable *object);
	void	add_frames (int	n);
	void	delete_frames (int	n);
	void	frame ();
	void	render (
		int i,	//	index of frame to be rendered
		Canvas *canvas,			//	address of canvas
		std::deque<Magick::Image*> frames,	//deque of frames
		std::deque<std::shared_future<void>> futures //futures
	);
	void	render (
		Magick::Image *image,	//	address of image onto which objects will be rendered
		std::list<Magick::Drawable> objects,	//	list of objects to be rendered
		std::deque<std::shared_future<void>> *futures,	//	address of futures vector
		int	future_index,	//	index of future
		std::mutex *mutex	// address of mutex
	);
	void	print();
	void	ready();
}

#endif