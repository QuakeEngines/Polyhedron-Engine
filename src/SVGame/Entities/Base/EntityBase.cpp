// SVGame Core.
#include "../../ServerGameLocal.h"
#include "../../Entities.h"

// Constructor(s)
EntityBase::EntityBase(ServerEntity* serverEntityHandle) {
    if (!serverEntityHandle) {
        gi.Error("Invalid nullptr serverEntityHandle passed to EntityBase.\n");
    }
    if (serverEntityHandle->inUse) {
        gi.Error("Attempted to allocate an entity into a non-free slot.\n");
    }

    this->entityHandle = serverEntityHandle;
    this->entityHandle->inUse = true;
}

EntityBase::~EntityBase() {
    this->entityHandle->inUse = false;
}

