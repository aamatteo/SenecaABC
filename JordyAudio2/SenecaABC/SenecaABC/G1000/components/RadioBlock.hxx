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

#ifndef RadioBlock_hxx
#define RadioBlock_hxx

#include <GaugeComponent.hxx>
#include "RadioBlockData.hxx"
#include <Eigen/Dense>

class LabelFlasher;

class RadioBlock: public hmi::GaugeComponent
{
public:
  RadioBlock();
  ~RadioBlock();


public:
  void Init();
  void Render();

public:
  RadioBlockData& GetData() {return data;}

private:
  void updateTransitions(bool current_altmode, bool current_hdgmode);

private:
  RadioBlockData data;
  LabelFlasher* _label_flasher;
};

#endif
