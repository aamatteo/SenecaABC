/* ------------------------------------------------------------------   */
/*      item            : ClimbPerformanceData.cxx
        from template   : DataInterface.cxx
        template made by: Joost Ellerbroek
        category        : implementation file
        template changes: 081016 first version
        language        : C++
*/

#include "ClimbPerformanceData.hxx"



ClimbPerformanceData::ClimbPerformanceData() :
    pitch(new DataHolder<float>(0.0)),
    roll(new DataHolder<float>(0.0)),
    performance_data_valid(new DataHolder<bool>(false)),
    gamma_max(new DataHolder<float>(0.0)),
    gamma_max_full_thrust(new DataHolder<float>(0.0))
{
}


ClimbPerformanceData::~ClimbPerformanceData()
{
}
