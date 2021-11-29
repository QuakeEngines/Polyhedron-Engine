// License here.
#pragma once

#include "Shared/Messaging.h"

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

// ServerEntity->serverFlags
struct EntityServerFlags {
    static constexpr uint32_t NoClient = 0x00000001;    // Don't send entity to clients, even if it has effects
    static constexpr uint32_t DeadMonster = 0x00000002; // Treat as CONTENTS_DEADMONSTER for collision
    static constexpr uint32_t Monster = 0x00000004;     // Treat as CONTENTS_MONSTER for collision
    static constexpr uint32_t Remove = 0x00000008;      // Delete the entity next tick
};

// ServerEntity->solid values
struct Solid {
    static constexpr uint32_t Not       = 0;    // No interaction with other objects
    static constexpr uint32_t Trigger   = 1;    // Only touch when inside, after moving
    static constexpr uint32_t BoundingBox = 2;  // Touch on edge
    static constexpr uint32_t BSP       = 3;    // Bsp clip, touch on edge
};
