/* ------------------------------------------------------------------   */
/*      item            : HorizonFieldsData.cxx
        from template   : DataInterface.cxx
        template made by: Joost Ellerbroek
        category        : implementation file
        template changes: 081016 first version
        language        : C++
*/

#include "HorizonFieldsData.hxx"



HorizonFieldsData::HorizonFieldsData() :
    pitch(new DataHolder<float>(0.0)),
    roll(new DataHolder<float>(0.0))
{
}


HorizonFieldsData::~HorizonFieldsData()
{
}
