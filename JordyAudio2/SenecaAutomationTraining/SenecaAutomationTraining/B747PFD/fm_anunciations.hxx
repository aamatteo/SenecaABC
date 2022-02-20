#ifndef FM_ANUNCIATIONS_HXX
#define FM_ANUNCIATIONS_HXX

#include "gl2dobject.hxx"
#include <vector>
using std::vector;

enum fm_mode {NONE=0, TOGA=1, HDG_HOLD=2, HDG_SEL=4, LNAV=8, LOC=16, ROLLOUT=32, 
  ATT=64, ALT=128, VS=256, VNAV_PTH=512, VNAV_SPD=1024, VNAV_ALT=2048, 
  GS=4096, FLARE=8192, FLCH_SPD=16384, THR_REF=32768, SPD=65536, IDLE=131072, 
  HOLD=262144, FD=524288, CMD=1048576, LAND2=2097152, LAND3=4194304, NO_AUTOLAND=8388608,
  MANEUVER= 16777216, RED_L=33554432, RED_R=67108864};

class fm_anunciations: public gl2DObject
{
  public:
    fm_anunciations();
    ~fm_anunciations();
    
    enum fm_type {ROLL, PITCH, AUTOTHROTTLE, AFDS_ENG, N_TYPES};
    
  protected:
    void draw();
    
  public:
    void init();
    
  public:
    void engage(int modes, bool reset_timer=true);
    void arm(int modes);
    void clear(int modes = -1);
    void update(float dt);
    
  private:
    static int              m_glId;
    vector<int>             m_engaged,
                            m_armed,
                            m_types;
    // Timers for boxes around indicators (boxes should be displayed the first 10 seconds after a state change)
    vector<float>           m_timers;

    static const char       *labels[28];
};

#endif
