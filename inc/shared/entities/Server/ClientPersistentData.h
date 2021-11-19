
#pragma once

//-------------------
// The ClientPersistentData struct manages data that has to stay persistent
// across level changes.
//-------------------
class ClientPersistentData {
    char userinfo[MAX_INFO_STRING];
    char netname[16];
    int32_t hand;

    qboolean isConnected;  // A loadgame will leave valid entities that
                           // just don't have a connection yet

                           // Values saved and restored from entities when changing levels
    int32_t health;
    int32_t maxHealth;
    int32_t savedFlags;

    int32_t selectedItem;
    int32_t inventory[MAX_ITEMS];

    // Ammo capacities
    int32_t maxBullets;
    int32_t maxShells;
    int32_t maxRockets;
    int32_t maxGrenades;
    int32_t maxCells;
    int32_t maxSlugs;

    gitem_t *activeWeapon;
    gitem_t *lastWeapon;

    int32_t powerCubes;    // Used for tracking the cubes in coop games
    int32_t score;         // For calculating total unit score in coop games

    qboolean isSpectator;          // client is a isSpectator
};