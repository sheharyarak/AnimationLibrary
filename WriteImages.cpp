#include "Animation.hpp"
/**********************************************
*
* Custom Write Function
* Please Work
* Oh God Please Work
*
* ********************************************
*/
//////////////////////////////////////////////////////////
//
// Implementation template definitions. Not for end-use.
//
//////////////////////////////////////////////////////////

// Link images together into an image list based on the ordering of
// the container implied by the iterator. This step is done in
// preparation for use with ImageMagick functions which operate on
// lists of images.
// Images are selected by range, first_ to last_ so that a subset of
// the container may be selected.  Specify first_ via the
// container's begin() method and last_ via the container's end()
// method in order to specify the entire container.
void	Animation::linkImages(std::vector<Magick::Image*>::iterator first_, std::vector<Magick::Image*>::iterator last_ )
{
	MagickLib::Image* previous = 0;
	int scene = 0;
	for ( std::vector<Magick::Image*>::iterator iter = first_; iter != last_; ++iter )
	{
		// Unless we reduce the reference count to one, the same image
		// structure may occur more than once in the container, causing
		// the linked list to fail.
		(*iter)->modifyImage();

		MagickLib::Image* current = (*iter)->image();

		current->previous = previous;
		current->next     = 0;
		current->scene    = scene++;

		if ( previous != 0)
			previous->next = current;

		previous = current;
	}
}

// Remove links added by linkImages. This should be called after the
// ImageMagick function call has completed to reset the image list
// back to its pristine un-linked state.
void	Animation::unlinkImages(std::vector<Magick::Image*>::iterator first_, std::vector<Magick::Image*>::iterator last_ )
{
	for( std::vector<Magick::Image*>::iterator iter = first_; iter != last_; ++iter )
	{
		MagickLib::Image* image = (*iter)->image();
		image->previous = 0;
		image->next = 0;
	}
}
// Write Images
//
// If an attribute is not supported as an explicit argument
// (e.g. 'magick'), then the attribute must be set on the involved
// images in the container prior to invoking writeImages() since
// attributes from the individual images are the ones which are
// used.
void	Animation::writeImages( std::vector<Magick::Image*>::iterator first_, std::vector<Magick::Image*>::iterator last_,
const std::string &imageSpec_,
bool adjoin_)
{

	(*first_)->adjoin( adjoin_ );

	MagickLib::ExceptionInfo exceptionInfo;
	MagickLib::GetExceptionInfo( &exceptionInfo );

	linkImages(first_, last_ );
	int errorStat = MagickLib::WriteImages( (*first_)->constImageInfo(),
	(*first_)->image(),
	imageSpec_.c_str(),
	&exceptionInfo );
	unlinkImages(first_, last_ );

	if ( errorStat != false )
	{
		MagickLib::DestroyExceptionInfo( &exceptionInfo );
		return;
	}

	Magick::throwException( exceptionInfo, (*first_)->quiet() );
}
/***********************************
*  end of custom code
***********************************
*/
