/* ------------------------------------------------------------------   */
/*      item            : AircraftReference.hxx
        made by         : jcomans
        from template   : hmigauge.hxx
        template made by: Joost Ellerbroek
        date            : 081013
        category        : header file
        description     :
        changes         : 081013 first version
        language        : C++
*/

#ifndef AircraftReference_hxx
#define AircraftReference_hxx

#include <GaugeComponent.hxx>
#include "AircraftReferenceData.hxx"
#include "GLTools.hxx"

class AircraftReference: public hmi::GaugeComponent
{
public:
  AircraftReference();
  ~AircraftReference();

public:
  void Init();
  void Render();

public:
  AircraftReferenceData& GetData() {return data;}

private:
  float drawFD(float pitch, float theta_ref, float distance_to_projection, GLTriangle fd_left_upper, GLTriangle fd_right_upper, GLTriangle fd_left_lower, GLTriangle fd_right_lower, float height, float old_height);

  AircraftReferenceData data;

  GLuint _gl_display_list_index;
};

#endif
