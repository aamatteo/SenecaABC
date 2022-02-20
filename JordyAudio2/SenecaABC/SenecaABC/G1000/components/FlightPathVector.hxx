/* ------------------------------------------------------------------   */
/*      item            : FlightPathVector.hxx
        made by         : jcomans
        from template   : hmigauge.hxx
        template made by: Joost Ellerbroek
        date            : 081013
        category        : header file
        description     : 
        changes         : 081013 first version
        language        : C++
*/

#ifndef FlightPathVector_hxx
#define FlightPathVector_hxx

#include <GaugeComponent.hxx>
#include "FlightPathVectorData.hxx"

class FlightPathVector: public hmi::GaugeComponent
{
public:
  FlightPathVector();
  ~FlightPathVector();

public:
  void Init();
  void Render();
  
public:
  FlightPathVectorData& GetData() {return data;}
  
private:
  FlightPathVectorData data;
};

#endif
