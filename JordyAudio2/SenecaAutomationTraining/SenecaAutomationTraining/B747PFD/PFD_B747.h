//-----------------------------------------------------------------------------
//
// PFD_B747.h
//
// Copyright (C) 2000:  Delft University of Technology,
//			Fac. Aerospace Engineering,
//			Control & Simulation
//
// Description:This class draws an OpenGL B747-400 Primary Flight Display
//
// Created: by Z.C. Roza on 29-6-2002
// Updated: by <name> on <date>
//
//------------------------------------------------------------------------------


#ifndef PFD_B747_H
#define PFD_B747_H

//------------------------------------------------------------------------------
// Include files
//------------------------------------------------------------------------------
#include "WglClientAreaUser.h"
#include "gl2dobject.hxx"

// This includes headers for the objects that are sent over the channels
#include "comm-objects.h"

//------------------------------------------------------------------------------
// Types & Enums
//------------------------------------------------------------------------------
#ifndef MY_PI
#define MY_PI 3.1415926535897
#endif
#ifndef rad2deg
#define rad2deg 57.29577951
#endif

//------------------------------------------------------------------------------
// Forward declarations
//------------------------------------------------------------------------------



//------------------------------------------------------------------------------
// PFD_B747 Class Declaration
//------------------------------------------------------------------------------
class PFD_B747: public WglClientAreaUser
{
  public:

    //--------------------------------------------------------------------------
    // Types & Enums
    //--------------------------------------------------------------------------
    enum apMode {VS, ALTCAPTURE, ALT};

    //--------------------------------------------------------------------------
    // Methods
    //--------------------------------------------------------------------------

    // CONSTRUCTORS
    PFD_B747();
    PFD_B747(const char *window_title, bool mouse_passive);
  
    // DESTRUCTOR
    virtual ~PFD_B747();

    // INTERFACE METHODS
    
    // inherited from DuecaGLWindow
    virtual void display ();
    virtual void initGL ();

    // main drawing Method
    void renderPFD();
  
    // MODIFIER METHODS
    void selectedVertSpeed(float Vspd);
    void selectedTas(float Tas);
    void selectedAlt(float Alt);

    void setAircraftState(float ias, float mach, float rc, float alt);

    void setApModeIndication(bool spd, bool flch, bool hdg, bool vspd, bool alt, apMode curMode);
    void setAltitudeOffset(int altOffset);
    void disableSpdBug(void);                                       //f
    void enableSpdBug(void);					//f
    void disableAltBug(void);                                       //f
    void enableAltBug(void);					//f
    void setILS(const float& dme){_ILS_DME = dme;}

    // for speed trend
    void setCurrentTime(double sec);
    void renderSpeedTrend();
    void renderSpeedLimits();
    
    // For speed limits
    void updateReferenceData(int selectedFlapAngle, int landingFlapAngle, float Vref, float Vstall,
                             float Vplackard, float Vmaneuver, float V1, float V2, float FAS);
  
    // ACCESSOR FUNCTIONS
    double getSelectedVertSpd()         {return _selectedVertSpd;}
    double getSelectedTas()             {return _selectedTas;}
    double getSelectedAlt()             {return _selectedAlt;}
    
    void set2DObjectRoot(gl2DObject* obj);

    inline void setSpeedsSet(int i){_speedsSet= ( (i>=0 && i <=1)?i:0);}

  protected:

    //--------------------------------------------------------------------------
    // Protected Member Data
    //--------------------------------------------------------------------------

    // AP MODE
    bool                    _spd;
    bool                    _flch;
    bool                    _hdg;
    bool                    _vspd;
    bool                    _alt;
    apMode                  _apMode;
    bool                    _spdBugOn;              // f
    bool                    _altBugOn;              // f

    // AP SETTINGS
    float                   _selectedVertSpd;       // [ft/min]
    float                   _selectedTas;           // [knots]
    float                   _selectedAlt;           // [ft]

    // AC STATE
    float                   currentMach;            // []
    float                   trueAirspeed;           // [knots]
    float                   currentAlt;             // [ft]
    float                   currentRC;              // [ft/min]

    float                   currentFlapPos;
    int                     _selectedFlapAngle;
    int                     _landingFlapAngle;
    float                   _ILS_DME;

    // Speed limits
    float _Vref;
    float _Vstall;
    float _Vplackard;
    float _Vmaneuver;
    float _V1;
    float _V2;
    float _FAS;


    // Display Altitude Offset
    int   _altOffset;	// [ft]

    // Time (for speed trend)
    double   _curTimeSec;

    // ID for speed limits set
    int _speedsSet;

  private:

    //--------------------------------------------------------------------------
    // Private Member Data
    //--------------------------------------------------------------------------
    char		_textString[256];	 // generic text container

    gl2DObject*         _2dobjectroot;
};	// End PFD_B747 class

#endif // PFD_B747_H
