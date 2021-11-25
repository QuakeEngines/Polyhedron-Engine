// SVGame Core.
#include "../../g_local.h"
#include "../../entities.h"

// Constructor(s)
EntityBase::EntityBase(ServerEntity* serverEntityHandle) {
    if (serverEntityHandle->inUse) {
        gi.Error("Attempted to allocate an entity into a non-free slot");
    }

    this->entityHandle = serverEntityHandle;
    this->entityHandle->inUse = true;
}

EntityBase::~EntityBase() {
    this->entityHandle->inUse = false;
}