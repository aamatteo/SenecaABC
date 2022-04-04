/* ------------------------------------------------------------------   */
/*      item            : InstructorParametersData.cxx
        from template   : DataInterface.cxx
        template made by: Joost Ellerbroek
        category        : implementation file
        template changes: 081016 first version
        language        : C++
*/

#include "InstructorParametersData.hxx"



InstructorParametersData::InstructorParametersData() :
    show_instructor(new DataHolder<bool>(false)),
    fuel_left(new DataHolder<float>(0.0)),
    fuel_right(new DataHolder<float>(0.0)),
    height(new DataHolder<float>(0.0)),
    min_height(new DataHolder<float>(0.0))
{
}


InstructorParametersData::~InstructorParametersData()
{
}
