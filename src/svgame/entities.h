/*Og ypi 
// LICENSE HERE.

//
// entities.h
//
// All entity related functionality resides here. Need to spawn a specific entity?
// Determine the distance between the two, etc? 
//
// This is THE place.
//
// A GameEntity(GE) is always related to a ServerENtity (SE).
// The SE is literally stored on the server and acts as a POD(Plain Old Data)
// structure which is efficient for networking.
//
// The GE is where the actual game logic is implemented in, and it is what makes the
// gameplay tick. Need a new type of entity, a special door perhaps? GE.
//
// There should seldom if ever at all be a reason to touch an SE. After all, it is the
// server's own job to work with those, not the game!
//
// The "CE" is where the actual game logic implementation goes into. It is bound
// to an SE, which has to not be InUse. For if it is, it's slot has already been
// eaten up by an other "CE". 
//
//
//
*/
#pragma once

// Include this guy here, gotta do so to make it work.
#include "entities/base/ServerGameEntity.h"
#include <ranges>
//
// C++ using magic.
// 
using ServerGameEntitySpan = std::span<ServerGameEntity*>;

// Returns a span containing all ServerEntities in the range of:
// [start] to [start + count].
//
// This span can be quired on by several filters to ensure you only
// acquire a list of entities with specific demands.
template <std::size_t start, std::size_t count>
inline auto GetServerEntityRange() -> std::span<ServerGameEntity, count> {
    return std::span(serverGameEntities).subspan<start, count>();
}
inline ServerGameEntitySpan GetServerEntityRange(std::size_t start, std::size_t count) {
    return ServerGameEntitySpan(serverGameEntities).subspan(start, count);
}




//
// C++ using magic.
//
using GameEntitySpan = std::span<ServerGameEntity*>;
using GameEntityVector = std::vector<ServerGameEntity*>;

// Returns a span containing all ServerGameEntities in the range of:
// [start] to [start + count].
//
// This span can be quired on by several filters to ensure you only
// acquire a list of entities with specific demands.
template <std::size_t start, std::size_t count>
inline auto GetGameEntityRange() -> std::span<ServerGameEntity*, count> {
    return std::span(serverGameEntities).subspan<start, count>();
}
inline auto GetGameEntityRange(std::size_t start, std::size_t count) {
    return std::span(serverGameEntities).subspan(start, count);
}


//
// ServerEntity SEARCH utilities.
//
ServerEntity* SVG_PickTarget(char* targetName);
ServerEntity* SVG_Find(ServerEntity* from, int32_t fieldofs, const char* match); // C++20: Added const to char*

// Find entities within a given radius.
// Moved to gamemodes. This allows for them to customize what actually belongs in a certain radius.
// All that might sound silly, but the key here is customization.
//BaseEntityVector SVG_FindEntitiesWithinRadius(vec3_t org, float rad, uint32_t excludeSolidFlags = Solid::Not);
// Find entities based on their field(key), and field(value).
ServerGameEntity* SVG_FindEntityByKeyValue(const std::string& fieldKey, const std::string& fieldValue, ServerGameEntity* lastEntity = nullptr);


//
// Server ServerEntity handling.
//
void    SVG_InitEntity(ServerEntity* e);
void    SVG_FreeEntity(ServerEntity* e);

ServerEntity* SVG_GetWorldServerEntity();
ServerEntity* SVG_Spawn(void);

ServerEntity* SVG_CreateTargetChangeLevel(char* map);

// Admer: quick little template function to spawn entities, until we have this code in a local game class :)
template<typename entityClass>
inline entityClass* SVG_CreateClassEntity(ServerEntity* edict = nullptr, bool allocateNewEdict = true) {
    entityClass* entity = nullptr;
    // If a null entity was passed, create a new one
    if (edict == nullptr) {
        if (allocateNewEdict) {
            edict = SVG_Spawn();
        } else {
            gi.DPrintf("WARNING: tried to spawn a class entity when the edict is null\n");
            return nullptr;
        }
    }
    // Abstract classes will have AllocateInstance as nullptr, hence we gotta check for that
    if (entityClass::ClassInfo.AllocateInstance) {
        entity = static_cast<entityClass*>(entityClass::ClassInfo.AllocateInstance(edict)); // Entities that aren't in the type info system will error out here
        edict->className = entity->GetTypeInfo()->className;
        if (nullptr == serverGameEntities[edict->state.number]) {
            serverGameEntities[edict->state.number] = entity;
        } else {
            gi.DPrintf("ERROR: edict %i is already taken\n", edict->state.number);
        }
    }
    return entity;
}


//
// ClassEntity handling.
//
ServerGameEntity* SVG_GetWorldClassEntity();
ServerGameEntity* SVG_SpawnClassEntity(ServerEntity* ent, const std::string& className);
void SVG_FreeClassEntity(ServerEntity* ent);
