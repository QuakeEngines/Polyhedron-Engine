#pragma once

// Core shared.
#include "shared/shared.h"

// Shared common.
#include "shared/list.h"
#include "shared/messaging.h"

// Shared Game.
#include "sharedgame/pmove.h"
#include "sharedgame/protocol.h"

// Shared Entities.
#include "shared/entities/Server/ClientPersistentData.h"
#include "shared/entities/Server/ClientRespawnData.h"
#include "shared/entities/Server/ServerClient.h"
#include "shared/entities/Server/ServerEntity.h"
#include "shared/entities/Server/ServerGameEntity.h"
#include "shared/entities/Server/GameItem.h"


//-------------------
// The Game Client structure.
// 
// Whenever PutClientInServer is called, this structure is cleared.
// The only thing that maintains its data is the persistent member.
// 
// This is to maintain several specific client data across maps.
//-------------------
class GameClient : public ServerClient {
public:
    // These are private to the game, hence do not reside in ServerClient
    ClientPersistentData persistent;
    ClientRespawnData respawn;

    qboolean showScores;         // set layout stat
    qboolean showInventory;      // set inventory stat
    qboolean showHelpIcon;

    int32_t ammoIndex;

    int32_t buttons;
    int32_t oldButtons;
    int32_t latchedButtons;     // These are used for one time push events.

    qboolean weaponThunk;

    GameItem *newWeapon;

    // sum up damage over an entire frame, so
    // shotgun blasts give a single big kick
    struct {
        int32_t armor;       // damage absorbed by armor
        int32_t powerArmor;      // damage absorbed by power armor
        int32_t blood;       // damage taken out of health
        int32_t knockBack;   // impact damage
        vec3_t from;        // origin for vector calculation
    } damages;

    float killerYaw;         // when dead, look at killer

    int32_t weaponState;

    vec3_t kickAngles;    // weapon kicks
    vec3_t kickOrigin;

    // View damage kicks.
    struct {
        float roll;
        float pitch;
        float time;
    } viewDamage;

    float fallTime, fallValue;      // for view drop on fall
    float damageAlpha;
    float bonusAlpha;
    vec3_t damageBlend;
    vec3_t aimAngles;            // aiming direction
    float bobTime;            // so off-ground doesn't change it

                              // Old view angles and velocity.
    vec3_t oldViewAngles;
    vec3_t oldVelocity;

    float nextDrownTime;
    int32_t oldWaterLevel;

    // For weapon raising
    int32_t machinegunShots;

    // animation vars
    struct {
        int32_t     endFrame;
        int32_t     priorityAnimation;
        qboolean    isDucking;
        qboolean    isRunning;
    } animation;

    // Weapon Sound.
    int32_t weaponSound;

    // Pick up message time.
    float pickupMessageTime;

    // Flood protection struct.
    struct {
        float lockTill;     // locked from talking
        float when[10];     // when messages were said
        int32_t whenHead;     // head pointer for when said
    } flood;

    // Client can respawn when time > this
    float respawnTime;

    // The (client)player we are chasing
    ServerEntity *chaseTarget;

    // Do we need to update chase info?
    qboolean updateChase;
};