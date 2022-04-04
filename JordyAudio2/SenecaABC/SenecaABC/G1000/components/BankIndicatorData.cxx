/* ------------------------------------------------------------------   */
/*      item            : BankIndicatorData.cxx
        from template   : DataInterface.cxx
        template made by: Joost Ellerbroek
        category        : implementation file
        template changes: 081016 first version
        language        : C++
*/

#include "BankIndicatorData.hxx"



BankIndicatorData::BankIndicatorData() :
    roll(new DataHolder<float>(0.0)),
    Y_fycg(new DataHolder<float>(0.0))
{
}


BankIndicatorData::~BankIndicatorData()
{
}
