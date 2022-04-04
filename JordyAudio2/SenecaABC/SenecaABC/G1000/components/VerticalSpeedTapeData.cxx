/* ------------------------------------------------------------------   */
/*      item            : VerticalSpeedTapeData.cxx
        from template   : DataInterface.cxx
        template made by: Joost Ellerbroek
        category        : implementation file
        template changes: 081016 first version
        language        : C++
*/

#include "VerticalSpeedTapeData.hxx"



VerticalSpeedTapeData::VerticalSpeedTapeData() :
    hdot(new DataHolder<float>(0.0)),
    target_vs(new DataHolder<float>(0.0)),
    curVerticalState(new DataHolder<int>(0)),
    Vtas(new DataHolder<float>(0.0)),
    ADC_failure(new DataHolder<bool>(false)),
    clogged_sp(new DataHolder<bool>(false)),
    dt(new DataHolder<float>(0.01))
{
}


VerticalSpeedTapeData::~VerticalSpeedTapeData()
{
}
