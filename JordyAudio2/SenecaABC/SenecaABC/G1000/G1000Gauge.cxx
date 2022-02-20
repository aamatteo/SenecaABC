/* ------------------------------------------------------------------   */
/*      item            : G1000Gauge.cxx
        made by         : jcomans
        from template   : hmigauge.cxx
        template made by: Joost Ellerbroek
        date            : 081013
        category        : body file
        description     :
        changes         : 081013 first version
        language        : C++
*/

#include "G1000Gauge.hxx"
#include <HMICommon.hxx>

#include "../include/GLTools.hxx"
#include "components/Math.hxx"

#include "components/AltitudeTape.hxx"
#include "components/AircraftReference.hxx"
#include "components/AirspeedTape.hxx"
#include "components/BankIndicator.hxx"
#include "components/ButtonBar.hxx"
#include "components/ClimbPerformance.hxx"
#include "components/CompassRose.hxx"
#include "components/FlightPathVector.hxx"
#include "components/HSI.hxx"
#include "components/HorizonFields.hxx"
#include "components/HorizonLine.hxx"
#include "components/InstructorParameters.hxx"
#include "components/PitchLadder.hxx"
#include "components/RadioBlock.hxx"
#include "components/ThrottleCalibration.hxx"
#include "components/VerticalSpeedTape.hxx"
#include "components/LeftBar.hxx"

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
  const double throttle_calibration_x_position = 200.0;
  const double throttle_calibration_y_position = 100.0;

  const double instructor_x_position = 164.;
  const double instructor_y_position =  50.;

  const double width_left = 195;
  const double width_right = 193;
  const double height_top = 49;
  const double height_bottom = 95;
};

