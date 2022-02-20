/* ------------------------------------------------------------------   */
/*      item            : MFDGaugeData.cxx
        from template   : DataInterface.cxx
        template made by: Joost Ellerbroek
        category        : implementation file
        template changes: 081016 first version
        language        : C++
*/

#include "MFDGaugeData.hxx"



MFDGaugeData::MFDGaugeData() :
    pitch(0.0),
    roll(0.0),
    heading(0.0),
    gamma(0.0),
    chi(0.0),
    altitude(0.0),
    hdot(0.0),
    Vias(0.0),
    Vtas(0.0),
    n1_left(0.0),
    n1_right(0.0),
    n2_left(0.0),
    n2_right(0.0),
    itt_left(0.0),
    itt_right(0.0),
    rpm_left(0.0),
    rpm_right(0.0),
    tl_left(0.0),
    tl_right(0.0),
    altitude_target(0.0),
    speed_target(0.0),
    Vmin(0.0),
    Vmax(0.0),
    performance_data_valid(false),
    Vc_gamma_max(0.0),
    gamma_max(0.0),
    gamma_max_full_thrust(0.0),
    dme(0.0),
    course(0.0),
    deviation(0.0),
    offset(0.0),
    trim_enabled(false),
    trim(0),
    ap_hdghold_mode(false),
    ap_althold_mode(false),
    ap_hdghold_transition(false),
    ap_althold_transition(false),
    crashed(false),
    fullscreen(false),
    show_instructor(false),
    height(0.0),
    min_height(0.0),
    curVerticalState(0),
    curLateralState(0),
    ap_armed(0),
    APstate(0),
    hdg_bug(0.0),
    target_vs(0.0),
    target_speed(0.0),
    alt_hold(0.0),
    ap_flash(false),
    pit_flash(false),
    rol_flash(false),
    theta_ref(0.0),
    phi_ref(0.0),
    x(0.0),
    y(0.0),
    active_nav_source(0),
    brg(0.0),
    dtk(0.0),
    active_leg(0),
    active_vnv_leg(0),
    dist_to_top(0.0),
    time_to_bod(0.0),
    GPS_failure(false),
    VOR_failure(false),
    map_left(0.0),
    map_right(0.0),
    dt(0.0),
    mouse_left(false),
    fpl_page(false),
    msg(13),
    range(5),
    fpa_req(0.0)
{
}


MFDGaugeData::~MFDGaugeData()
{
}
