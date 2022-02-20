/* ------------------------------------------------------------------   */
/*      item            : MFDBezel.hxx
        made by         : jkvanleeuwen
        from template   : hmigauge.hxx
        template made by: Joost Ellerbroek
        date            : 081013
        category        : header file
        description     :
        changes         : 081013 first version
        language        : C++
*/

#ifndef MFDBezel_hxx
#define MFDBezel_hxx

#include <GaugeComponent.hxx>
#include "MFDBezelData.hxx"
//#include "../../../MCP737/MCP737GUI/project_utilities.h"
class MFDBezel: public hmi::GaugeComponent
{
public:
  MFDBezel();
  ~MFDBezel();

public:
  void Init();
  void Render();
  void reshape(int x, int y);


public:
  MFDBezelData& GetData() {return data;}

private:
  //ProjectUtilities utils;
  MFDBezelData data;


};

#endif
