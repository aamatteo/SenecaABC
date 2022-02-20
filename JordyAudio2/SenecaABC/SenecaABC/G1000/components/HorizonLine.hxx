/* ------------------------------------------------------------------   */
/*      item            : HorizonLine.hxx
        made by         : jcomans
        from template   : hmigauge.hxx
        template made by: Joost Ellerbroek
        date            : 081013
        category        : header file
        description     : 
        changes         : 081013 first version
        language        : C++
*/

#ifndef HorizonLine_hxx
#define HorizonLine_hxx

#include <GaugeComponent.hxx>
#include "HorizonLineData.hxx"

class HorizonLine: public hmi::GaugeComponent
{
public:
  HorizonLine();
  ~HorizonLine();

public:
  void Init();
  void Render();

public:
  HorizonLineData& GetData() {return data;}

private:
  HorizonLineData data;

  GLuint _gl_display_list_index;
};

#endif
