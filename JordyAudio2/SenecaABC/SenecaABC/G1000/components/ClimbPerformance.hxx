/* ------------------------------------------------------------------   */
/*      item            : ClimbPerformance.hxx
        made by         : jcomans
        from template   : hmigauge.hxx
        template made by: Joost Ellerbroek
        date            : 081013
        category        : header file
        description     : 
        changes         : 081013 first version
        language        : C++
*/

#ifndef ClimbPerformance_hxx
#define ClimbPerformance_hxx

#include <GaugeComponent.hxx>
#include "ClimbPerformanceData.hxx"

class ClimbPerformance: public hmi::GaugeComponent
{
public:
  ClimbPerformance();
  ~ClimbPerformance();

public:
  void Init();
  void Render();

public:
  ClimbPerformanceData& GetData() {return data;}

private:
  ClimbPerformanceData data;

};

#endif
