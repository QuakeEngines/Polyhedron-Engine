// License here.
#pragma once

//---------------------------------------------------------
// Server ServerEntity Data.
//---------------------------------------------------------
class ServerEntity {
    // Current entity state. (Contains all that'd be networked.)
    ServerEntityState  state;
    struct gclient_s    *client;
    qboolean    inUse;
    int         linkCount;

    // FIXME: move these fields to a server private sv_entity_t
    list_t      area;           // Linked to a division node or leaf

    int         numClusters;    // if -1, use headNode instead
    int         clusterNumbers[MAX_ENT_CLUSTERS];
    int         headNode;       // Unused if numClusters != -1
    int         areaNumber, areaNumber2;

    //================================
    // Flags determining what the specific goal of this server entity is.
    int         serverFlags;            // EntityServerFlags::NoClient, EntityServerFlags::DeadMonster, EntityServerFlags::Monster, etc
    
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
};