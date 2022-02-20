/* ------------------------------------------------------------------   */
/*      item            : PitchLadder.hxx
        made by         : jcomans
        from template   : hmigauge.hxx
        template made by: Joost Ellerbroek
        date            : 081013
        category        : header file
        description     : 
        changes         : 081013 first version
        language        : C++
*/

#ifndef PitchLadder_hxx
#define PitchLadder_hxx

#include <GaugeComponent.hxx>
#include "PitchLadderData.hxx"

class PitchLadder: public hmi::GaugeComponent
{
public:
  PitchLadder();
  ~PitchLadder();

public:
  void Init();
  void Render();

private:
  void drawLadder(float pitch,
		  float half_tick_width, float spacing,
		  float start_tick, size_t n_ticks,
		  bool draw_labels);
  
public:
  PitchLadderData& GetData() {return data;}

private:
  PitchLadderData data;

  GLuint     _gl_display_list_index;
  hmi::Font* _font;
};

#endif
