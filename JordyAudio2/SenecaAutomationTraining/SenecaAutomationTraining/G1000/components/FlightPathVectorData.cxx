/* ------------------------------------------------------------------   */
/*      item            : FlightPathVectorData.cxx
        from template   : DataInterface.cxx
        template made by: Joost Ellerbroek
        category        : implementation file
        template changes: 081016 first version
        language        : C++
*/

#include "FlightPathVectorData.hxx"



FlightPathVectorData::FlightPathVectorData() :
    pitch(new DataHolder<float>(0.0)),
    roll(new DataHolder<float>(0.0)),
    heading(new DataHolder<float>(0.0)),
    gamma(new DataHolder<float>(0.0)),
    chi(new DataHolder<float>(0.0))
{
}


FlightPathVectorData::~FlightPathVectorData()
{
}
