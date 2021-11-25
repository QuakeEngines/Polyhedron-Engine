// SVGame Core.
#include "../../g_local.h"		// SVGame.
#include "../../effects.h"		// Effects.
#include "../../entities.h"    // Entities.
#include "../../utils.h"		// Util funcs.

// Shared Entities.
#include "shared/entities.h"

// ServerEntity Bases.
#include "EntityBase.h"
#include "SynchedEntityBase.h"

// Constructor.
SynchedEntityBase::SynchedEntityBase() :
	EntityBase(QueryFreeServerEntity()) {
};

SynchedEntityBase::SynchedEntityBase(ServerEntity* entity) :
	EntityBase(entity) {
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
