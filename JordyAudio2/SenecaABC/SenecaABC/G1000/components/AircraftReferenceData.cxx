/* ------------------------------------------------------------------   */
/*      item            : AircraftReferenceData.cxx
        from template   : DataInterface.cxx
        template made by: Joost Ellerbroek
        category        : implementation file
        template changes: 081016 first version
        language        : C++
*/

#include "AircraftReferenceData.hxx"



AircraftReferenceData::AircraftReferenceData() :
    pitch(new DataHolder<float>(0.0)),
    roll(new DataHolder<float>(0.0)),
    theta_ref(new DataHolder<float>(0.0)),
    phi_ref(new DataHolder<float>(0.0)),
    APstate(new DataHolder<int>(0))
{
}


AircraftReferenceData::~AircraftReferenceData()
{
}
