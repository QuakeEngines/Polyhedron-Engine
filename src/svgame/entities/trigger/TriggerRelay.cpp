/*
// LICENSE HERE.

// TriggerRelay.cpp
*/

#include "../../g_local.h"
#include "../../effects.h"
#include "../../entities.h"
#include "../../utils.h"
#include "../../physics/stepmove.h"
#include "../../brushfuncs.h"

#include "../base/ServerGameEntity.h"
#include "../base/SVGBaseTrigger.h"

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
void TriggerRelay::RelayUse( ServerGameEntity* other, ServerGameEntity* activator ) {
	UseTargets( activator );
}
