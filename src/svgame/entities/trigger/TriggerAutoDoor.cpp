/*
// LICENSE HERE.

// TriggerAutoDoor.cpp
*/

#include "../../g_local.h"
#include "../../effects.h"
#include "../../entities.h"
#include "../../utils.h"
#include "../../physics/stepmove.h"
#include "../../brushfuncs.h"

#include "../base/ServerGameEntity.h"
#include "../base/SVGBaseTrigger.h"
#include "../base/SVGBaseMover.h"

#include "../func/FuncDoor.h"

#include "TriggerAutoDoor.h"

//===============
// TriggerAutoDoor::ctor
//===============
TriggerAutoDoor::TriggerAutoDoor( ServerEntity* ServerEntity )
	: SVGBaseTrigger( ServerEntity ) {
	debounceTouchTime = 0.0f;
}

//===============
// TriggerAutoDoor::Spawn
//===============
void TriggerAutoDoor::Spawn() {
	Base::Spawn();

	SetSolid( Solid::Trigger );
	SetMoveType( MoveType::None );
	SetTouchCallback( &TriggerAutoDoor::AutoDoorTouch );
	LinkServerEntity();
}

//===============
// TriggerAutoDoor::AutoDoorTouch
//===============
void TriggerAutoDoor::AutoDoorTouch( ServerGameEntity* self, ServerGameEntity* other, cplane_t* plane, csurface_t* surf ) {
	bool isMonster = other->GetServerFlags() & ServerEntityServerFlags::Monster;
	// Alternatively, when we have a BaseMonster class:
	// isMonster = other->IsSubclassOf<BaseMonster>();

	if ( other->GetHealth() <= 0 ) {
		return; // If you're dead, you can't pass
	}
	// Only players and monsters are allowed
	if ( !(isMonster) && (!other->GetClient()) ) {
		return;
	}
	// Unless the no monster flag is set
	if ( (GetOwner()->GetSpawnFlags() & FuncDoor::SF_NoMonsters) && (isMonster) ) {
		return;
	}
	// If it's not the time to activate the door yet, then don't
	if ( level.time < debounceTouchTime ) {
		return;
	}
	debounceTouchTime = level.time + 1.0f;
	// Trigger our door
	GetOwner()->Use( other, other );
}

//===============
// TriggerAutoDoor::Create
//===============
TriggerAutoDoor* TriggerAutoDoor::Create( ServerGameEntity* ownerServerEntity, vec3_t ownerMaxs, vec3_t ownerMins ) {
	TriggerAutoDoor* autoDoor = SVG_CreateClassServerEntity<TriggerAutoDoor>();
	autoDoor->SetOwner( ownerServerEntity );
	autoDoor->SetMaxs( ownerMaxs );
	autoDoor->SetMins( ownerMins );
	autoDoor->Spawn();
	return autoDoor;
}
