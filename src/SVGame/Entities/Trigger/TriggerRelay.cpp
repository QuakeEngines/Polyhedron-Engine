/*
// LICENSE HERE.

// TriggerRelay.cpp
*/

#include "../../ServerGameLocal.h"
#include "../../Effects.h"
#include "../../Entities.h"
#include "../../Utilities.h"
#include "../../Physics/StepMove.h"
#include "../../BrushFunctions.h"

#include "../Base/SVGBaseEntity.h"
#include "../Base/SVGBaseTrigger.h"

#include "TriggerRelay.h"

//===============
// TriggerRelay::ctor
//===============
TriggerRelay::TriggerRelay( Entity* entity )
	: Base( entity ) {
}

//===============
// TriggerRelay::Spawn
//===============
void TriggerRelay::Spawn() {
	Base::Spawn();
	SetUseCallback( &TriggerRelay::RelayUse );
}

//===============
// TriggerRelay::RelayUse
//===============
void TriggerRelay::RelayUse( SVGBaseEntity* other, SVGBaseEntity* activator ) {
	UseTargets( activator );
}
