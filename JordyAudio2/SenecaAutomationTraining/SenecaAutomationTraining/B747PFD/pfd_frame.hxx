#ifndef PFD_FRAME_HXX
#define PFD_FRAME_HXX

#include "gl2dobject.hxx"


class pfd_frame: public gl2DObject
{
  public:
    pfd_frame();
    ~pfd_frame();
  
  protected:
    void draw();
  
  public:
    void init();
  
  public:
  private:
};

#endif
