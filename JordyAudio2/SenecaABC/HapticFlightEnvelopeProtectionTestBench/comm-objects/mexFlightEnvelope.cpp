/*==========================================================
 * mexFlightEnvelope.cpp - Matlab interface to the FlightEnvelope defined here
 *
 * The calling syntax is:
 *
 *		flight_envelope = mexFlightEnvelope( ... TO FILL IN )
 *
 * This is a MEX-file for MATLAB.
 *
 *========================================================*/

#include "mex.h"
#include "../../../../phd_git/99_external/02_matlab/01_cpp_class_interface/class_handle.hpp"
#include <cassert>
#include <algorithm>
#include "../common/mexIncludes.h"
#include "../common/Atmosphere.hxx"
#include "FlightEnvelope.hxx"

FlightEnvelope::LoadFactorSign numberToLoadFactorSign( int p_number )
{
    // enum LoadFactorSign
    // {
    //     POSITIVE = 0,
    //     NEGATIVE,
    //     MAX_SIGNS
    // };
    FlightEnvelope::LoadFactorSign answer = FlightEnvelope::MAX_SIGNS;

    switch ( p_number )
    {
        case 1:
        {
            answer = FlightEnvelope::POSITIVE;
            break;
        }
        case -1:
        {
            answer = FlightEnvelope::NEGATIVE;
            break;
        }
        default:
        {
            mexErrMsgTxt( "numberToLoadFactorSign: Unexpected int to convert" );
            break;
        }
    }

    return answer;
}

FlightEnvelope::FlightEnvelopeLimits numberToFlightEnvelopeLimits( int p_number )
{
    // enum FlightEnvelopeLimits
    // {
    //     NOMINAL = 0,
    //     SAFE,
    //     LOW_VELOCITY_REGION,
    //     MAX_LIMITS
    // };
    FlightEnvelope::FlightEnvelopeLimits answer = FlightEnvelope::MAX_LIMITS;

    switch ( p_number )
    {
        case 0:
        {
            answer = FlightEnvelope::NOMINAL;
            break;
        }
        case 1:
        {
            answer = FlightEnvelope::SAFE;
            break;
        }
        case 2:
        {
            answer = FlightEnvelope::LOW_VELOCITY_REGION;
            break;
        }
        default:
        {
            mexErrMsgTxt( "numberToFlightEnvelopeLimits: Unexpected int to convert" );
            break;
        }
    }

    return answer;
}

// enum Violation
// {
//     POSITIVE_LOAD_FACTOR_ALPHA_STALL = 0,
//     POSITIVE_LOAD_FACTOR_OVERLOAD,
//     OVERSPEED,
//     NEGATIVE_LOAD_FACTOR_OVERLOAD,
//     NEGATIVE_LOAD_FACTOR_ALPHA_STALL,
//     LOW_VELOCITY_STALL,
//     LOW_VELOCITY_ABOVE_1G,
//     LOW_VELOCITY_MARGIN,
//     PROTECTED_REGION,
//     PROTECTED_REGION_ABOVE_1G,
//     PROTECTED_REGION_BELOW_1G,
//     MAX_VIOLATIONS
// };

