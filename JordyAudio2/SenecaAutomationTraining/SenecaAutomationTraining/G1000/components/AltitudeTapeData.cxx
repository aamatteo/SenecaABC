/* ------------------------------------------------------------------   */
/*      item            : AltitudeTapeData.cxx
        from template   : DataInterface.cxx
        template made by: Joost Ellerbroek
        category        : implementation file
        template changes: 081016 first version
        language        : C++
*/

#include "AltitudeTapeData.hxx"



AltitudeTapeData::AltitudeTapeData() :
    altitude(new DataHolder<float>(0.0)),
    altitude_target(new DataHolder<float>(0.0)),
    curVerticalState(new DataHolder<int>(0)),
    altitude_target_vnav(new DataHolder<float>(0.0)),
    nav_R(new DataHolder<float>(0.0)),
    vnav_R(new DataHolder<float>(0.0)),
    hdot(new DataHolder<float>(0.0)),
    ADC_failure(new DataHolder<bool>(false)),
    clogged_sp(new DataHolder<bool>(false))
{
}


AltitudeTapeData::~AltitudeTapeData()
{
}
