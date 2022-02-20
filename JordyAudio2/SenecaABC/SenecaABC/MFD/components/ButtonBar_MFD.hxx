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

#ifndef ButtonBar_MFD_hxx
#define ButtonBar_MFD_hxx

#include <GaugeComponent.hxx>
#include "ButtonBarData_MFD.hxx"

class ButtonBar_MFD: public hmi::GaugeComponent
{
public:
  ButtonBar_MFD();
  ~ButtonBar_MFD();

public:
  void Init();
  void Render();

public:
  ButtonBarData_MFD& GetData() {return data;}

private:
  ButtonBarData_MFD data;
};

#endif
