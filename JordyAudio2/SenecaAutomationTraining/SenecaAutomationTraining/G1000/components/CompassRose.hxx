/* ------------------------------------------------------------------   */
/*      item            : CompassRose.hxx
        made by         : jcomans
        from template   : hmigauge.hxx
        template made by: Joost Ellerbroek
        date            : 081013
        category        : header file
        description     : 
        changes         : 081013 first version
        language        : C++
*/

#ifndef CompassRose_hxx
#define CompassRose_hxx

#include <GaugeComponent.hxx>
#include "CompassRoseData.hxx"

class CompassRose: public hmi::GaugeComponent
{
public:
  CompassRose();
  ~CompassRose();

public:
  void Init();
  void Render();

private:
  void addText(float heading);

public:
  CompassRoseData& GetData() {return data;}

private:
  CompassRoseData data;

  GLuint     _gl_display_list_index;
  hmi::Font* _font;
};

#endif
