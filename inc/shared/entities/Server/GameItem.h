// License here.
#pragma once

// Shared.
#include "shared/shared.h"

// Predefine.
class ServerEntity;

//
// Game item structure -- Might as well become an entity,...
// 
struct GameItem {
    const char        *classname; // spawning name
    qboolean    (*pickup)(ServerEntity*ent, ServerEntity*other);
    void        (*use)(ServerEntity*ent, GameItem *item);
    void        (*drop)(ServerEntity*ent, GameItem *item);
    void        (*weaponthink)(ServerEntity*ent);
    const char        *pickup_sound;
    const char        *world_model;
    int         world_model_flags;
    const char        *view_model;

    // client side info
    const char        *icon;
    const char        *pickup_name;   // for printing on pickup
    int         count_width;    // number of digits to display by icon

    int         quantity;       // for ammo how much, for weapons how much is used per shot
    const char        *ammo;          // for weapons
    int         flags;          // IT_* flags

    int         weapmodel;      // weapon model index (for weapons)

    void        *info;
    int         tag;

    const char        *precaches;     // string of all models, sounds, and images this item will use
};