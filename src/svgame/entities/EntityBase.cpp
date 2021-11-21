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

// Set handle.
void EntityBase::SetHandle(Entity *handle)
{
    this->handle = handle;
    this->handle->inUse = true;
}
