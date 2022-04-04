/* ------------------------------------------------------------------   */
/*      item            : HSIData.cxx
        from template   : DataInterface.cxx
        template made by: Joost Ellerbroek
        category        : implementation file
        template changes: 081016 first version
        language        : C++
*/

#include "HSIData.hxx"



HSIData::HSIData() :
    heading(new DataHolder<float>(0.0)),
    dme(new DataHolder<float>(0.0)),
    course(new DataHolder<float>(0.0)),
    deviation(new DataHolder<float>(0.0)),
    offset(new DataHolder<float>(0.0)),
    needle_deviation(new DataHolder<float>(0.0)),
    active_nav_source(new DataHolder<int>(0)),
    VOR_failure(new DataHolder<bool>(false)),
    HSI_failure(new DataHolder<bool>(false)),
    GMU_failure(new DataHolder<bool>(false)),
    AFCS_rol(new DataHolder<bool>(false)),
    vor_flag_state(new DataHolder<bool>(true))
{
}


HSIData::~HSIData()
{
}
