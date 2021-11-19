#pragma once

#include "shared/list.h"
#include "sharedgame/pmove.h"
#include "sharedgame/protocol.h"

#include "shared/entities/Server/ServerEntity.h"
#include "shared/entities/Server/ClientPersistentData.h"
#include "shared/entities/Server/ClientRespawnData.h"

class ServerClient {
public:
    // The client's current player state. (Communicated by server to clients.)
    PlayerState playerStates;

    // Current ping.
    int32_t ping;

    // Client index number.
    int32_t clientNumber;
};

//-------------------
// The gclient_s, Game Client structure.
// 
// Whenever PutClientInServer is called, this structure is cleared.
// The only thing that maintains its data is the persistent member.
// 
// This is to maintain several specific client data across maps.
//-------------------
class ClientPersistentData;
class ClientRespawnData;

class GameClient : public ServerClient {
public:
    // private to game
    ClientPersistentData persistent;
    ClientRespawnData respawn;

    qboolean showScores;         // set layout stat
    qboolean showInventory;      // set layout stat
    qboolean showHelpIcon;

    int32_t ammoIndex;

    int32_t buttons;
    int32_t oldButtons;
    int32_t latchedButtons;     // These are used for one time push events.

    qboolean weaponThunk;

    gitem_t *newWeapon;

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



//-------------------
// ServerEntity_s, the server side ServerEntity structure. If you know what an ServerEntity is,
// then you know what this is.
// 
// The actual SVGBaseEntity class is a member. It is where the magic happens.
// Entities can be linked to their "classname", this will in turn make sure that
// the proper inheritance ServerEntity is allocated.
//-------------------
using ServerEntityDictionary = std::map<std::string, std::string>;

class ServerEntity {
public:
    //---------------------------------
    // Public again.
    //---------------------------------
    // Actual ServerEntity state member. Contains all data that is actually networked.
    ServerEntityState  state;

    // NULL if not a player the server expects the first part of gclient_s to
    // be a PlayerState but the rest of it is opaque
    ServerClient *client;

    // An ServerEntity is in no use, in case it complies to the INUSE macro.
    qboolean inUse;

    // Link count for colliding.
    int32_t linkCount;

    //---------------------------------
    // Entity type and key/value related.
    //---------------------------------
    // className being used for determining wich in-game object to spawn this entity as.
    const char* className;

    ServerEntityDictionary serverEntityDictionary;

private:
    //---------------------------------
    // Private again.
    //---------------------------------
    // FIXME: move these fields to a server private sv_ServerEntity_t
    list_t area; // Linked to a division node or leaf

    // If numClusters is -1, use headNodew instead.
    int32_t numClusters;    // if -1, use headNode instead
    int32_t clusterNumbers[MAX_ENT_CLUSTERS];

    // Only use this instead of numClusters if numClusters == -1
    int32_t headNode;
    int32_t areaNumber;
    int32_t areaNumber2;

public:
    //---------------------------------
    // Public again.
    //---------------------------------
    int32_t serverFlags;// ServerEntityServerFlags::NoClient, ServerEntityServerFlags::DeadMonster, ServerEntityServerFlags::Monster, etc
    
    vec3_t mins, maxs;
    vec3_t absMin, absMax, size;

    uint32_t solid;
    int32_t solid32; // Can probably go.

    int32_t clipMask;

    ServerEntity* owner;
};

#if 0
struct ServerEntity {
private:
    ServerEntityState state;
    struct gclient_s* client;
    qboolean         inUse;
    int              linkCount;

public:

private:
    // FIXME: move these fields to a server private sv_ServerEntity_t
    // WID:Like this!
    list_t      area;               // linked to a division node or leaf

public:
    int         numClusters;       // if -1, use headNode instead
    int         clusterNumbers[MAX_ENT_CLUSTERS];
    int         headNode;           // unused if numClusters != -1
    int         areaNumber, areaNumber2;

    //================================

    int         serverFlags;            // ServerEntityServerFlags::NoClient, ServerEntityServerFlags::DeadMonster, ServerEntityServerFlags::Monster, etc
    vec3_t      mins, maxs;
    vec3_t      absMin, absMax, size;
    uint32_t    solid;
    int         clipMask;
    ServerEntity* owner;
};

#endif // 0
