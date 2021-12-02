// SVGame Core.
#include "../../ServerGameLocal.h"
#include "../../Entities.h"
#include "../../Utilities.h"   // Util funcs.

// Shared Entities.
#include "Shared/Entities.h"

// ServerEntity Bases.
#include "EntityBase.h"
#include "PrivateEntityBase.h"

// Constructor.
PrivateEntityBase::PrivateEntityBase() :
    handleMemory{ .state = {.number = -1, },
    }, EntityBase(&handleMemory) {
}
