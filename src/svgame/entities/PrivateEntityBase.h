// License here.
#pragma once

#include "EntityBase.h"

//---------------------------------------------------------
// Used for entities that have no need to take up an entity
// slot. For example, consider a path_corner or info_notnull
// they are required, and useful, but a waste of consuming
// an entity slot.
//----------------------------------------------------------
class PrivateEntityBase abstract : public EntityBase
{ 
public:
    // Constructor.
    PrivateEntityBase();

    // Deconstructor
    virtual ~PrivateEntityBase();

protected:
    // Internal memory 
    ServerEntity handleMemory;
};