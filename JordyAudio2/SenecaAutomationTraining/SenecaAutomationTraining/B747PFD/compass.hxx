#ifndef COMPASS_HXX
#define COMPASS_HXX

#include "gl2dobject.hxx"


class compass: public gl2DObject
{
  public:
    compass();
    ~compass();
  
  protected:
    void draw();
  
  public:
    void init();
  
  public:
    void  selectedHeading(float Heading);
    float selectedHeading() {return m_selectedHeading;};
    
    void  currentHeading(float Heading);
    float currentHeading() {return m_currentHeading;};
    
    void  trackAngle(float angle);
    float trackAngle() {return m_trackAngle;};
    void enableHeadingBug()  {_draw_heading_bug = true;};
    void disableHeadingBug() {_draw_heading_bug = false;};
  private:
    int m_stockId;
    float m_currentHeading, m_trackAngle, m_selectedHeading; // [deg]
    bool _draw_heading_bug;
};

#endif
