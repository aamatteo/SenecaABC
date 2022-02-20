/* ------------------------------------------------------------------   */
/*      item            : MFDGauge.cxx
        made by         : jkvanleeuwen
        from template   : hmigauge.cxx
        template made by: Joost Ellerbroek
        date            : 081013
        category        : body file
        description     :
        changes         : 081013 first version
        language        : C++
*/

#include "MFDGauge.hxx"
#include <HMICommon.hxx>

#include "../include/GLTools.hxx"
#include "../G1000/components/Math.hxx"

#include "../G1000/components/AltitudeTape.hxx"
#include "../G1000/components/AircraftReference.hxx"
#include "../G1000/components/AirspeedTape.hxx"
#include "../G1000/components/BankIndicator.hxx"
#include "../G1000/components/ClimbPerformance.hxx"
#include "../G1000/components/CompassRose.hxx"
#include "components/EngineData.hxx"
#include "components/ButtonBar_MFD.hxx"
#include "components/RadioBlock_MFD.hxx"
#include "components/Map.hxx"
#include "components/MFDBezel.hxx"
#include "../G1000/components/FlightPathVector.hxx"
#include "../G1000/components/HSI.hxx"
#include "../G1000/components/HorizonFields.hxx"
#include "../G1000/components/HorizonLine.hxx"
#include "../G1000/components/InstructorParameters.hxx"
#include "../G1000/components/PitchLadder.hxx"
#include "../G1000/components/RadioBlock.hxx"
#include "../G1000/components/ThrottleCalibration.hxx"
#include "../G1000/components/VerticalSpeedTape.hxx"

namespace {
  ////////////////////////////////////////////////////////////
  // Some variables that define the geometry of this gauge
  ////////////////////////////////////////////////////////////
  // The width of the actual G1000 is 1024 pixels. A 'natural'
  // zero position on the X-axis would be the center of the
  // aircraft symbol and HSI. This position is slightly left
  // of the geometric window center.
   const double drawing_plane_x_min = -460.;
   const double drawing_plane_x_max =  564.;
  // There is no real apparent symetry in the vertical direction
  // so we put the origin of the Y-axis at the bottom of the window
  // const double drawing_plane_y_min =  261.;
  // const double drawing_plane_y_max =  713.;
  const double drawing_plane_y_min =  0.;
  const double drawing_plane_y_max =  768.;
  // If we did our homework, the width and height should be 1024x768
  const double drawing_plane_width  = drawing_plane_x_max - drawing_plane_x_min;
  const double drawing_plane_height = drawing_plane_y_max - drawing_plane_y_min;

  ////////////////////////////////////////////////////////////
  // Variables that define component position
  ////////////////////////////////////////////////////////////
  // The vertical position of everything centered on the aircraft
  // reference symbol
  const double horizon_baseline_y = 483.0;
  // The left side of the altitude box
  const double altitude_tape_box_x_position = 245.0;
  // The left side of the vertical speed box
  const double vertical_speed_box_x_position = 350.0;
  // The left side of the airspeed box
  const double airspeed_tape_box_x_position = -310.0;
  // The bottom of the radio block
  // const double radio_block_y_position = drawing_plane_y_max - 55.0;
  const double radio_block_y_position = drawing_plane_y_max -55;
  // The middle of the compass rose
  const double compass_rose_y_position = 180.0;

  // The position of the throttle calibration box
  // const double throttle_calibration_x_position = 200.0;
  // const double throttle_calibration_y_position = 100.0;

  const double instructor_x_position = 164.;
  const double instructor_y_position =  50.;

  const double width_left = 195;
  const double width_right = 193;
  const double height_top = 49;
  const double height_bottom = 95;
};

