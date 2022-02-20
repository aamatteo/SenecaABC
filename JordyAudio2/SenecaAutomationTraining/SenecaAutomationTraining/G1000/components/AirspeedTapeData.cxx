/* ------------------------------------------------------------------   */
/*      item            : AirspeedTapeData.cxx
        from template   : DataInterface.cxx
        template made by: Joost Ellerbroek
        category        : implementation file
        template changes: 081016 first version
        language        : C++
*/

#include "AirspeedTapeData.hxx"



AirspeedTapeData::AirspeedTapeData() :
    Vias(new DataHolder<float>(0.0)),
    Vtas(new DataHolder<float>(0.0)),
    Vc_gamma_max(new DataHolder<float>(0.0)),
    speed_target(new DataHolder<float>(0.0)),
    Vmin(new DataHolder<float>(0.0)),
    Vmax(new DataHolder<float>(0.0)),
    curVerticalState(new DataHolder<int>(0.0)),
    vtasdot(new DataHolder<float>(0.0)),
    clogged_pt(new DataHolder<bool>(false)),
    clogged_sp(new DataHolder<bool>(false)),
    ADC_failure(new DataHolder<bool>(false)),
    altitude(new DataHolder<float>(0.0)),
    dt(new DataHolder<float>(0.01))
{
}


AirspeedTapeData::~AirspeedTapeData()
{
}