// The gateway function
void mexFunction( int nlhs, mxArray *plhs[],
				  int nrhs, const mxArray *prhs[])
{
    // Somewhere we will need the flightenvelope
    FlightEnvelope *this_envelope;

    // Get the command string
    char cmd[64];
    if ( nrhs < 1 || mxGetString( prhs[ 0 ], cmd, sizeof( cmd ) ) )
    {
        mexErrMsgTxt( "First input should be a command string less than 64 characters long." );
    }

    // New
    if ( !strcmp( "new", cmd ) )
    {
        // Check parameters
        if ( nlhs > 1 )
        {
            mexErrMsgTxt( "New: no more then one output expected." );
        }

        // Make a handle to a new C++ instance
        this_envelope = new FlightEnvelope;
        plhs[ 0 ] = convertPtr2Mat< FlightEnvelope >( this_envelope );

        /* check for proper number of arguments */
        if ( nrhs != 2  )
        {
            mexErrMsgIdAndTxt( "mexFlightEnvelope:nrhs", "Two inputs required." );
        }
        // For easy writing
        const mxArray *this_data = prhs[ 1 ];

        /* make sure the first input argument is struct */
        if( !mxIsStruct( this_data ) )
        {
            mexErrMsgIdAndTxt( "mexFlightEnvelope:inputNotStruct", "First input must be a structure." );
        }

        /* get input arguments */
        int        nfields      = mxGetNumberOfFields( this_data );
        mwSize     NStructElems = mxGetNumberOfElements( this_data );
        assert ( NStructElems == 1 );
        int jstruct = 0;
        /* allocate memory  for storing classIDflags */
        mxClassID *classIDflags = (mxClassID*) mxCalloc( nfields, sizeof( mxClassID ) );


        /* check empty field, proper data type, and data type consistency;
         * and get classID for each field. */

        // For each field
        for( int ifield = 0; ifield < nfields; ifield++ )
        {
            mxArray* tmp = mxGetFieldByNumber( this_data, jstruct, ifield );
            if ( tmp == NULL )
            {
                mexPrintf( "%s%d\t%s%d\n", "FIELD: ", ifield+1, "STRUCT INDEX :", jstruct+1 );
                mexErrMsgIdAndTxt( "mexFlightEnvelope:fieldEmpty", "Above field is empty!");
            }
            if ( jstruct == 0 )
            {
                if( ( !mxIsChar( tmp ) && !mxIsNumeric( tmp ) ) || mxIsSparse( tmp ) )
                {
                    mexPrintf( "%s%d\t%s%d\n", "FIELD: ", ifield+1, "STRUCT INDEX :", jstruct+1 );
                    mexErrMsgIdAndTxt( "mexFlightEnvelope:invalidField", "Above field must have either string or numeric non-sparse data.");
                }
                classIDflags[ ifield ] = mxGetClassID( tmp );
            }
            else
            {
                if ( mxGetClassID( tmp ) != classIDflags[ ifield ] )
                {
                    mexPrintf( "%s%d\t%s%d\n", "FIELD: ", ifield+1, "STRUCT INDEX :", jstruct+1 );
                    mexErrMsgIdAndTxt( "mexFlightEnvelope:invalidFieldType", "Inconsistent data type in above field!");
                }
                else if ( !mxIsChar(tmp) && ( ( mxIsComplex(tmp) || mxGetNumberOfElements( tmp ) != 1 ) ) )
                {
                    mexPrintf( "%s%d\t%s%d\n", "FIELD: ", ifield+1, "STRUCT INDEX :", jstruct+1 );
                    mexErrMsgIdAndTxt( "mexFlightEnvelope:fieldNotRealScalar",  "Numeric data in above field must be scalar and noncomplex!");
                }
            }
        }

        readNumberInSruct( this_data, "m_max_load_factor",                 &this_envelope->m_max_load_factor );
        readNumberInSruct( this_data, "m_min_load_factor",                 &this_envelope->m_min_load_factor );
        readNumberInSruct( this_data, "m_maximum_operation_velocity",      &this_envelope->m_maximum_operation_velocity );
        readNumberInSruct( this_data, "m_max_angle_of_attack",             &this_envelope->m_max_angle_of_attack );
        readNumberInSruct( this_data, "m_min_angle_of_attack",             &this_envelope->m_min_angle_of_attack );
        readNumberInSruct( this_data, "m_lift_coefficient_slope_positive", &this_envelope->m_lift_coefficient_slope_positive );
        readNumberInSruct( this_data, "m_lift_coefficient_slope_negative", &this_envelope->m_lift_coefficient_slope_negative );
        readNumberInSruct( this_data, "m_lift_at_zero_aoa",                &this_envelope->m_lift_at_zero_aoa );
        readNumberInSruct( this_data, "m_altitude",                        &this_envelope->m_altitude );
        readNumberInSruct( this_data, "m_margin_angle_of_attack",          &this_envelope->m_margin_angle_of_attack );
        readNumberInSruct( this_data, "m_margin_low_velocity",             &this_envelope->m_margin_low_velocity );
        readNumberInSruct( this_data, "m_margin_high_velocity",            &this_envelope->m_margin_high_velocity );
        readNumberInSruct( this_data, "m_margin_load_factor",              &this_envelope->m_margin_load_factor );
        readNumberInSruct( this_data, "m_margin_low_velocity_region",      &this_envelope->m_margin_low_velocity_region );
        readNumberInSruct( this_data, "m_lifting_surface",                 &this_envelope->m_lifting_surface );
        readNumberInSruct( this_data, "m_mass",                            &this_envelope->m_mass );
    }
    else
    {
        // Check there is a second input, which should be the class instance handle
        if ( nrhs < 2 )
        {
            mexErrMsgTxt( "Second input should be a class instance handle." );
        }
        this_envelope = convertMat2Ptr < FlightEnvelope >( prhs[ 1 ] );
    }

    // Delete
    if ( !strcmp( "delete", cmd ) )
    {
        // Destroy the C++ object
        destroyObject < FlightEnvelope > ( this_envelope );

        // Warn if other commands were ignored
        if ( nlhs != 0 || nrhs != 2 )
        {
            mexWarnMsgTxt( "Delete: Unexpected arguments ignored." );
        }
    }
    // Just get the limits of the flight envelope, looking from your current point of view
    else if ( !strcmp( "curStateLimits", cmd ) )
    {
        // Check for proper number of arguments
        if ( nrhs < 4 )
        {
            mexErrMsgIdAndTxt( "mexFlightEnvelope:nrhs", "Four inputs required." );
        }
        if( nlhs > 1 )
        {
            mexErrMsgIdAndTxt( "mexFlightEnvelope:nlhs", "Only one output supported." );
        }

        /* make sure the other input arguments are numbers */
        if ( ( !( mxGetClassID( prhs[ 2 ] ) == mxDOUBLE_CLASS ) || mxIsComplex( prhs[ 2 ] ) ) )
        {
            mexErrMsgIdAndTxt( "mexFlightEnvelope:inputNotDouble", "Second input must be a double for velocity." );
        }
        if ( ( !( mxGetClassID( prhs[ 3 ] ) == mxDOUBLE_CLASS ) || mxIsComplex( prhs[ 3 ] ) ) )
        {
            mexErrMsgIdAndTxt( "mexFlightEnvelope:inputNotDouble", "Third input must be a double for load factor." );
        }

        // For easy writing
        double cur_velocity    = *mxGetPr( prhs[ 2 ] );
        double cur_load_factor = *mxGetPr( prhs[ 3 ] );

        // This will hold field names
        int number_of_fields = 16;
        const char *fieldnames[] = {
            "max_load_factor_nominal",            "max_load_factor_safe",
            "min_load_factor_nominal",            "min_load_factor_safe",
            "max_structural_load_factor_nominal", "max_structural_load_factor_safe",
            "min_structural_load_factor_nominal", "min_structural_load_factor_safe",
            "min_velocity_nominal",               "min_velocity_safe",
            "max_velocity_nominal",               "max_velocity_safe",
            "pos_manouvering_velocity_nominal",   "pos_manouvering_velocity_safe",
            "neg_manouvering_velocity_nominal",   "neg_manouvering_velocity_safe",
            };

        // Allocate memory for the structure
        mxArray *out_struct = mxCreateStructMatrix( 1, 1, number_of_fields, fieldnames );
        plhs[ 0 ] = out_struct;

        FlightEnvelope::LoadFactorSign       pos     = FlightEnvelope::POSITIVE;
        FlightEnvelope::LoadFactorSign       neg     = FlightEnvelope::NEGATIVE;
        FlightEnvelope::FlightEnvelopeLimits nominal = FlightEnvelope::NOMINAL;
        FlightEnvelope::FlightEnvelopeLimits safe    = FlightEnvelope::SAFE;

        // Get the numbers from the flight envelope and put them in the output
        setNumberInStruct( out_struct, "max_load_factor_nominal",            this_envelope->loadFactor( pos, cur_velocity, nominal ) );
        setNumberInStruct( out_struct, "max_load_factor_safe",               this_envelope->loadFactor( pos, cur_velocity, safe ) );
        setNumberInStruct( out_struct, "min_load_factor_nominal",            this_envelope->loadFactor( neg, cur_velocity, nominal ) );
        setNumberInStruct( out_struct, "min_load_factor_safe",               this_envelope->loadFactor( neg, cur_velocity, safe ) );
        setNumberInStruct( out_struct, "max_structural_load_factor_nominal", this_envelope->maxLoadFactor( pos, nominal ) );
        setNumberInStruct( out_struct, "max_structural_load_factor_safe",    this_envelope->maxLoadFactor( pos, safe ) );
        setNumberInStruct( out_struct, "min_structural_load_factor_nominal", this_envelope->maxLoadFactor( neg, nominal ) );
        setNumberInStruct( out_struct, "min_structural_load_factor_safe",    this_envelope->maxLoadFactor( neg, safe ) );
        setNumberInStruct( out_struct, "min_velocity_nominal",               this_envelope->velocity( cur_load_factor, nominal ) );
        setNumberInStruct( out_struct, "min_velocity_safe",                  this_envelope->velocity( cur_load_factor, safe ) );
        setNumberInStruct( out_struct, "max_velocity_nominal",               this_envelope->maxOperationalVelocity( nominal ) );
        setNumberInStruct( out_struct, "max_velocity_safe",                  this_envelope->maxOperationalVelocity( safe ) );
        setNumberInStruct( out_struct, "pos_manouvering_velocity_nominal",   this_envelope->manouveringVelocity( pos, nominal ) );
        setNumberInStruct( out_struct, "pos_manouvering_velocity_safe",      this_envelope->manouveringVelocity( pos, safe ) );
        setNumberInStruct( out_struct, "neg_manouvering_velocity_nominal",   this_envelope->manouveringVelocity( neg, nominal ) );
        setNumberInStruct( out_struct, "neg_manouvering_velocity_safe",      this_envelope->manouveringVelocity( neg, safe ) );
    }
    // Interface to the manouvering velocity
    else if ( !strcmp( "manouveringVelocity", cmd ) )
    {
        // Check for proper number of arguments
        if ( nrhs < 4 )
        {
            mexErrMsgIdAndTxt( "mexFlightEnvelope:nrhs", "Four inputs required." );
        }
        if( nlhs > 1 )
        {
            mexErrMsgIdAndTxt( "mexFlightEnvelope:nlhs", "Only one output supported." );
        }

        /* make sure the other input arguments are numbers */
        if ( ( !( mxGetClassID( prhs[ 2 ] ) == mxDOUBLE_CLASS ) || mxIsComplex( prhs[ 2 ] ) ) )
        {
            mexErrMsgIdAndTxt( "mexFlightEnvelope:inputNotInt", "Second input must be a int for sign." );
        }
        if ( ( !( mxGetClassID( prhs[ 3 ] ) == mxDOUBLE_CLASS ) || mxIsComplex( prhs[ 3 ] ) ) )
        {
            mexErrMsgIdAndTxt( "mexFlightEnvelope:inputNotInt", "Third input must be a int for condition." );
        }

        // For easy writing
        FlightEnvelope::LoadFactorSign        sign  = numberToLoadFactorSign(       *mxGetPr( prhs[ 2 ] ) );
        FlightEnvelope::FlightEnvelopeLimits  limit = numberToFlightEnvelopeLimits( *mxGetPr( prhs[ 3 ] ) );

        // Get the number
        double manouv_vel = this_envelope->manouveringVelocity( sign, limit );

        // And write to the output
        setOutputVector( &plhs[ 0 ], &manouv_vel );
    }
    // Interface to the velocity for a loadfactor
    else if ( !strcmp( "velocity", cmd ) )
    {
        // Check for proper number of arguments
        if ( nrhs < 4 )
        {
            mexErrMsgIdAndTxt( "mexFlightEnvelope:nrhs", "Four inputs required." );
        }
        if( nlhs > 1 )
        {
            mexErrMsgIdAndTxt( "mexFlightEnvelope:nlhs", "Only one output supported." );
        }

        /* make sure the other input arguments are numbers */
        if ( ( !( mxGetClassID( prhs[ 2 ] ) == mxDOUBLE_CLASS ) || mxIsComplex( prhs[ 2 ] ) ) )
        {
            mexErrMsgIdAndTxt( "mexFlightEnvelope:inputNotInt", "Second input must be a double for load factor." );
        }
        if ( ( !( mxGetClassID( prhs[ 3 ] ) == mxDOUBLE_CLASS ) || mxIsComplex( prhs[ 3 ] ) ) )
        {
            mexErrMsgIdAndTxt( "mexFlightEnvelope:inputNotInt", "Third input must be a int for limit." );
        }

        // For easy writing
        double                                load_factor = *mxGetPr( prhs[ 2 ] );
        FlightEnvelope::FlightEnvelopeLimits  limit       = numberToFlightEnvelopeLimits( *mxGetPr( prhs[ 3 ] ) );

        // Get the number
        double vel = this_envelope->velocity( load_factor, limit );

        // And write to the output
        setOutputVector( &plhs[ 0 ], &vel );
    }
    // Interface to the max velocity for a limit
    else if ( !strcmp( "maxOperationalVelocity", cmd ) )
    {
        // Check for proper number of arguments
        if ( nrhs < 3 )
        {
            mexErrMsgIdAndTxt( "mexFlightEnvelope:nrhs", "Three inputs required." );
        }
        if( nlhs > 1 )
        {
            mexErrMsgIdAndTxt( "mexFlightEnvelope:nlhs", "Only one output supported." );
        }

        /* make sure the other input arguments are numbers */
        if ( ( !( mxGetClassID( prhs[ 2 ] ) == mxDOUBLE_CLASS ) || mxIsComplex( prhs[ 2 ] ) ) )
        {
            mexErrMsgIdAndTxt( "mexFlightEnvelope:inputNotInt", "Second input must be a int for limit." );
        }

        // For easy writing
        FlightEnvelope::FlightEnvelopeLimits limit = numberToFlightEnvelopeLimits( *mxGetPr( prhs[ 2 ] ) );

        // Get the number
        double max_vel = this_envelope->maxOperationalVelocity( limit );

        // And write to the output
        setOutputVector( &plhs[ 0 ], &max_vel );
    }
    // Interface to the loadfactor for a velocity
    else if ( !strcmp( "loadFactor", cmd ) )
    {
        // Check for proper number of arguments
        if ( nrhs < 5 )
        {
            mexErrMsgIdAndTxt( "mexFlightEnvelope:nrhs", "Five inputs required." );
        }
        if( nlhs != 1 )
        {
            mexErrMsgIdAndTxt( "mexFlightEnvelope:nlhs", "Only one output supported." );
        }

        /* make sure the other input arguments are numbers */
        if ( ( !( mxGetClassID( prhs[ 2 ] ) == mxDOUBLE_CLASS ) || mxIsComplex( prhs[ 2 ] ) ) )
        {
            mexErrMsgIdAndTxt( "mexFlightEnvelope:inputNotInt", "Second input must be a int for sign." );
        }
        if ( ( !( mxGetClassID( prhs[ 3 ] ) == mxDOUBLE_CLASS ) || mxIsComplex( prhs[ 3 ] ) ) )
        {
            mexErrMsgIdAndTxt( "mexFlightEnvelope:inputNotDouble", "Third input must be a double for velocity." );
        }
        if ( ( !( mxGetClassID( prhs[ 4 ] ) == mxDOUBLE_CLASS ) || mxIsComplex( prhs[ 4 ] ) ) )
        {
            mexErrMsgIdAndTxt( "mexFlightEnvelope:inputNotInt", "Fourth input must be a int for condition." );
        }

        // For easy writing
        FlightEnvelope::LoadFactorSign        sign     = numberToLoadFactorSign(       *mxGetPr( prhs[ 2 ] ) );
        double                                velocity = *mxGetPr( prhs[ 3 ] );
        FlightEnvelope::FlightEnvelopeLimits  limit    = numberToFlightEnvelopeLimits( *mxGetPr( prhs[ 4 ] ) );

        // Get the number
        double load_factor = this_envelope->loadFactor( sign, velocity, limit );

        // // And write to the output
        setOutputVector( &plhs[ 0 ], &load_factor );
    }
    // Interface to the maximum structural load factor
    else if ( !strcmp( "maxLoadFactor", cmd ) )
    {
        // Check for proper number of arguments
        if ( nrhs < 4 )
        {
            mexErrMsgIdAndTxt( "mexFlightEnvelope:nrhs", "Four inputs required." );
        }
        if( nlhs > 1 )
        {
            mexErrMsgIdAndTxt( "mexFlightEnvelope:nlhs", "Only one output supported." );
        }

        /* make sure the other input arguments are numbers */
        if ( ( !( mxGetClassID( prhs[ 2 ] ) == mxDOUBLE_CLASS ) || mxIsComplex( prhs[ 2 ] ) ) )
        {
            mexErrMsgIdAndTxt( "mexFlightEnvelope:inputNotInt", "Second input must be a int for sign." );
        }
        if ( ( !( mxGetClassID( prhs[ 3 ] ) == mxDOUBLE_CLASS ) || mxIsComplex( prhs[ 3 ] ) ) )
        {
            mexErrMsgIdAndTxt( "mexFlightEnvelope:inputNotInt", "Third input must be a int for condition." );
        }

        // For easy writing
        FlightEnvelope::LoadFactorSign        sign  = numberToLoadFactorSign(       *mxGetPr( prhs[ 2 ] ) );
        FlightEnvelope::FlightEnvelopeLimits  limit = numberToFlightEnvelopeLimits( *mxGetPr( prhs[ 3 ] ) );

        // Get the number
        double load_factor = this_envelope->maxLoadFactor( sign, limit );

        // And write to the output
        setOutputVector( &plhs[ 0 ], &load_factor );
    }
}