MFDGauge::MFDGauge(bool frame) :
  hmi::Gauge("G1000Gauge"),
  _frame(frame)
{
  SetDrawingPlane(drawing_plane_x_min-width_left, drawing_plane_x_max+width_left,
		  drawing_plane_y_min-height_bottom, drawing_plane_y_max+height_top );

  SetAspectRatio((drawing_plane_width+width_left+width_right)/(drawing_plane_height+height_top+height_bottom));


  ////////////////////////////////////////////////////////////
  // Map

  Map* map = new Map;
  map->SetDrawPosition(drawing_plane_x_min+145, 27.0f);
  map->SetScale(1.0,1.0);
  AddGaugeComponent( map );

  make_link(map->GetData().x, data.x);
  make_link(map->GetData().y, data.y);
  make_link(map->GetData().heading, data.heading);
  make_link(map->GetData().active_leg, data.active_leg);
  make_link(map->GetData().active_vnv_leg, data.active_vnv_leg);
  make_link(map->GetData().GPS_failure, data.GPS_failure);
  make_link(map->GetData().fp_name, data.fp_name);
  make_link(map->GetData().fpl_page, data.fpl_page );
  make_link(map->GetData().Vtas, data.Vtas );
  make_link(map->GetData().dist_to_top, data.dist_to_top );
  make_link(map->GetData().time_to_bod, data.time_to_bod );
  make_link(map->GetData().curVerticalState, data.curVerticalState);
  make_link(map->GetData().msg, data.msg);
  make_link(map->GetData().range, data.range);
  make_link(map->GetData().altitude, data.altitude);
  make_link(map->GetData().fpa_req, data.fpa_req);
  make_link(map->GetData().dt, data.dt);

  // ////////////////////////////////////////////////////////////
  //The engine data
  EngineData* engine_data = new EngineData;
  engine_data->SetDrawPosition( drawing_plane_x_min,
				radio_block_y_position );
  engine_data->SetScale(1.0,1.0);
  AddGaugeComponent( engine_data );

  make_link(engine_data->GetData().n1_left, data.n1_left);
  make_link(engine_data->GetData().n1_right, data.n1_right);
  make_link(engine_data->GetData().n2_left, data.n2_left);
  make_link(engine_data->GetData().n2_right, data.n2_right);
  make_link(engine_data->GetData().itt_left, data.itt_left);
  make_link(engine_data->GetData().itt_right, data.itt_right);
  make_link(engine_data->GetData().rpm_left, data.rpm_left);
  make_link(engine_data->GetData().rpm_right, data.rpm_right);
  make_link(engine_data->GetData().tl_left, data.tl_left);
  make_link(engine_data->GetData().tl_right, data.tl_right);
  make_link(engine_data->GetData().altitude, data.altitude);
  make_link(engine_data->GetData().map_left, data.map_left);
  make_link(engine_data->GetData().map_right, data.map_right);
  make_link(engine_data->GetData().dt, data.dt);
  // ////////////////////////////////////////////////////////////

  // The text and data fields
  RadioBlock_MFD* radio_block = new RadioBlock_MFD;
  radio_block->SetDrawPosition( drawing_plane_x_min,
   				radio_block_y_position);
  radio_block->SetScale(1.0,1.0);
  AddGaugeComponent(radio_block);

  make_link(radio_block->GetData().ap_hdghold_mode       , data.ap_hdghold_mode );
  make_link(radio_block->GetData().ap_althold_mode       , data.ap_althold_mode );
  make_link(radio_block->GetData().ap_hdghold_transition , data.ap_hdghold_transition );
  make_link(radio_block->GetData().ap_althold_transition , data.ap_althold_transition );

  make_link(radio_block->GetData().dme    , data.dme      );
  make_link(radio_block->GetData().dtk    , data.dtk   );
  make_link(radio_block->GetData().brg    , data.brg   );
  make_link(radio_block->GetData().trk    , data.heading   );
  make_link(radio_block->GetData().Vtas    , data.Vtas   );
  make_link(radio_block->GetData().x    , data.x   );
  make_link(radio_block->GetData().y    , data.y   );

  make_link(radio_block->GetData().curVerticalState    , data.curVerticalState);
  make_link(radio_block->GetData().curLateralState    , data.curLateralState);
  make_link(radio_block->GetData().APstate    , data.APstate);
  make_link(radio_block->GetData().target_vs, data.target_vs);
  make_link(radio_block->GetData().altitude_target , data.altitude_target);
  make_link(radio_block->GetData().hdg_bug    , data.hdg_bug);
  make_link(radio_block->GetData().ap_armed    , data.ap_armed);
  make_link(radio_block->GetData().target_speed    , data.target_speed);
  make_link(radio_block->GetData().alt_hold    , data.alt_hold);
  make_link(radio_block->GetData().ap_flash    , data.ap_flash);
  make_link(radio_block->GetData().pit_flash    , data.pit_flash);
  make_link(radio_block->GetData().rol_flash    , data.rol_flash);
  make_link(radio_block->GetData().VOR_failure    , data.VOR_failure);
  make_link(radio_block->GetData().fp_name, data.fp_name);
  make_link(radio_block->GetData().active_nav_source, data.active_nav_source);
  make_link(radio_block->GetData().fpl_page , data.fpl_page );
  make_link(radio_block->GetData().msg, data.msg);
  make_link(radio_block->GetData().dt, data.dt);



  //
  ButtonBar_MFD* button_bar = new ButtonBar_MFD;
  button_bar->SetDrawPosition( drawing_plane_x_min, 0.0 );
  button_bar->SetScale(1.0,1.0);
  AddGaugeComponent(button_bar);

  MFDBezel* mfd_bezel = new MFDBezel;
  mfd_bezel->SetDrawPosition( drawing_plane_x_min-width_left, 0.0-height_bottom );
  mfd_bezel->SetScale(1.0,1.0);
  AddGaugeComponent(mfd_bezel);
  // make_link(mfd_bezel->GetData().mouse_left , data.mouse_left );
  // make_link(mfd_bezel->GetData().mouse_x , data.mouse_x );
  // make_link(mfd_bezel->GetData().mouse_y , data.mouse_y );

}

MFDGauge::~MFDGauge()
{

}

void MFDGauge::Render()
{
  if(!_frame)
    return;


  glLineWidth(1.0f);

  glColor3f(0.0f,0.0f,0.0f);

  GLRectangle(drawing_plane_y_min-height_bottom,
	      drawing_plane_y_max-1+height_top,
	      drawing_plane_x_min-width_left,
	      drawing_plane_x_max-1+width_right).drawOutline();

}
