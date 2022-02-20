/* ------------------------------------------------------------------   */
/*      item            : RadioBlockData_MFD.cxx
        from template   : DataInterface.cxx
        template made by: Joost Ellerbroek
        category        : implementation file
        template changes: 081016 first version
        language        : C++
*/

#include "RadioBlockData_MFD.hxx"



RadioBlockData_MFD::RadioBlockData_MFD() :
    ap_hdghold_mode(new DataHolder<bool>(false)),
    ap_althold_mode(new DataHolder<bool>(false)),
    ap_hdghold_transition(new DataHolder<bool>(false)),
    ap_althold_transition(new DataHolder<bool>(false)),
    course(new DataHolder<float>(0.0)),
    curVerticalState(new DataHolder<int>(0)),
    curLateralState(new DataHolder<int>(0)),
    APstate(new DataHolder<int>(0)),
    altitude_target(new DataHolder<float>(0.0)),
    target_vs(new DataHolder<float>(0.0)),
    hdg_bug(new DataHolder<float>(0.0)),
    ap_armed(new DataHolder<int>(0)),
    target_speed(new DataHolder<float>(0.0)),
    alt_hold(new DataHolder<float>(0.0)),
    ap_flash(new DataHolder<bool>(false)),
    pit_flash(new DataHolder<bool>(false)),
    rol_flash(new DataHolder<bool>(false)),
    brg(new DataHolder<float>(0.0)),
    trk(new DataHolder<float>(0.0)),
    dtk(new DataHolder<float>(0.0)),
    dme(new DataHolder<float>(0.0)),
    Vtas(new DataHolder<float>(0.0)),
    x(new DataHolder<float>(0.0)),
    y(new DataHolder<float>(0.0)),
    active_nav_source(new DataHolder<int>(0)),
    VOR_failure(new DataHolder<bool>(false)),
    msg(new DataHolder<int>(13)),
    dt(new DataHolder<float>(1.0))
{
}


RadioBlockData_MFD::~RadioBlockData_MFD()
{
}
