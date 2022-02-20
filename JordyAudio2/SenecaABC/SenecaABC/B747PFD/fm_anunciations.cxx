#include "fm_anunciations.hxx"
#include <cmath>
#include <algorithm>

const char *fm_anunciations::labels[] = {"", "TO/GA", "HDG HOLD", "HDG_SEL", "LNAV", "LOC", "ROLLOUT", "ATT", "ALT", "V/S", "VNAV PTH", 
                        "VNAV SPD", "VNAV ALT", "G/S", "FLARE", "FLCH SPD", "THR REF", "SPD", "IDLE", "HOLD", "F/D", 
                        "CMD", "LAND2", "LAND3", "NO AUTOLAND", "!-MAN-!", "RED_LFT", "RED_RGHT"};

//! Retrieve the index of the lowest enabled bit in "mask"
inline int get_index(int mask)
{
  if (mask == 0)
    return 0;
  
  int ret = 1;
  while (!(mask & 1))
  {
    mask >>=1;
    ++ret;
  }
  return ret;
}

//! Retrieve the bitmask for enabled bit "bit"
inline int get_mask(int index)
{
  return (index<1 ? 0 : 1<<(index-1));
}

int fm_anunciations::m_glId = 0;

fm_anunciations::fm_anunciations():
    gl2DObject("fm_anunciations", 24.0f, 135.0f),
    m_engaged(4, NONE),
    m_armed(4, NONE),
    m_types(4),
    m_timers(4, 10.1f)
{
  /*! Initialize type categories
  -ROLL (center box item):        first 7 modes
  -PITCH (right box item):        mode  1 and 8 - 15
  -AUTOTHROTTLE (left box item):  modes 16 - 19
  -AFDS_ENG (label centered below FM anunciations box) */
  m_types[ROLL]         = (TOGA|HDG_HOLD|HDG_SEL|LNAV|LOC|ROLLOUT|ATT|MANEUVER);
  m_types[PITCH]        = (TOGA|ALT|VS|VNAV_PTH|VNAV_SPD|VNAV_ALT|GS|FLARE|FLCH_SPD|RED_R);
  m_types[AUTOTHROTTLE] = (THR_REF|SPD|IDLE|HOLD|RED_L);
  m_types[AFDS_ENG]     = (FD|CMD|LAND2|LAND3|NO_AUTOLAND|MANEUVER);
}

fm_anunciations::~fm_anunciations()
{
}

void fm_anunciations::init()
{
  if (m_glId == 0) // init already done for previous object?
  {
    // FM anunciations grey box and dividing lines
    m_glId = glGenLists(1);
    if (m_glId !=0)
    {
      glNewList(m_glId, GL_COMPILE);
      glColor3fv(Grey);
      glRectf(0.0f, 0.0f, 90.0f, 9.0f);
      
      glColor3fv(White);
      glBegin(GL_LINES);
      glVertex2f(30.0f, 0.0f);
      glVertex2f(30.0f, 9.0f);
      glVertex2f(60.0f, 0.0f);
      glVertex2f(60.0f, 9.0f);
      glEnd();
      
      glEndList();
    }
  }
}

