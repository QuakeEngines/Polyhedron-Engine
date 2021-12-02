/*
// LICENSE HERE.

// TriggerRelay.cpp
*/

#include "../../ServerGameLocal.h"
#include "../../Effects.h"
#include "../../Entities.h"
#include "../../Utilities.h"
#include "../../Physics/Stepmove.h"
#include "../../brushfuncs.h"

#include "../base/SynchedEntityBase.h"
#include "../base/BaseTrigger.h"

#include "TriggerRelay.h"

//===============
// TriggerRelay::ctor
//===============
TriggerRelay::TriggerRelay( ServerEntity* entity )
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
void TriggerRelay::RelayUse( SynchedEntityBase * other, SynchedEntityBase * activator ) {
	UseTargets( activator );
}
