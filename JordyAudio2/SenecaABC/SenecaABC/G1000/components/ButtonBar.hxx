/* ------------------------------------------------------------------   */
/*      item            : ButtonBar.hxx
        made by         : jcomans
        from template   : hmigauge.hxx
        template made by: Joost Ellerbroek
        date            : 081013
        category        : header file
        description     : 
        changes         : 081013 first version
        language        : C++
*/

#ifndef ButtonBar_hxx
#define ButtonBar_hxx

#include <GaugeComponent.hxx>
#include "ButtonBarData.hxx"

class ButtonBar: public hmi::GaugeComponent
{
public:
  ButtonBar();
  ~ButtonBar();

public:
  void Init();
  void Render();

public:
  ButtonBarData& GetData() {return data;}

private:
  ButtonBarData data;
};

#endif
