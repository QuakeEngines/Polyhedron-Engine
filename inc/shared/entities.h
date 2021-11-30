// License here.
#pragma once

#include "Shared/Messages.h"

//-------------------------------------
// Shared by the client AND server. Contains all data which a client needs
// to interprete and render a view of the server's actual gameplay.
//-------------------------------------
#include "Shared/Entities/Base/ServerEntity.h"

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
