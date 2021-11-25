// SVGame Core.
#include "../../g_local.h"
#include "../../entities.h"
#include "../../utils.h"   // Util funcs.

// Shared Entities.
#include "shared/entities.h"

// ServerEntity Bases.
#include "EntityBase.h"
#include "PrivateEntityBase.h"

// Constructor.
PrivateEntityBase::PrivateEntityBase() :
    handleMemory{ .state = { .number = -1 } },
    EntityBase(&handleMemory) {
}
