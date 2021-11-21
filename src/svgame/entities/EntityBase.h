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
    EntityBase();
    EntityBase(Entity* handle);

protected:
    // Handle to the server entity. (Assumed to be internal)
    Entity  *handle;

protected:
    void SetHandle(Entity* handle);
    virtual ~EntityBase();

public:
    //vec3 &GetOrigin() { return handle->origin; }
    //void SetOrigin(const vec3 &o) { handle->origin = o; }
};