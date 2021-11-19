/*
// LICENSE HERE.

//
// MiscExplosionBox.cpp
//
//
*/
#include "g_local.h"			// Include SVGame header.
#include "entities.h"			// Entities header.
#include "player/client.h"		// Include Player Client header.



//
// SVG_SpawnClassServerEntity
//
//
#include "entities/base/SVGBaseEntity.h"
#include "entities/base/SVGBaseTrigger.h"
#include "entities/base/SVGBaseMover.h"
#include "entities/base/PlayerClient.h"
#include "entities/info/InfoPlayerStart.h"
#include "entities/Worldspawn.h"

#include <ranges>

//-----------------
// ServerEntity Game Variables.
//
// TODO: Explain shit, lol.
//-----------------
// Actual Server ServerEntity array.
ServerEntity g_entities[MAX_EDICTS];

// BaseServerEntity array, matches similarly index wise.
SVGBaseEntity* g_baseEntities[MAX_EDICTS];

//
// This is the old method, or at least, where we started off with.
//
//auto FetchModernMethod(std::size_t start, std::size_t end) {
//    return BaseServerEntityRange(&g_baseEntities[start], &g_baseEntities[end]) |
//        std::views::filter([](SVGBaseEntity* ent) {
//            return ent != nullptr && ent->GetServerServerEntity() && ent->IsInUse();
//        }
//    );
//}
//
//auto FetchModernMethod2(std::size_t start, std::size_t end) {
//    //return std::span(&g_entities[start], &g_entities[end]) | std::views::filter([](auto& ent) { return ent.inUse; });
//    //std::span<ServerEntity, MAX_EDICTS>(g_entities).subspan(start, end)
//    return std::span(&g_entities[start], &g_entities[end]) | std::views::filter([](auto& ent) { return ent.inUse; });
//}
//===================================================================
//

//
// This is the new method, let's roll!
//

//
//===================================================================
//
// Testing...
#ifdef DEBUG_SHIT_FOR_ENTITIES_LULZ
#include "entities/info/InfoPlayerStart.h"
void DebugShitForEntitiesLulz() {
    gi.DPrintf("Entities - ===========================================\n");
    for (auto& ServerEntity : g_entities | ServerEntityFilters::InUse) {
        gi.DPrintf("%s\n", ServerEntity.className);
    }
    gi.DPrintf("BaseEntities - ===========================================\n");
    for (auto* baseServerEntity : g_baseEntities | BaseServerEntityFilters::IsValidPointer | BaseServerEntityFilters::HasServerServerEntity | BaseServerEntityFilters::InUse) {
        gi.DPrintf("%s\n", baseServerEntity->GetClassName());
    }

    gi.DPrintf("ServerEntity - info_player_start filter - ===========================================\n");
    // Hehe, only  fetch info_player_start
    for (auto& ServerEntity : GetServerEntityRange<0, MAX_EDICTS>()
        | ef::HasClassServerEntity
        | ef::InUse
        | ef::HasClassName("info_player_start")) {
        gi.DPrintf("Filtered out the ServerEntity #%i: %s\n", ServerEntity.state.number, ServerEntity.className);
    }

    gi.DPrintf("BaseServerEntity - info_player_start filter - ===========================================\n");
    // Hehe, only  fetch info_player_start
    for (auto* baseServerEntity : GetBaseServerEntityRange<0, MAX_EDICTS>()
        | bef::IsValidPointer
        | bef::HasServerServerEntity
        | bef::InUse
        | bef::IsClassOf<InfoPlayerStart>()) {
        gi.DPrintf("Filtered out the base ServerEntity #%i: %s\n", baseServerEntity->GetNumber(), baseServerEntity->GetClassName());
    }
}
#endif
//===============
// SVG_SpawnClassServerEntity
//
//=================
SVGBaseEntity* SVG_SpawnClassServerEntity(ServerEntity* ent, const std::string& className) {
    // Start with a nice nullptr.
    SVGBaseEntity* spawnServerEntity = nullptr;
    if ( nullptr == ent ) {
        return nullptr;
    }

    // Fetch ServerEntity number.
    int32_t ServerEntityNumber = ent->state.number;

    // New type info-based spawning system, to replace endless string comparisons
    // First find it by the map name
    TypeInfo* info = TypeInfo::GetInfoByMapName( className.c_str() );
    if ( nullptr == info ) { // Then try finding it by the C++ class name
        if ( nullptr == (info = TypeInfo::GetInfoByName( className.c_str() )) ) { 
            gi.DPrintf( "WARNING: unknown ServerEntity '%s'\n", className.c_str() );
            return nullptr; // Bail out, we didn't find one
        }
    }

    // Don't freak out if the ServerEntity cannot be allocated, but do warn us about it, it's good to know
    // ServerEntity classes with 'DefineDummyMapClass' won't be reported here
    if ( nullptr != info->AllocateInstance && info->IsMapSpawnable() ) {
        return (g_baseEntities[ServerEntityNumber] = info->AllocateInstance( ent ));
    } else {
        if ( info->IsAbstract() ) {
            gi.DPrintf( "WARNING: tried to allocate an abstract class '%s'\n", info->className );
        } else if ( !info->IsMapSpawnable() ) {
            gi.DPrintf( "WARNING: tried to allocate a code-only class '%s'\n", info->className );
        }
        return nullptr;
    }
}

