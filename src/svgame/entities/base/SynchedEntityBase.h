// License here.
#pragma once

#include "EntityBase.h"

//---------------------------------------------------------
// Used for when an entity has to be in sync with the server.
// Meaning the entire world will know about it. (Unless it has
// an entityflag of NO_CLIENT, but the server still will know
// about it.
//----------------------------------------------------------
class SynchedEntityBase abstract : public EntityBase {
protected:
    // pick a free slot
    SynchedEntityBase();
    // specify a specific slot to override
    SynchedEntityBase(ServerEntity* entity);

    static ServerEntity* QueryFreeServerEntity();
};