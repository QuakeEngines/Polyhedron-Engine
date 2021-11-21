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
public:
    SynchedEntityBase();
    SynchedEntityBase(Entity* entityHandle);
    virtual ~SynchedEntityBase();

protected:
    static Entity* QueryFreeServerEntity()
    {
        //for (int32_t i = Cvar_Get("maxclients")->integer; i < MAX_EDICTS; i++) {
        //    Entity* entity = gi.GetEntityHandle(i);
        //    if (!entity->inuse)
        //        return entity;
        //}
        return nullptr;

        // TODO: Could also throw here and catch it later or whatever
        gi.Error("There were no more free entity slots available.\n");
    }
};