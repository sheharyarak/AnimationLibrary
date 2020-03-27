#include "WriteImages.hpp"
//
// Implementation template definitions. Not for end-use.
//
// Link images together into an image list based on the ordering of
// the container implied by the iterator. This step is done in
// preparation for use with ImageMagick functions which operate on
// lists of images.
// Images are selected by range, first_ to last_ so that a subset of
// the container may be selected.  Specify first_ via the
// container's begin() method and last_ via the container's end()
// method in order to specify the entire container.

template <class InputIterator>
bool linkImages( InputIterator first_,
     InputIterator last_ ) {
  MagickCore::Image* previous = 0;
  ::ssize_t scene = 0;
  for ( InputIterator iter = first_; iter != last_; ++iter )
  {
    // Unless we reduce the reference count to one, the same image
    // structure may occur more than once in the container, causing
    // the linked list to fail.
    (*iter)->modifyImage();
    MagickCore::Image* current = (*iter)->image();
    current->previous = previous;
    current->next = 0;
    current->scene = scene++;
    if ( previous != 0)
      previous->next = current;
    previous = current;
  }
  return(scene > 0 ? true : false);
}
// Remove links added by linkImages. This should be called after the
// ImageMagick function call has completed to reset the image list
// back to its pristine un-linked state.
template <class InputIterator>
void unlinkImages( InputIterator first_,
       InputIterator last_ ) {
  for( InputIterator iter = first_; iter != last_; ++iter )
    {
MagickCore::Image* image = (*iter)->image();
image->previous = 0;
image->next = 0;
    }
}
// Write Images
template <class InputIterator>
void writeImages( InputIterator first_,
      InputIterator last_,
      const std::string &imageSpec_,
      bool adjoin_ = true ) {
  if (linkImages(first_,last_) == false)
    return;
  (*first_)->adjoin( adjoin_ );
  GetPPException;
  ::ssize_t errorStat = MagickCore::WriteImages( (*first_)->constImageInfo(),
                                          (*first_)->image(),
                                          imageSpec_.c_str(),
                                          exceptionInfo );
  unlinkImages( first_, last_ );
  if ( errorStat != false )
    {
      (void) MagickCore::DestroyExceptionInfo( exceptionInfo );
      return;
    }
  ThrowPPException((*first_)->quiet());
}