// License here.
#pragma once

//---------------------------------------------------------
// EntityBase - Points to a server entity handle.
//---------------------------------------------------------
class EntityBase
{
protected:
    // Handle to the server entity. (Assumed to be internal)
    ServerEntity  *entityHandle;
    
    EntityBase(ServerEntity* serverEntityHandle);

    // Destructor.
    virtual ~EntityBase();

public:

    //vec3_t &GetOrigin() { return entityHandle->state.origin; }
    //void SetOrigin(const vec3_t &o) { entityHandle->state.origin = o; }
};