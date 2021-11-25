// License here.
#pragma once

//-------------------
// ServerEntity, the server side entity structure. If you know what an entity is,
// then you know what this is.
// 
// The actual ServerGameEntity class stors a handle to a ServerEntity. It is where 
// the magic happens. Entities can be linked to their "classname", this will in turn 
// make sure that the proper inheritance entity is allocated.
//-------------------
// Using for readability, I love it.
using EntityDictionary = std::map<std::string, std::string>;

// As silly as it seems, we do this for readability and actually a mere pair of functions too.
using ServerEntityID = uint32_t;

// License here.
#include "Entities/EntityBase.h"
#include "Entities/PrivateEntityBase.h"
#include "Entities/SynchedEntityBase.h"
#include "Entities/ServerEntity.h"