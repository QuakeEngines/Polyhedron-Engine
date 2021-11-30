// License here.
#pragma once

// Maximumn serverEntity clusters.
static constexpr uint32_t MAX_ENT_CLUSTERS = 16;

// Using.
using EntityDictionary = std::map<std::string, std::string>;

// Include TypeInfo here.
#include "Shared/Entities/TypeInfo.h"

//---------------------------------------------------------
// Server ServerEntity Data.
//---------------------------------------------------------
struct ServerEntity {
protected:
    // Top entity, contains our dictionary too after all.
    DefineTopAbstractClass(ServerEntity);

public:
    // Current entity state. (Contains all that'd be networked.)
    EntityState  state;

    // Assigned client to control this entity(If any.)
    struct gclient_s    *client;

    // Is set to 'true' in case the entity is already taken and thus occupied
    // a slot in the ServerEntity array.
    qboolean    inUse;

    int32_t         linkCount;

    // FIXME: move these fields to a server private sv_entity_t
    list_t      area;           // Linked to a division node or leaf

    int32_t     numClusters;    // if -1, use headNode instead
    int32_t     clusterNumbers[MAX_ENT_CLUSTERS];
    int32_t     headNode;       // Unused if numClusters != -1
    int32_t     areaNumber, areaNumber2;

    //================================
    // Flags determining what the specific goal of this server entity is.
    int32_t     serverFlags;            // EntityServerFlags::NoClient, EntityServerFlags::DeadMonster, EntityServerFlags::Monster, etc
    
    // Size (boundingbox) related.
    vec3_t      mins, maxs;
    vec3_t      absoluteMin, absoluteMax, size;

    // Solids.
    uint32_t    solid;
    int32_t     solid32;

    // Mask to decide where to, and where not to clip against.
    int32_t     clipMask;

    // Entities can have owners, yes.
    ServerEntity    *owner;

    // Entity
    EntityDictionary entityDictionary;
};