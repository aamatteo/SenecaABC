/* ------------------------------------------------------------------   */
/*      item            : CompassRoseData.cxx
        from template   : DataInterface.cxx
        template made by: Joost Ellerbroek
        category        : implementation file
        template changes: 081016 first version
        language        : C++
*/

#include "CompassRoseData.hxx"



CompassRoseData::CompassRoseData() :
    heading(new DataHolder<float>(0.0)),
    track(new DataHolder<float>(0.0)),
    hdg_bug(new DataHolder<float>(0.0)),
    course(new DataHolder<float>(0.0)),
    active_nav_source(new DataHolder<int>(0)),
    turn_rate(new DataHolder<float>(0.0)),
    GMU_failure(new DataHolder<bool>(false))
{
}


CompassRoseData::~CompassRoseData()
{
}
