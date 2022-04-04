/* ------------------------------------------------------------------   */
/*      item            : RadioBlockData.cxx
        from template   : DataInterface.cxx
        template made by: Joost Ellerbroek
        category        : implementation file
        template changes: 081016 first version
        language        : C++
*/

#include "RadioBlockData.hxx"



RadioBlockData::RadioBlockData() :
    ap_hdghold_mode(new DataHolder<bool>(false)),
    ap_althold_mode(new DataHolder<bool>(false)),
    ap_hdghold_transition(new DataHolder<bool>(false)),
    ap_althold_transition(new DataHolder<bool>(false)),
    dme(new DataHolder<float>(0.0)),
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
    active_nav_source(new DataHolder<int>(0)),
    vnav_situation(new DataHolder<int>(0)),
    brg(new DataHolder<float>(0.0)),
    alts_flash_state(new DataHolder<int>(0)),
    alt_flash_state(new DataHolder<int>(0)),
    ADC_failure(new DataHolder<bool>(false)),
    VOR_failure(new DataHolder<bool>(false)),
    PFD_failure(new DataHolder<bool>(false)),
    active_leg(new DataHolder<int>(0))
{
}


RadioBlockData::~RadioBlockData()
{
}
