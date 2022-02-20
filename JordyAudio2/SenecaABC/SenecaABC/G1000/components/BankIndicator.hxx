/* ------------------------------------------------------------------   */
/*      item            : BankIndicator.hxx
        made by         : jcomans
        from template   : hmigauge.hxx
        template made by: Joost Ellerbroek
        date            : 081013
        category        : header file
        description     : 
        changes         : 081013 first version
        language        : C++
*/

#ifndef BankIndicator_hxx
#define BankIndicator_hxx

#include <GaugeComponent.hxx>
#include "BankIndicatorData.hxx"

class BankIndicator: public hmi::GaugeComponent
{
public:
  BankIndicator();
  ~BankIndicator();

public:
  void Init();
  void Render();
  
public:
  BankIndicatorData& GetData() {return data;}

private:
  BankIndicatorData data;

  GLuint _gl_display_list_index;
};

#endif
