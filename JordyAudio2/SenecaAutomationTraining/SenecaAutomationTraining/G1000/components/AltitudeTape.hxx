/* ------------------------------------------------------------------   */
/*      item            : AltitudeTape.hxx
        made by         : jcomans
        from template   : hmigauge.hxx
        template made by: Joost Ellerbroek
        date            : 081013
        category        : header file
        description     : 
        changes         : 081013 first version
        language        : C++
*/

#ifndef AltitudeTape_hxx
#define AltitudeTape_hxx

#include <GaugeComponent.hxx>
#include "AltitudeTapeData.hxx"

class AltitudeTape: public hmi::GaugeComponent
{
public:
  AltitudeTape();
  ~AltitudeTape();

public:
  void Init();
  void Render();
  
public:
  AltitudeTapeData& GetData() {return data;}

private:
  AltitudeTapeData data;
};

#endif