void fm_anunciations::draw()
{
  glCallList(m_glId);  // draw anunciations box stockscene
  
  /*! --------------------------------------------------------------------------------------------------
      ENGAGED ITEMS ------------------------------------------------------------------------------------
      -------------------------------------------------------------------------------------------------- */
  glColor3fv(Red); //was Green
  float str_width;
  if (m_engaged[AFDS_ENG])
  {
    str_width = strokeString(labels[m_engaged[AFDS_ENG]], 45.0f, -15.0f, 4.0f, GLUT_STROKE_ROMAN, CENTER);
    if (m_timers[AFDS_ENG] <= 10.0f)
      wireBox(45.0f, -15.0f, (str_width + 2.0f), 6.0f, CENTER);
  }
  
  if (m_engaged[AUTOTHROTTLE])
  {
    str_width = strokeString(labels[m_engaged[AUTOTHROTTLE]], 15.0f, 6.75f, 2.5f, GLUT_STROKE_ROMAN, CENTER);
    if (m_timers[AUTOTHROTTLE] <= 10.0f)
      wireBox(15.0f, 6.75f, (str_width + 1.5f), 4.0f, CENTER);
  }
  if (m_engaged[ROLL])
  {
    str_width = strokeString(labels[m_engaged[ROLL]], 45.0f, 6.75f, 2.5f, GLUT_STROKE_ROMAN, CENTER);
    if (m_timers[ROLL] <= 10.0f)
      wireBox(45.0f, 6.75f, (str_width + 1.5f), 4.0f, CENTER);
  }
  if (m_engaged[PITCH])
  {
    str_width = strokeString(labels[m_engaged[PITCH]], 75.0f, 6.75f, 2.5f, GLUT_STROKE_ROMAN, CENTER);
    if (m_timers[PITCH] <= 10.0f)
      wireBox(75.0f, 6.75f, (str_width + 1.5f), 4.0f, CENTER);
  }
  
  /*! --------------------------------------------------------------------------------------------------
      ARMED ITEMS --------------------------------------------------------------------------------------
      -------------------------------------------------------------------------------------------------- */
  glColor3fv(White);
  if (m_armed[ROLL])
    strokeString(labels[m_armed[ROLL]], 45.0f, 2.25f, 2.5f, GLUT_STROKE_ROMAN, CENTER);
  if (m_armed[PITCH])
    strokeString(labels[m_armed[PITCH]], 75.0f, 2.25f, 2.5f, GLUT_STROKE_ROMAN, CENTER);
  
#if 0

  glColor3f(0.0f,0.85f,0.0f);
  if(_autoPilotDisengaged)
  strokeString(64.0f, 122.0f, "F/D", GLUT_STROKE_ROMAN, 0.04);
                                  else
                              {
		// FIXED AP SETTING TEXT
                                  strokeString(64.0f, 122.0f,"CMD", GLUT_STROKE_ROMAN, 0.04);
                                  strokeString(63.0f,138.0f,"LNAV", GLUT_STROKE_ROMAN, 0.035);

                                  if(_spd)
                                  strokeString(34.0f,138.0f,"SPD", GLUT_STROKE_ROMAN, 0.035);
/*		if(_flch)
                                  strokeString(94.0f,138.0f,"FLCH", GLUT_STROKE_ROMAN, 0.035);
*/

                                  switch(_apMode)
                              {
  case(PFD_B747::VS):
                                  strokeString(95.0f,138.0f,"V/S", GLUT_STROKE_ROMAN, 0.035);
                                  break;
  case(PFD_B747::ALT):
                                  strokeString(95.0f,138.0f,"ALT", GLUT_STROKE_ROMAN, 0.035);
                                  break;
  case(PFD_B747::ALTCAPTURE):
                              {
                                  strokeString(95.0f,138.0f,"ALT", GLUT_STROKE_ROMAN, 0.035);
                                  glBegin(GL_LINE_LOOP);
                                  glVertex2f(93.0f,137.0f);
                                  glVertex2f(93.0f,143.0f);
                                  glVertex2f(105.0f,143.0f);
                                  glVertex2f(105.0f,137.0f);
                                  glEnd();
}
                                  break;
}
}
#endif
}

void fm_anunciations::engage(int modes, bool reset_timer)
{
  for (int i = 0; i < N_TYPES; ++i)
    // If we have a flag of type 'i' in 'modes', enable it:
    if (int mode_i = get_index((m_types[i] & modes)))
      if (m_engaged[i] != mode_i)
      {
        m_engaged[i] = mode_i;
        if (reset_timer)
          m_timers[i] = 0.0f;
        // If this flag was armed first, remove armed flag
        if (m_armed[i] == m_engaged[i])
          m_armed[i] = NONE;
      }
}

void fm_anunciations::arm(int modes)
{
  for (int i = 0; i < N_TYPES; ++i)
    // If we have a flag of type 'i' in 'modes', enable it:
    if (int mode_i = (m_types[i] & modes))
      m_armed[i] = get_index(mode_i);
}

void fm_anunciations::clear(int modes)
{
  // clear all labels
  if (modes == -1)
    for (int i = 0; i < N_TYPES; ++i)
    {
      m_engaged[i]  = NONE;
      m_armed[i]    = NONE;
      m_timers[i]   = 10.1f;
    }
  
  // Loop through the engaged and armed labels and check if any of <modes> are active
  for (int i = 0; i < N_TYPES; ++i)
  {
    if (modes & get_mask(m_engaged[i]))
    {
      m_engaged[i]  = NONE;
      m_timers[i]   = 10.1f;
    }
    if (modes & get_mask(m_armed[i]))
      m_armed[i]    = NONE;
  }
}

void fm_anunciations::update(float dt)
{
  // Increase timers, with an upper bound slightly over 10.0 (seconds)
  m_timers[ROLL]          = std::min(10.1f, m_timers[ROLL] + dt);
  m_timers[PITCH]         = std::min(10.1f, m_timers[PITCH] + dt);
  m_timers[AUTOTHROTTLE]  = std::min(10.1f, m_timers[AUTOTHROTTLE] + dt);
  m_timers[AFDS_ENG]      = std::min(10.1f, m_timers[AFDS_ENG] + dt);
}
