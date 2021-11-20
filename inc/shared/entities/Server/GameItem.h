// License here.
#pragma once

struct GameItem {
    char        *classname; // spawning name
    qboolean    (*pickup)(ServerEntity*ent, ServerEntity*other);
    void        (*use)(ServerEntity*ent, GameItem *item);
    void        (*drop)(ServerEntity*ent, GameItem *item);
    void        (*weaponthink)(ServerEntity*ent);
    char        *pickup_sound;
    char        *world_model;
    int         world_model_flags;
    char        *view_model;

    // client side info
    char        *icon;
    char        *pickup_name;   // for printing on pickup
    int         count_width;    // number of digits to display by icon

    int         quantity;       // for ammo how much, for weapons how much is used per shot
    char        *ammo;          // for weapons
    int         flags;          // IT_* flags

    int         weapmodel;      // weapon model index (for weapons)

    void        *info;
    int         tag;

    char        *precaches;     // string of all models, sounds, and images this item will use
};