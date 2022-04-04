/** @file comm-objects.h

    This file lists all DUECA Communication Objects that this module
    depends on.

    These are:
    PrimaryControls
    CitationPilotInput
    CitationOutput
    SnapshotRequest
    VehicleCabPosition
    VehicleCabMotion
    Reposition
    Trim_inco
    PropSoundData
    ControlEvent
    EngineEvent
    MassEvent
    WindEvent
    AutopilotChannel
    AP2G1000Channel
    GFC700Event
    ManifoldChannel
    BaseObjectPosition
    BaseObjectMotion
    AudioObjectFixed
    CommEvent
*/
#include "../../Generic/comm-objects/PrimaryControls.hxx"
#include "../../CitationDemo/comm-objects/CitationPilotInput.hxx"
#include "../../CitationExample/comm-objects/CitationOutput.hxx"
#include "../../CitationExample/comm-objects/SnapshotRequest.hxx"
#include "../../Generic/comm-objects/VehicleCabPosition.hxx"
#include "../../SRSMotion/comm-objects/VehicleCabMotion.hxx"
#include "../../Asym1/comm-objects/Reposition.hxx"
#include "../../Asym1/comm-objects/Trim_inco.hxx"
#include "../../SenecaABC/comm-objects/PropSoundData.hxx"
#include "../../SenecaABC/comm-objects/ControlEvent.hxx"
#include "../../SenecaABC/comm-objects/EngineEvent.hxx"
#include "../../SenecaABC/comm-objects/MassEvent.hxx"
#include "../../SenecaABC/comm-objects/WindEvent.hxx"
#include "../../SenecaABC/comm-objects/AutopilotChannel.hxx"
#include "../../SenecaABC/comm-objects/AP2G1000Channel.hxx"
#include "../../SenecaABC/comm-objects/GFC700Event.hxx"
#include "../../SenecaABC/comm-objects/ManifoldChannel.hxx"
#include "../../WorldListener/comm-objects/BaseObjectPosition.hxx"
#include "../../WorldListener/comm-objects/BaseObjectMotion.hxx"
#include "../../WorldListener/comm-objects/AudioObjectFixed.hxx"
#include "../../SenecaABC/comm-objects/CommEvent.hxx"
