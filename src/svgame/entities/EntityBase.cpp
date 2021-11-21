// SVGame Core.
#include "../g_local.h"		// SVGame.
#include "../effects.h"		// Effects.
#include "../entities.h"    // Entities.
#include "../utils.h"		// Util funcs.

// Entity Bases.
#include "EntityBase.h"

// Constructor(s)
EntityBase::EntityBase() {
    this->handle = nullptr;
}
EntityBase::EntityBase(Entity* handle) {
    this->handle = handle;
    this->handle->inUse = true;
}

// Destructor.
EntityBase::~EntityBase()
{
    handle->inUse = false;
}

// Sets a handle pointer to the given server entity, and automatically tells it
// that it is in use.
void EntityBase::SetHandle(Entity *handle)
{
    if (handle == nullptr) {
        gi.BPrintf(PRINT_WARNING, "EntityBase::SetHandle called with a 'nullptr' handle. %s\n", __FUNCTION__);
    }
    this->handle = handle;
    this->handle->inUse = true;
}

// Unsets the handle if any, meaning it also sets the old handle back to inUse = false,
// and nullifies our pointer to it.
void EntityBase::UnsetHandle() {
    if (this->handle->inUse)
        this->handle->inUse = false;
    this->handle = nullptr;
}
