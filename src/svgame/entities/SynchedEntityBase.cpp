// SVGame Core.
#include "../g_local.h"		// SVGame.
#include "../effects.h"		// Effects.
#include "../entities.h"    // Entities.
#include "../utils.h"		// Util funcs.

// ServerEntity Bases.
#include "EntityBase.h"
#include "SynchedEntityBase.h"

// Constructor.
//SynchedEntityBase::SynchedEntityBase() {
//    // 
//}

SynchedEntityBase::SynchedEntityBase(ServerEntity* serverEntityHandle) : EntityBase(serverEntityHandle) {

}

SynchedEntityBase::~SynchedEntityBase()
{
    entityHandle->inUse = false;
}
