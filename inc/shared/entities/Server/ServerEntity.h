// License here.
#pragma once

// Shared.
#include "shared/shared.h"

// Other.
#include "shared/ServerGameImports.h"

#include "shared/list.h"
#include "sharedgame/pmove.h"
#include "sharedgame/protocol.h"

#include "ClientPersistentData.h"
#include "ClientRespawnData.h"
#include "ServerClient.h"
#include "GameItem.h"

//-------------------
// ServerEntity_s, the server side ServerEntity structure. If you know what an ServerEntity is,
// then you know what this is.
// 
// The actual ServerGameEntity class is a member. It is where the magic happens.
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


 protected:
    //---------------------------------
    // Private again.
    //---------------------------------
    // FIXME: move these fields to a server private sv_ServerEntity_t
    list_t area; // Linked to a division node or leaf

    // If numClusters is -1, use headNodew instead.
    int32_t numClusters;    // if -1, use headNode instead
    static constexpr uint32_t MAX_ENT_CLUSTERS = 8;
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

    //------------------------------------
    //
    //-------------------------------------
    float   freetime;           // sv.time when the object was freed
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
