/* ------------------------------------------------------------------   */
/*      item            : VerticalSpeedTape.hxx
        made by         : jcomans
        from template   : hmigauge.hxx
        template made by: Joost Ellerbroek
        date            : 081013
        category        : header file
        description     : 
        changes         : 081013 first version
        language        : C++
*/

#ifndef VerticalSpeedTape_hxx
#define VerticalSpeedTape_hxx

#include <GaugeComponent.hxx>
#include "VerticalSpeedTapeData.hxx"

class VerticalSpeedTape: public hmi::GaugeComponent
{
public:
  VerticalSpeedTape();
  ~VerticalSpeedTape();

public:
  void Init();
  void Render();

public:
  VerticalSpeedTapeData& GetData() {return data;}
  
private:
  VerticalSpeedTapeData data;
};

#endif
