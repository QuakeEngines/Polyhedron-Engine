// SVGame Core.
#include "../g_local.h"		// SVGame.
#include "../effects.h"		// Effects.
#include "../entities.h"    // Entities.
#include "../utils.h"		// Util funcs.

// Entity Bases.
#include "EntityBase.h"
#include "SynchedEntityBase.h"

// Constructor.
SynchedEntityBase::SynchedEntityBase(Entity* entityHandle) : EntityBase(entityHandle) {

}

SynchedEntityBase::~SynchedEntityBase()
{
    handle->inUse = false;
}
