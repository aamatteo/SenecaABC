/* ------------------------------------------------------------------   */
/*      item            : ThrottleCalibrationData.cxx
        from template   : DataInterface.cxx
        template made by: Joost Ellerbroek
        category        : implementation file
        template changes: 081016 first version
        language        : C++
*/

#include "ThrottleCalibrationData.hxx"



ThrottleCalibrationData::ThrottleCalibrationData() :
    enabled(new DataHolder<bool>(false)),
    tl_left(new DataHolder<float>(0.0)),
    tl_right(new DataHolder<float>(0.0)),
    gear(new DataHolder<int>(0)),
    altitude(new DataHolder<float>(0.0))
{
}


ThrottleCalibrationData::~ThrottleCalibrationData()
{
}
