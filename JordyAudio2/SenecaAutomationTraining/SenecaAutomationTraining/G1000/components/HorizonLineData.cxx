/* ------------------------------------------------------------------   */
/*      item            : HorizonLineData.cxx
        from template   : DataInterface.cxx
        template made by: Joost Ellerbroek
        category        : implementation file
        template changes: 081016 first version
        language        : C++
*/

#include "HorizonLineData.hxx"



HorizonLineData::HorizonLineData() :
    pitch(new DataHolder<float>(0.0)),
    roll(new DataHolder<float>(0.0))
{
}


HorizonLineData::~HorizonLineData()
{
}
