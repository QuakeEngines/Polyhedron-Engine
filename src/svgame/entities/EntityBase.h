// License here.
#pragma once

//---------------------------------------------------------
// EntityBase - Points to a server entity handle.
// 
// This works as the following:
//  - SetHandle: Accepts a pointer to a server entity and 
//    sets it to inUse = true while also assigning its address
//    to its own handle pointer.
//  - When destructed, it automatically sets the handle's inUse
//    to false. This demands(and expects) that the handle lives
//    in a natural array.
//---------------------------------------------------------
class EntityBase
{
public:
    EntityBase(Entity* handle);
    ~EntityBase();

protected:
    // Handle to the server entity. (Assumed to be internal)
    Entity  *handle;

protected:
    // Sets the handle to a server entity so it can be safely made use of
    // in our server game module.
    void SetHandle(Entity* handleEntity);
    
    // Unsets the handle if any, meaning it also sets the old handle back to inUse = false,
    // and nullifies our pointer to it.
    void UnsetHandle();

    // Destructor.
    virtual ~EntityBase();

public:

    //vec3 &GetOrigin() { return handle->origin; }
    //void SetOrigin(const vec3 &o) { handle->origin = o; }
};