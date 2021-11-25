// SVGame Core.
#include <svgame/g_local.h>
#include <shared/entities.h>
#include <svgame/utils.h>   // Util funcs.

// Shared Entities.
#include "shared/entities.h"

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