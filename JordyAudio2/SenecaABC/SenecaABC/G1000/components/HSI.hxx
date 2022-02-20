/* ------------------------------------------------------------------   */
/*      item            : HSI.hxx
        made by         : jcomans
        from template   : hmigauge.hxx
        template made by: Joost Ellerbroek
        date            : 081013
        category        : header file
        description     : 
        changes         : 081013 first version
        language        : C++
*/

#ifndef HSI_hxx
#define HSI_hxx

#include <GaugeComponent.hxx>
#include "HSIData.hxx"

class HSI: public hmi::GaugeComponent
{
public:
  HSI();
  ~HSI();

public:
  void Init();
  void Render();

public:
  HSIData& GetData() {return data;}

private:
  HSIData data;

};

#endif
