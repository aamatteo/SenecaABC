/* ------------------------------------------------------------------   */
/*      item            : PitchLadderData.cxx
        from template   : DataInterface.cxx
        template made by: Joost Ellerbroek
        category        : implementation file
        template changes: 081016 first version
        language        : C++
*/

#include "PitchLadderData.hxx"



PitchLadderData::PitchLadderData() :
    pitch(new DataHolder<float>(0.0)),
    roll(new DataHolder<float>(0.0)),
    dummy(new DataHolder<float>(0.0))
{
}


PitchLadderData::~PitchLadderData()
{
}
