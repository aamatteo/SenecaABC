/* ------------------------------------------------------------------   */
/*      item            : MapData.cxx
        from template   : DataInterface.cxx
        template made by: Joost Ellerbroek
        category        : implementation file
        template changes: 081016 first version
        language        : C++
*/

#include "MapData.hxx"



MapData::MapData() :
    x(new DataHolder<float>(0.0)),
    y(new DataHolder<float>(0.0)),
    lat(new DataHolder<float>(0.0)),
    lon(new DataHolder<float>(0.0)),
    heading(new DataHolder<float>(0.0)),
    active_leg(new DataHolder<int>(0)),
    active_vnv_leg(new DataHolder<int>(0)),
    GPS_failure(new DataHolder<bool>(false)),
    fpl_page(new DataHolder<bool>(false)),
    Vtas(new DataHolder<float>(0.0)),
    dist_to_top(new DataHolder<float>(0.0)),
    time_to_bod(new DataHolder<float>(0.0)),
    curVerticalState(new DataHolder<int>(0.0)),
    msg(new DataHolder<int>(13)),
    range(new DataHolder<int>(5)),
    altitude(new DataHolder<float>(0.0)),
    fpa_req(new DataHolder<float>(0.0)),
    dt(new DataHolder<float>(1.0))
{
}


MapData::~MapData()
{
}