//===============
// SVG_FreeClassServerEntity
// 
// Will remove the class ServerEntity, if it exists. For fully freeing an ServerEntity,
// look for SVG_FreeServerEntity instead. It automatically takes care of 
// classEntities too.
//=================
void SVG_FreeClassServerEntity(ServerEntity* ent) {
    // Special class ServerEntity handling IF it still has one.
    if (ent->classServerEntity) {
        // Remove the classServerEntity reference
        ent->classServerEntity->SetServerServerEntity(nullptr);
        ent->classServerEntity = nullptr;
    }

    // Fetch ServerEntity number.
    int32_t ServerEntityNumber = ent->state.number;

    // In case it exists in our base ServerEntitys, get rid of it, assign nullptr.
    if (g_baseEntities[ServerEntityNumber]) {
        delete g_baseEntities[ServerEntityNumber];
        g_baseEntities[ServerEntityNumber] = nullptr;
    }
}


//===============
// SVG_FreeServerEntity
// 
// Will remove the class ServerEntity, if it exists. Continues to then mark the
// ServerEntity as "freed". (inUse = false)
//=================
void SVG_FreeServerEntity(ServerEntity* ent)
{
    if (!ent)
        return;

    // Fetch ServerEntity number.
    int32_t ServerEntityNumber = ent->state.number;

    // First of all, unlink the ServerEntity from this world.
    gi.UnlinkServerEntity(ent);        // unlink from world

    // Prevent freeing "special edicts". Clients, and the dead "client body queue".
    if ((ent - g_entities) <= (maximumClients->value + BODY_QUEUE_SIZE)) {
        //      gi.DPrintf("tried to free special edict\n");
        return;
    }

    // Delete the actual ServerEntity pointer.
    SVG_FreeClassServerEntity(ent);

    // Clear the struct.
    *ent = {};
    
    // Reset classname to "freed" (It is, freed...)
    ent->className = "freed";

    // Store the freeTime, so we can prevent allocating a new ServerEntity with this ID too soon.
    // If we don't, we can expect client side LERP horror.
    ent->freeTime = level.time;

    // Last but not least, since it isn't in use anymore, let it be known.
    ent->inUse = false;

    // Reset serverFlags.
    ent->serverFlags = 0;
}

//===============
// SVG_PickTarget
// 
// Searches all active entities for the next one that holds
// the matching string at fieldofs (use the FOFS() macro) in the structure.
// 
// Searches beginning at the edict after from, or the beginning if NULL
// NULL will be returned if the end of the list is reached.
//
//===============
#define MAXCHOICES  8

ServerEntity* SVG_PickTarget(char* targetName)
{
    ServerEntity* ent = nullptr;
    int     num_choices = 0;
    ServerEntity* choice[MAXCHOICES];

    // Can't go on without a target name, can we?
    if (!targetName) {
        gi.DPrintf("SVG_PickTarget called with NULL targetName\n");
        return NULL;
    }

    // Try and find the given ServerEntity that matches this targetName.
    while (1) {
        ent = SVG_Find(ent, FOFS(targetName), targetName);
        // If we can't find it, break out of this loop.
        if (!ent)
            break;

        // If we did find one, add it to our list of targets to choose from.
        choice[num_choices++] = ent;

        // Break out in case of maximum choice limit.
        if (num_choices == MAXCHOICES)
            break;
    }

    // If there is nothing to choose from, it means we never found an ServerEntity matching this targetname.
    if (!num_choices) {
        gi.DPrintf("SVG_PickTarget: target %s not found\n", targetName);
        return NULL;
    }

    // Return a random target use % to prevent out of bounds.
    return choice[rand() % num_choices];
}

//===============
// SVG_Find
// 
// Searches all active entities for the next one that holds
// the matching string at fieldofs (use the FOFS() macro) in the structure.
//
// Searches beginning at the edict after from, or the beginning if NULL
// NULL will be returned if the end of the list is reached.
//===============
ServerEntity* SVG_Find(ServerEntity* from, int fieldofs, const char* match)
{
    char* s;

    if (!from)
        from = g_entities;
    else
        from++;

    for (; from < &g_entities[globals.numberOfEntities]; from++) {
        if (!from->inUse)
            continue;
        s = *(char**)((byte*)from + fieldofs);
        if (!s)
            continue;
        if (!Q_stricmp(s, match))
            return from;
    }

    return NULL;
}

