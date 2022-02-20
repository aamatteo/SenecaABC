#ifndef ATTITUDE_INDICATOR_HXX
#define ATTITUDE_INDICATOR_HXX

#include "gl2dobject.hxx"


class attitude_indicator: public gl2DObject
{
  public:
    attitude_indicator();
    ~attitude_indicator();
  
  protected:
    void draw();
  
  public:
    void init();
  
  public:
    void setAttitude(float pitch, float bank);
    void setSideSlip(float slip, bool Slip_top, bool Slip_beta, float Climb);
    void setFDBarsDeg(float theta, float phi);
    void setFDBarsRad(float theta, float phi);
  void showFD(bool b);
  
  private:
    int   m_att_stock1, m_att_stock2, m_flightdirbar_stock,m_climb_stock;
    float m_bank, m_pitch, m_thetaFD, m_phiFD, m_slip,m_climb,dx1,dy1,dx2,dy2;
    bool  m_FDEngaged, m_slip_top, m_slip_beta;
};

#endif
