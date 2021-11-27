// License here.
#pragma once

//-------------------------------------
// Shared by the client AND server. Contains all data which a client needs
// to interprete and render a view of the server's actual gameplay.
//-------------------------------------
#include "Shared/Entities/Base/ServerEntity.h"

//-------------------------------------
// EntityBase represents a game entity. 
// It contains all of the base logic and data to make an entity function
// as long as it has a proper backing object for its entity state.
// 
// Synced entities will use a ServerEntity slot as a backing entity, 
// allowing the server to sync the entity to clients.
// 
// Private entities will use their own internal entity state, so they aren't 
// visible to the server. 
//-------------------------------------
#include "Shared/Entities/Base/EntityBase.h"
