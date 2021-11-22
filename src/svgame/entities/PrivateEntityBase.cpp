// SVGame Core.
#include "../g_local.h"		// SVGame.
#include "../effects.h"		// Effects.
#include "../entities.h"    // Entities.
#include "../utils.h"		// Util funcs.

// ServerEntity Bases.
#include "EntityBase.h"
#include "PrivateEntityBase.h"

// Constructor.
PrivateEntityBase::PrivateEntityBase() {
    SetHandle(&handleMemory);
}

// Destructor.
PrivateEntityBase::~PrivateEntityBase() {
    
}