//// SVGame Core.
//#include "../../../g_local.h"	// SVGame.
//#include "../../../Effects.h"	// Effects.
//#include "../../../Entities.h"	// Entities.
//#include "../../../Utils.h"		// Util funcs.
//
//// Shared Entities.
//#include "Shared/Entities.h"

/*
// LICENSE HERE.

//
// SynchedEntityBase.h.cpp
//
//
*/
#include "../../g_local.h"		// SVGame.
#include "../../Effects.h"		// Effects.
#include "../../Entities.h"		// Entities.
#include "../../Utilities.h"		// Util funcs.

#include "SynchedEntityBase.h"
#include "BaseTrigger.h"
#include "../Trigger/TriggerDelayedUse.h"

//
// Constructor.
//
SynchedEntityBase::SynchedEntityBase() :
	EntityBase(SynchedEntityBase::QueryFreeServerEntity()) {

};

SynchedEntityBase::SynchedEntityBase(ServerEntity* serverEntity) :
	EntityBase(serverEntity) {
};

/*static*/ ServerEntity* SynchedEntityBase::QueryFreeServerEntity()
{
	ServerEntityID i;
	int32_t active = gi.GetNumberOfEntities();

	for (i = game.maximumClients; i < active; i++) {
		ServerEntity* handle = gi.GetEntityServerHandle(i);

		if (!handle->inUse) {
			break;
		}
	}

	if (i == MAX_EDICTS) {
		gi.Error("Reached maximum entity count\n");
	} else if (i == active) {
		gi.SetNumberOfEntities(active + 1);
	}

	ServerEntity* handle = gi.GetEntityServerHandle(i);

	// reset memory before sending it back
	*handle = {};

	handle->state.number = i;

	return handle;
}
