// SVGame Core.
#include <svgame/g_local.h>
#include <shared/entities.h>

// Constructor(s)
EntityBase::EntityBase() {
    this->entityHandle = nullptr;
}
EntityBase::EntityBase(ServerEntity* serverEntityHandle) {
    this->entityHandle = serverEntityHandle;
    this->entityHandle->inUse = true;
}

// Destructor.
EntityBase::~EntityBase()
{
    entityHandle = nullptr;
    entityHandle->inUse = false;
}

// Sets a handle pointer to the given server entity, and automatically tells it
// that it is in use.
void EntityBase::SetHandle(ServerEntity *serverEntityHandle)
{
    if (entityHandle == nullptr) {
        gi.BPrintf(PRINT_WARNING, "EntityBase::SetHandle called with a 'nullptr' handle. %s\n", __FUNCTION__);
    }

    entityHandle = entityHandle;
    entityHandle->inUse = true;
}

// Unsets the handle if any, meaning it also sets the old handle back to inUse = false,
// and nullifies our pointer to it.
void EntityBase::UnsetHandle() {
    if (entityHandle->inUse)
        entityHandle->inUse = false;
    entityHandle = nullptr;
}