//===============
// SVG_FindServerEntity
//
// Returns an ServerEntity that matches the given fieldKey and fieldValue in its 
// ServerEntity dictionary.
//===============
SVGBaseEntity* SVG_FindServerEntityByKeyValue(const std::string& fieldKey, const std::string& fieldValue, SVGBaseEntity* lastServerEntity) {
    ServerEntity* serverEnt = (lastServerEntity ? lastServerEntity->GetServerServerEntity() : nullptr);

    if (!lastServerEntity)
        serverEnt = g_entities;
    else
        serverEnt++;

    for (; serverEnt < &g_entities[globals.numberOfEntities]; serverEnt++) {
        // Fetch serverEntity its ClassServerEntity.
        SVGBaseEntity* classServerEntity = serverEnt->classServerEntity;

        // Ensure it has a class ServerEntity.
        if (!serverEnt->classServerEntity)
            continue;

        // Ensure it is in use.
        if (!classServerEntity->IsInUse())
            continue;

        // Start preparing for checking IF, its dictionary HAS fieldKey.
        auto dictionary = serverEnt->ServerEntityDictionary;

        if (dictionary.find(fieldKey) != dictionary.end()) {
            if (dictionary[fieldKey] == fieldValue) {
                return classServerEntity;
            }
        }
    }

    return nullptr;
}

//===============
// SVG_FindEntitiesWithinRadius
// 
// Returns entities that have origins within a spherical area
// 
// SVG_FindEntitiesWithinRadius (origin, radius)
//===============
BaseServerEntityVector SVG_FindEntitiesWithinRadius(vec3_t origin, float radius, uint32_t excludeSolidFlags)
{
    BaseServerEntityVector ServerEntityList;

    // Iterate over all entities, see who is nearby, and who is not.
    for (auto* radiusServerEntity : GetBaseServerEntityRange<0, MAX_EDICTS>()
        | bef::IsValidPointer
        | bef::HasServerServerEntity
        | bef::InUse
        | bef::WithinRadius(origin, radius, excludeSolidFlags)) {

        // Push radiusServerEntity result item to the list.
        ServerEntityList.push_back(radiusServerEntity);
    }

    // The list might be empty, ensure to check for that ;-)
    return ServerEntityList;
}

//===============
// SVG_InitServerEntity
// 
// Reinitializes a ServerEntity for use.
//===============
void SVG_InitServerEntity(ServerEntity* e)
{
    // From here on this ServerEntity is in use.
    e->inUse = true;

    // Set classname to "noclass", because it is.
    e->className = "noclass";

    // Reset gravity.
    //s->gravity = 1.0;

    // Last but not least, give it that ID number it so badly deserves for being initialized.
    e->state.number = e - g_entities;
}

//===============
// SVG_Spawn
// 
// Either finds a free server ServerEntity, or initializes a new one.
// Try to avoid reusing an ServerEntity that was recently freed, because it
// can cause the client to Think the ServerEntity morphed into something else
// instead of being removed and recreated, which can cause interpolated
// angles and bad trails.
//===============
ServerEntity* SVG_Spawn(void)
{
    ServerEntity *serverEntity = nullptr;
    int32_t i = 0;
    // Acquire a pointer to the ServerEntity we'll check for.
    serverEntity = &g_entities[game.maximumClients + 1];
    for (i = game.maximumClients + 1; i < globals.numberOfEntities; i++, serverEntity++) {
        // The first couple seconds of server time can involve a lot of
        // freeing and allocating, so relax the replacement policy
        if (!serverEntity->inUse && (serverEntity->freeTime < 2 || level.time - serverEntity->freeTime > 0.5)) {
            SVG_InitServerEntity(serverEntity);
            return serverEntity;
        }
    }


    if (i == game.maxEntities)
        gi.Error("ED_Alloc: no free edicts");

    // If we've gotten past the gi.Error, it means we can safely increase the number of entities.
    globals.numberOfEntities++;
    SVG_InitServerEntity(serverEntity);

    return serverEntity;
}

//=====================
// SVG_CreateTargetChangeLevel
//
// Returns the created target changelevel ServerEntity.
//=====================
ServerEntity* SVG_CreateTargetChangeLevel(char* map) {
    ServerEntity* ent;

    ent = SVG_Spawn();
    ent->className = (char*)"target_changelevel"; // C++20: Added a cast.
    Q_snprintf(level.nextMap, sizeof(level.nextMap), "%s", map);
    ent->map = level.nextMap;
    return ent;
}

//===============
// SVG_GetWorldServerServerEntity
// 
// Returns a pointer to the 'Worldspawn' ServerEntity.
//===============
ServerEntity* SVG_GetWorldServerServerEntity() {
    return &g_entities[0];
};

//===============
// SVG_GetWorldClassServerEntity
// 
// Returns a pointer to the 'Worldspawn' ClassServerEntity.
//===============
SVGBaseEntity* SVG_GetWorldClassServerEntity() {
    return g_baseEntities[0];
};