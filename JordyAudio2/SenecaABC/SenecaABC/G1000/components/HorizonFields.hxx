/* ------------------------------------------------------------------   */
/*      item            : HorizonFields.hxx
        made by         : jcomans
        from template   : hmigauge.hxx
        template made by: Joost Ellerbroek
        date            : 081013
        category        : header file
        description     : 
        changes         : 081013 first version
        language        : C++
*/

#ifndef HorizonFields_hxx
#define HorizonFields_hxx

#include <GaugeComponent.hxx>
#include "HorizonFieldsData.hxx"

class HorizonFields: public hmi::GaugeComponent
{
public:
  HorizonFields();
  ~HorizonFields();

public:
  void Init();
  void Render();
  
public:
  HorizonFieldsData& GetData() {return data;}

private:
  HorizonFieldsData data;

  GLuint _gl_display_list_index;
};

#endif
