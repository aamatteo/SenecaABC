/* ------------------------------------------------------------------   */
/*      item            : G1000Gauge.hxx
        made by         : jcomans
        from template   : hmigauge.hxx
        template made by: Joost Ellerbroek
        date            : 081013
        category        : header file
        description     : 
        changes         : 081013 first version
        language        : C++
*/

#ifndef G1000Gauge_hxx
#define G1000Gauge_hxx

#include <Gauge.hxx>
#include "G1000GaugeData.hxx"

class G1000Gauge: public hmi::Gauge
{
public:
  G1000Gauge(bool frame=false);
  ~G1000Gauge();

  void Render();

public:
  G1000GaugeData& GetData() {return data;}

private:
  bool _frame;
  G1000GaugeData data;
};

#endif
