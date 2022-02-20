#ifndef GS_LOC_BAR_HXX
#define GS_LOC_BAR_HXX

#include "gl2dobject.hxx"

class gs_loc_bar: public gl2DObject
{
  public:
    gs_loc_bar(float x, float y, float phi, float maxangle, const char* name);
    ~gs_loc_bar();

  protected:
    void draw();

  public:
    void init();
    void angle(float a);

  private:
    static int              m_glId;
    float                   m_angle,
                            m_maxangle;
};

#endif
