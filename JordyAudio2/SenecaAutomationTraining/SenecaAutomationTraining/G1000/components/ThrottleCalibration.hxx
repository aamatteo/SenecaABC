/* ------------------------------------------------------------------   */
/*      item            : ThrottleCalibration.hxx
        made by         : jcomans
        from template   : hmigauge.hxx
        template made by: Joost Ellerbroek
        date            : 081013
        category        : header file
        description     : 
        changes         : 081013 first version
        language        : C++
*/

#ifndef ThrottleCalibration_hxx
#define ThrottleCalibration_hxx

#include <GaugeComponent.hxx>
#include "ThrottleCalibrationData.hxx"

class ThrottleCalibration: public hmi::GaugeComponent
{
public:
  ThrottleCalibration();
  ~ThrottleCalibration();

public:
  void Init();
  void Render();

public:
  ThrottleCalibrationData& GetData() {return data;}

private:
  ThrottleCalibrationData data;

};

#endif
