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

#ifndef MFDGauge_hxx
#define MFDGauge_hxx

#include <Gauge.hxx>
#include "MFDGaugeData.hxx"

class MFDGauge: public hmi::Gauge
{
public:
  MFDGauge(bool frame=false);
  ~MFDGauge();

  void Render();

public:
  MFDGaugeData& GetData() {return data;}

private:
  bool _frame;
  MFDGaugeData data;
};

#endif
