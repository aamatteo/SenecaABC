/* ------------------------------------------------------------------   */
/*      item            : LeftBar.hxx
        made by         : jcomans
        from template   : hmigauge.hxx
        template made by: Joost Ellerbroek
        date            : 081013
        category        : header file
        description     :
        changes         : 081013 first version
        language        : C++
*/

#ifndef LeftBar_hxx
#define LeftBar_hxx

#include <GaugeComponent.hxx>
#include "LeftBarData.hxx"
#include "../../../MCP737/MCP737GUI/project_utilities.h"
class LeftBar: public hmi::GaugeComponent
{
public:
  LeftBar();
  ~LeftBar();

public:
  void Init();
  void Render();
  void reshape(int x, int y);


public:
  LeftBarData& GetData() {return data;}

private:
  ProjectUtilities utils;
  LeftBarData data;


};

#endif
