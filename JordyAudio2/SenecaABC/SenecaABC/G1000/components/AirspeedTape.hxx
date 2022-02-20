/* ------------------------------------------------------------------   */
/*      item            : AirspeedTape.hxx
        made by         : jcomans
        from template   : hmigauge.hxx
        template made by: Joost Ellerbroek
        date            : 081013
        category        : header file
        description     :
        changes         : 081013 first version
        language        : C++
*/

#ifndef AirspeedTape_hxx
#define AirspeedTape_hxx

#include <GaugeComponent.hxx>
#include "AirspeedTapeData.hxx"

class AirspeedTape: public hmi::GaugeComponent
{
public:
  AirspeedTape();
  ~AirspeedTape();

public:
  void Init();
  void Render();

  float calc_p(float h);

public:
  AirspeedTapeData& GetData() {return data;}

private:
  AirspeedTapeData data;
};

#endif
