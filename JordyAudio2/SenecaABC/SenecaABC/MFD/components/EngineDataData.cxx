/* ------------------------------------------------------------------   */
/*      item            : EngineDataData.cxx
        from template   : DataInterface.cxx
        template made by: Joost Ellerbroek
        category        : implementation file
        template changes: 081016 first version
        language        : C++
*/

#include "EngineDataData.hxx"



EngineDataData::EngineDataData() :
    n1_left(new DataHolder<float>(0.0)),
    n1_right(new DataHolder<float>(0.0)),
    n2_left(new DataHolder<float>(0.0)),
    n2_right(new DataHolder<float>(0.0)),
    itt_left(new DataHolder<float>(0.0)),
    itt_right(new DataHolder<float>(0.0)),
    rpm_left(new DataHolder<float>(0.0)),
    rpm_right(new DataHolder<float>(0.0)),
    tl_left(new DataHolder<float>(0.0)),
    tl_right(new DataHolder<float>(0.0)),
    altitude(new DataHolder<float>(0.0)),
    map_left(new DataHolder<float>(0.0)),
    map_right(new DataHolder<float>(0.0)),
    dt(new DataHolder<float>(0.0)),
    lgear(new DataHolder<int>(0)),
    ngear(new DataHolder<int>(0)),
    rgear(new DataHolder<int>(0))
{
}


EngineDataData::~EngineDataData()
{
}
