// SVGame Core.
#include "../g_local.h"		// SVGame.
#include "../effects.h"		// Effects.
#include "../entities.h"    // Entities.
#include "../utils.h"		// Util funcs.

// Shared Entities.
#include "shared/entities.h"

// ServerEntity Bases.
#include "shared/Entities/EntityBase.h"
#include "shared/Entities/SynchedEntityBase.h"
#include "shared/Entities/ServerEntity.h"

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
