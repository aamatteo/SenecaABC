/* ------------------------------------------------------------------   */
/*      item            : RadioBlock.hxx
        made by         : jcomans
        from template   : hmigauge.hxx
        template made by: Joost Ellerbroek
        date            : 081013
        category        : header file
        description     :
        changes         : 081013 first version
        language        : C++
*/

#ifndef RadioBlock_MFD_hxx
#define RadioBlock_MFD_hxx

#include <GaugeComponent.hxx>
#include "RadioBlockData_MFD.hxx"

class LabelFlasher;

class RadioBlock_MFD: public hmi::GaugeComponent
{
public:
  RadioBlock_MFD();
  ~RadioBlock_MFD();


public:
  void Init();
  void Render();

public:
  RadioBlockData_MFD& GetData() {return data;}

private:
  void updateTransitions(bool current_altmode, bool current_hdgmode);

private:
  RadioBlockData_MFD data;
  LabelFlasher* _label_flasher;
};

#endif