G1000Gauge::G1000Gauge(bool frame) :
  hmi::Gauge("G1000Gauge"),
  _frame(frame)
{
  SetDrawingPlane(drawing_plane_x_min-width_left, drawing_plane_x_max+width_left,
		  drawing_plane_y_min-height_bottom, drawing_plane_y_max+height_top );

  SetAspectRatio((drawing_plane_width+width_left+width_right)/(drawing_plane_height+height_top+height_bottom));

  ////////////////////////////////////////////////////////////
  // The Attitude indicator
  HorizonFields* horizon_fields = new HorizonFields;
  horizon_fields->SetDrawPosition(0.0, horizon_baseline_y);
  horizon_fields->SetScale(1.0,1.0);
  AddGaugeComponent(horizon_fields);

  make_link(horizon_fields->GetData().pitch , data.pitch);
  make_link(horizon_fields->GetData().roll  , data.roll);


  HorizonLine* horizon_line = new HorizonLine;
  horizon_line->SetDrawPosition(0.0, horizon_baseline_y);
  horizon_line->SetScale(1.0,1.0);
  AddGaugeComponent(horizon_line);

  make_link(horizon_line->GetData().pitch , data.pitch);
  make_link(horizon_line->GetData().roll  , data.roll);

  PitchLadder* pitch_ladder = new PitchLadder;
  pitch_ladder->SetDrawPosition(0.0, horizon_baseline_y);
  pitch_ladder->SetScale(1.0,1.0);
  AddGaugeComponent(pitch_ladder);

  make_link(pitch_ladder->GetData().pitch , data.pitch);
  make_link(pitch_ladder->GetData().roll  , data.roll);

  BankIndicator* bank_indicator = new BankIndicator;
  bank_indicator->SetDrawPosition(0.0, horizon_baseline_y);
  bank_indicator->SetScale(1.0,1.0);
  AddGaugeComponent(bank_indicator);

  make_link(bank_indicator->GetData().roll  , data.roll);
  make_link(bank_indicator->GetData().Y_fycg  , data.Y_fycg);

  AircraftReference* aircraft_reference = new AircraftReference;
  aircraft_reference->SetDrawPosition(0.0, horizon_baseline_y);
  aircraft_reference->SetScale(1.0,1.0);
  AddGaugeComponent(aircraft_reference);

  make_link(aircraft_reference->GetData().pitch , data.pitch);
  make_link(aircraft_reference->GetData().roll , data.roll);
  make_link(aircraft_reference->GetData().theta_ref , data.theta_ref);
  make_link(aircraft_reference->GetData().phi_ref , data.phi_ref);
  make_link(aircraft_reference->GetData().APstate , data.APstate);



  FlightPathVector* flight_path_vector = new FlightPathVector;
  flight_path_vector->SetDrawPosition(0.0, horizon_baseline_y);
  flight_path_vector->SetScale(1.0,1.0);
  AddGaugeComponent(flight_path_vector);

  make_link(flight_path_vector->GetData().pitch   , data.pitch);
  make_link(flight_path_vector->GetData().roll    , data.roll);
  make_link(flight_path_vector->GetData().heading , data.heading);
  make_link(flight_path_vector->GetData().gamma   , data.gamma);
  make_link(flight_path_vector->GetData().chi     , data.chi);

  ////////////////////////////////////////////////////////////
  // The Altitude tape block
  AltitudeTape* altitude_tape = new AltitudeTape;
  altitude_tape->SetDrawPosition( altitude_tape_box_x_position ,
				  horizon_baseline_y);
  altitude_tape->SetScale(1.0,1.0);
  AddGaugeComponent(altitude_tape);

  make_link(altitude_tape->GetData().altitude , data.altitude);
  make_link(altitude_tape->GetData().altitude_target , data.altitude_target);
  make_link(altitude_tape->GetData().altitude_target_vnav , data.altitude_target_vnav);
  make_link(altitude_tape->GetData().curVerticalState , data.curVerticalState);
  make_link(altitude_tape->GetData().nav_R , data.nav_R);
  make_link(altitude_tape->GetData().vnav_R , data.vnav_R);
  make_link(altitude_tape->GetData().hdot , data.hdot);
  make_link(altitude_tape->GetData().ADC_failure , data.ADC_failure);
  make_link(altitude_tape->GetData().clogged_sp , data.clogged_sp);

  ////////////////////////////////////////////////////////////
  // The vertical speed tape
  VerticalSpeedTape* vertical_speed_tape = new VerticalSpeedTape;
  vertical_speed_tape->SetDrawPosition( vertical_speed_box_x_position ,
  					horizon_baseline_y );
  vertical_speed_tape->SetScale(1.0,1.0);
  AddGaugeComponent(vertical_speed_tape);

  make_link(vertical_speed_tape->GetData().hdot , data.hdot );
  make_link(vertical_speed_tape->GetData().curVerticalState, data.curVerticalState);
  make_link(vertical_speed_tape->GetData().target_vs, data.target_vs);
  make_link(vertical_speed_tape->GetData().Vtas, data.Vtas);
  make_link(vertical_speed_tape->GetData().ADC_failure , data.ADC_failure);
  make_link(vertical_speed_tape->GetData().clogged_sp , data.clogged_sp);
  make_link(vertical_speed_tape->GetData().dt , data.dt);


  ////////////////////////////////////////////////////////////
  // The airspeed tape block
  AirspeedTape* airspeed_tape = new AirspeedTape;
  airspeed_tape->SetDrawPosition( airspeed_tape_box_x_position ,
  				  horizon_baseline_y);
  airspeed_tape->SetScale(1.0,1.0);
  AddGaugeComponent(airspeed_tape);

  make_link(airspeed_tape->GetData().Vias         , data.Vias );
  make_link(airspeed_tape->GetData().Vtas         , data.Vtas );
  make_link(airspeed_tape->GetData().Vc_gamma_max , data.Vc_gamma_max );
  make_link(airspeed_tape->GetData().speed_target , data.speed_target);
  make_link(airspeed_tape->GetData().Vmin         , data.Vmin );
  make_link(airspeed_tape->GetData().Vmax         , data.Vmax );
  make_link(airspeed_tape->GetData().curVerticalState, data.curVerticalState);
  make_link(airspeed_tape->GetData().vtasdot, data.vtasdot);
  make_link(airspeed_tape->GetData().clogged_sp, data.clogged_sp);
  make_link(airspeed_tape->GetData().clogged_pt, data.clogged_pt);
  make_link(airspeed_tape->GetData().ADC_failure, data.ADC_failure);
  make_link(airspeed_tape->GetData().altitude, data.altitude);
  make_link(airspeed_tape->GetData().dt, data.dt);

  ////////////////////////////////////////////////////////////
  // Buttonbar
  ButtonBar* button_bar = new ButtonBar;
  button_bar->SetDrawPosition( drawing_plane_x_min, 0.0 );
  button_bar->SetScale(1.0,1.0);
  AddGaugeComponent(button_bar);
  make_link(button_bar->GetData().dme_status, data.dme_status );
  make_link(button_bar->GetData().fp_name, data.fp_name );
  make_link(button_bar->GetData().x, data.y );
  make_link(button_bar->GetData().y, data.x );
  make_link(button_bar->GetData().altitude, data.altitude );
  make_link(button_bar->GetData().ADC_failure, data.ADC_failure );


  // The compass rose
  CompassRose* compass_rose = new CompassRose;
  compass_rose->SetDrawPosition( 0.0, compass_rose_y_position );
  compass_rose->SetScale(1.0,1.0);
  AddGaugeComponent( compass_rose );

  make_link(compass_rose->GetData().heading, data.heading);
  make_link(compass_rose->GetData().track, data.chi);
  make_link(compass_rose->GetData().hdg_bug, data.hdg_bug);
  make_link(compass_rose->GetData().course, data.trueCourse);
  make_link(compass_rose->GetData().active_nav_source, data.active_nav_source);
  make_link(compass_rose->GetData().turn_rate, data.turn_rate);
  make_link(compass_rose->GetData().GMU_failure, data.GMU_failure);

  ////////////////////////////////////////////////////////////
  // The HSI
  HSI* hsi = new HSI;
  hsi->SetDrawPosition( 0.0, compass_rose_y_position );
  hsi->SetScale(1.0,1.0);
  AddGaugeComponent( hsi );

  make_link(hsi->GetData().heading, data.heading);

  make_link(hsi->GetData().dme       , data.dme      );
  make_link(hsi->GetData().course    , data.course   );
  make_link(hsi->GetData().deviation , data.deviation);
  make_link(hsi->GetData().offset    , data.offset   );
  make_link(hsi->GetData().needle_deviation, data.needle_deviation   );
  make_link(hsi->GetData().active_nav_source, data.active_nav_source);
  make_link(hsi->GetData().VOR_failure, data.VOR_failure);
  make_link(hsi->GetData().HSI_failure, data.HSI_failure);
  make_link(hsi->GetData().GMU_failure, data.GMU_failure);
  make_link(hsi->GetData().AFCS_rol, data.AFCS_rol);
  make_link(hsi->GetData().vor_flag_state, data.vor_flag_state);
  make_link(hsi->GetData().fp_name, data.fp_name);
  ////////////////////////////////////////////////////////////
  // The engine data
  // EngineData* engine_data = new EngineData;
  // engine_data->SetDrawPosition( drawing_plane_x_min,
	// 			radio_block_y_position );
  // engine_data->SetScale(1.0,1.0);
  // AddGaugeComponent( engine_data );
  //
  // make_link(engine_data->GetData().n1_left   , data.n1_left   );
  // make_link(engine_data->GetData().n1_right  , data.n1_right  );
  // make_link(engine_data->GetData().n2_left   , data.n2_left   );
  // make_link(engine_data->GetData().n2_right  , data.n2_right  );
  // make_link(engine_data->GetData().itt_left  , data.itt_left  );
  // make_link(engine_data->GetData().itt_right , data.itt_right );
  // make_link(engine_data->GetData().rpm_left , data.rpm_left );
  // make_link(engine_data->GetData().rpm_right , data.rpm_right );
  // make_link(engine_data->GetData().tl_left , data.tl_left );
  // make_link(engine_data->GetData().tl_right , data.tl_right );
  // make_link(engine_data->GetData().altitude , data.altitude );

  ////////////////////////////////////////////////////////////
  // The performance data
  ClimbPerformance* climb_performance = new ClimbPerformance;
  climb_performance->SetDrawPosition(0.0, horizon_baseline_y);
  climb_performance->SetScale(1.0,1.0);
  AddGaugeComponent(climb_performance);

  make_link(climb_performance->GetData().pitch                  , data.pitch                  );
  make_link(climb_performance->GetData().roll                   , data.roll                   );
  make_link(climb_performance->GetData().performance_data_valid , data.performance_data_valid );
  make_link(climb_performance->GetData().gamma_max              , data.gamma_max              );
  make_link(climb_performance->GetData().gamma_max_full_thrust  , data.gamma_max_full_thrust  );






  ////////////////////////////////////////////////////////////
  // The text and data fields

  RadioBlock* radio_block = new RadioBlock;
  radio_block->SetDrawPosition( drawing_plane_x_min,
   				radio_block_y_position);
  radio_block->SetScale(1.0,1.0);
  AddGaugeComponent(radio_block);

  make_link(radio_block->GetData().ap_hdghold_mode       , data.ap_hdghold_mode );
  make_link(radio_block->GetData().ap_althold_mode       , data.ap_althold_mode );
  make_link(radio_block->GetData().ap_hdghold_transition , data.ap_hdghold_transition );
  make_link(radio_block->GetData().ap_althold_transition , data.ap_althold_transition );

  make_link(radio_block->GetData().dme       , data.dme      );
  make_link(radio_block->GetData().course    , data.course   );
  make_link(radio_block->GetData().brg    , data.brg   );

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
  make_link(radio_block->GetData().active_nav_source, data.active_nav_source);
  make_link(radio_block->GetData().vnav_situation, data.vnav_situation);
  make_link(radio_block->GetData().alts_flash_state, data.alts_flash_state);
  make_link(radio_block->GetData().alt_flash_state, data.alt_flash_state);
  make_link(radio_block->GetData().ADC_failure, data.ADC_failure);
  make_link(radio_block->GetData().VOR_failure, data.VOR_failure);
  make_link(radio_block->GetData().PFD_failure, data.PFD_failure);
  make_link(radio_block->GetData().fp_name, data.fp_name);
  make_link(radio_block->GetData().active_leg, data.active_leg);



  ////////////////////////////////////////////////////////////
  // The throttle calibration box
  ThrottleCalibration* throttle_calibration = new ThrottleCalibration;

  throttle_calibration->SetDrawPosition( drawing_plane_x_min, drawing_plane_y_min );

  throttle_calibration->SetScale(1.0,1.0);
  AddGaugeComponent(throttle_calibration);

  make_link(throttle_calibration->GetData().enabled, data.trim_enabled);
  make_link(throttle_calibration->GetData().tl_left, data.tl_left);
  make_link(throttle_calibration->GetData().tl_right, data.tl_right);
  make_link(throttle_calibration->GetData().gear, data.gear);
  make_link(throttle_calibration->GetData().altitude, data.altitude);



  ////////////////////////////////////////////////////////////
  // The throttle calibration box
  InstructorParameters* instructor_parameters = new InstructorParameters;

  instructor_parameters->SetDrawPosition( instructor_x_position, instructor_y_position );

  AddGaugeComponent(instructor_parameters);

  make_link(instructor_parameters->GetData().show_instructor , data.show_instructor );
  make_link(instructor_parameters->GetData().height          , data.height          );
  make_link(instructor_parameters->GetData().min_height      , data.min_height      );



  LeftBar* left_bar = new LeftBar;
  left_bar->SetDrawPosition( drawing_plane_x_min-width_left, 0.0-height_bottom );
  left_bar->SetScale(1.0,1.0);
  AddGaugeComponent(left_bar);
  make_link(left_bar->GetData().mouse_left , data.mouse_left );
  make_link(left_bar->GetData().mouse_x , data.mouse_x );
  make_link(left_bar->GetData().mouse_y , data.mouse_y );
  make_link(left_bar->GetData().GFC_msg, data.GFC_msg);
  make_link(left_bar->GetData().dme_animation, data.dme_animation);
}

G1000Gauge::~G1000Gauge()
{

}

void G1000Gauge::Render()
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
