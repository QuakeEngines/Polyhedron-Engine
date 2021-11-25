// SVGame Core.
#include "../../g_local.h"
#include "../../entities.h"

// Constructor(s)
EntityBase::EntityBase(ServerEntity* serverEntityHandle) {
    this->entityHandle = serverEntityHandle;
    this->entityHandle->inUse = true;
}
