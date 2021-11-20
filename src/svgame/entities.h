/*
// LICENSE HERE.

//
// entities.h
//
// All ServerEntity related functionality resides here. Need to allocate a class?
// Find an ServerEntity? Anything else? You've hit the right spot.
//
// A "ClassServerEntity", or a CE, is always a member of a "ServerEntity", aka an SE.
//
// The actual game logic implementation thus goes in ClassEntities. An SE is
// merely a POD binding layer between SVGame and the server. (Important for
// networking.)
//
*/
#pragma once

// Include this guy here, gotta do so to make it work.
#include "shared/entities/Server/ServerEntity.h"
#include "shared/entities/Server/ServerGameEntity.h"

// Externs.
// Array containing all our ServerGameEntity pointer objects.
extern std::array<ServerGameEntity*, MAX_EDICTS> gameEntities;

//
// Filter function namespace that actually contains the ServerEntity filter implementations.
// 
namespace ServerEntityFilterFunctions {
    // Returns true in case the (server-)ServerEntity is in use.
    inline bool ServerEntityInUse(const ServerEntity& ent) { return ent.inUse; }
    // Returns true in case the (server-)ServerEntity has a client attached to it.
    inline bool ServerEntityHasClient(const ServerEntity& ent) { return static_cast<bool>(ent.client); }
    // Returns true in case the (server-)ServerEntity has a Class ServerEntity attached to it.
    inline bool ServerEntityHasClassServerEntity(const ServerEntity& ent) { return static_cast<bool>(ent.className); }

    // Returns true in case the (server-)ServerEntity has a client attached to it.
    inline bool BaseServerEntityHasClient(ServerGameEntity* ent) { return ent->GetClient(); }
    // Returns true in case the BaseServerEntity has a ground ServerEntity set to it.
    inline bool BaseServerEntityHasGroundServerEntity(ServerGameEntity* ent) { return ent->GetGroundServerEntity(); }
    // Returns true in case the BaseServerEntity is properly linked to a server ServerEntity.
    inline bool BaseServerEntityHasServerServerEntity(ServerGameEntity* ent) { return ent->GetServerServerEntity(); }
    // Returns true if the BaseServerEntity contains the sought for targetname.
    inline bool BaseServerEntityHasTargetName(ServerGameEntity* ent) { return ent->GetTargetName() != "" && !ent->GetTargetName().empty(); }
    // Returns true in case the BaseServerEntity has a client attached to it.
    inline bool BaseServerEntityInUse(ServerGameEntity* ent) { return ent->IsInUse(); }
    // Returns true if the BaseServerEntity is NOT a nullptr.
    inline bool BaseServerEntityIsValidPointer(ServerGameEntity* ent) { return ent != nullptr; }

    // Returns true in case the BaseServerEntity has the queried for classname.
    //inline bool BaseServerEntityHasClass(ServerGameEntity* ent, std::string classname) { return ent->GetClassName() == classname; }
};


//
// Actual filters to use with GetBaseServerEntityRange, ..., ... TODO: What other functions?
//
namespace ServerEntityFilters {
    using namespace std::views;

    inline auto InUse = std::views::filter( &ServerEntityFilterFunctions::ServerEntityInUse );
    inline auto HasClient = std::views::filter( &ServerEntityFilterFunctions::ServerEntityHasClient );
    inline auto HasClassServerEntity = std::views::filter( &ServerEntityFilterFunctions::ServerEntityHasClassServerEntity );
    // WID: TODO: This one actually has to move into ServerEntityFilterFunctions, and then
    // be referred to from here. However, I am unsure how to do that as of yet.
    inline auto HasClassName(const std::string& classname) {
        return std::ranges::views::filter(
            [classname /*need a copy!*/](ServerEntity &ent) {
                return classname == ent.className;
            }
        );
    }
    // WID: TODO: This one actually has to move into ServerEntityFilterFunctions, and then
    // be referred to from here. However, I am unsure how to do that as of yet.
    inline auto HasKeyValue(const std::string& fieldKey, const std::string &fieldValue) {
        return std::ranges::views::filter(
            [fieldKey, fieldValue /*need a copy!*/](ServerEntity& ent) {
                auto& dictionary = ent.serverEntityDictionary;

                if (dictionary.find(fieldKey) != dictionary.end()) {
                    if (dictionary[fieldKey] == fieldValue) {
                        return true;
                    }
                }

                return false;
            }
        );
    }

    // WID: TODO: This one actually has to move into ServerEntityFilterFunctions, and then
    // be referred to from here. However, I am unsure how to do that as of yet.
    template <typename ClassType>
    auto HasSubclassServerEntityType() {
        return std::ranges::views::filter(
            [](ServerEntity &ent) {
                if (ent.classServerEntity) {
                    return ent->classServerEntity->IsClass<ClassType>();
                } else {
                    return false;
                }
            }
        );
    }

    template <typename ClassType>
    auto HasSubclassServerEntityTypeOf() {
        return std::ranges::views::filter(
            [](ServerEntity& ent) {
                if (ent.classServerEntity) {
                    return ent.classServerEntity->IsSubclassOf<ClassType>();
                } else {
                    return false;
                }
            }
        );
    }
    
    inline auto Standard = (InUse);
};
namespace ef = ServerEntityFilters; // Shortcut, lesser typing.


//
// Actual filters to use with GetServerEntityRange, ..., ... TODO: What other functions?
//
namespace BaseServerEntityFilters {
    using namespace std::views;

    // BaseServerEntity Filters to employ by pipelining. Very nice and easy method of doing loops.
    inline auto IsValidPointer = std::views::filter( &ServerEntityFilterFunctions::BaseServerEntityIsValidPointer );
    inline auto HasServerServerEntity = std::views::filter( &ServerEntityFilterFunctions::BaseServerEntityHasServerServerEntity);
    inline auto HasGroundServerEntity = std::views::filter( &ServerEntityFilterFunctions::BaseServerEntityHasGroundServerEntity);
    inline auto InUse = std::views::filter( &ServerEntityFilterFunctions::BaseServerEntityInUse );
    inline auto HasClient = std::views::filter ( &ServerEntityFilterFunctions::BaseServerEntityHasClient );

    // WID: TODO: This one actually has to move into ServerEntityFilterFunctions, and then
    // be referred to from here. However, I am unsure how to do that as of yet.
    inline auto HasClassName(const std::string& classname) {
        return std::ranges::views::filter(
            [classname /*need a copy!*/](ServerGameEntity* ent) {
                return ent->GetClassName() == classname;
            }
        );
    }

    // WID: TODO: This one actually has to move into ServerEntityFilterFunctions, and then
    // be referred to from here. However, I am unsure how to do that as of yet.
    inline auto HasKeyValue(const std::string& fieldKey, const std::string& fieldValue) {
        return std::ranges::views::filter(
            [fieldKey, fieldValue /*need a copy!*/](ServerGameEntity *ent) {
                auto& dictionary = ent->GetServerEntityDictionary();

                if (dictionary.find(fieldKey) != dictionary.end()) {
                    if (dictionary[fieldKey] == fieldValue) {
                        return true;
                    }
                }

                return false;
            }
        );
    }

    // WID: TODO: This one actually has to move into ServerEntityFilterFunctions, and then
    // be referred to from here. However, I am unsure how to do that as of yet.
    template <typename ClassType>
    auto IsClassOf() {
        return std::ranges::views::filter(
            [](ServerGameEntity* ent) {
                return ent->IsClass<ClassType>();
            }
        );
    }

    template <typename ClassType>
    auto IsSubclassOf() {
        return std::ranges::views::filter(
            [](ServerGameEntity* ent) {
                return ent->IsSubclassOf<ClassType>();
            }
        );
    }

    // WID: TODO: This one actually has to move into ServerEntityFilterFunctions, and then
    // be referred to from here. However, I am unsure how to do that as of yet.
    inline auto WithinRadius(vec3_t origin, float radius, uint32_t excludeSolidFlags) {
        return std::ranges::views::filter(
            [origin, radius, excludeSolidFlags/*need a copy!*/](ServerGameEntity* ent) {
                // Find distances between ServerEntity origins.
                vec3_t ServerEntityOrigin = origin - (ent->GetOrigin() + vec3_scale(ent->GetMins() + ent->GetMaxs(), 0.5f));

                // Do they exceed our radius? Then we haven't find any.
                if (vec3_length(ServerEntityOrigin) > radius)
                    return false;

                // Cheers, we found our class ServerEntity.
                return true;
            }
        );
    }

    //
    // Summed up pipelines to simplify life with.
    //
    // A wrapper for the most likely 3 widely used, and if forgotten, error prone filters.
    inline auto Standard = (IsValidPointer | HasServerServerEntity | InUse);
};
namespace bef = BaseServerEntityFilters; // Shortcut, lesser typing.


//
// C++ using magic.
//
using ServerEntitySpan = std::span<ServerEntity>;
using ServerEntityVector = std::span<ServerEntity>;
using ServerGameEntitySpan = std::span<ServerGameEntity*>;
using ServerGameEntityVector = std::vector<ServerGameEntity*>;

// Returns a span containing all the entities in the range of [start] to [start + count].
//template <std::size_t start, std::size_t count>
//inline auto GetServerEntityRange() -> std::span<ServerEntity, count> {
//    return std::span(g_entities).subspan<start, count>();
//}
//inline ServerEntitySpan GetServerEntityRange(std::size_t start, std::size_t count) {
//    return ServerEntitySpan(g_entities).subspan(start, count);
//}

// Templated version of: Returns a span containing all game entities in the range of [start] to [start + count].
template <std::size_t start, std::size_t count>
inline auto GetServerGameEntityRange() -> std::span<ServerGameEntity*, count> {
    return std::span(gameEntities).subspan<start, count>();
}
// Non templated version of: Returns a span containing all game entities in the range of [start] to [start + count].
inline ServerGameEntitySpan GetServerGameEntityRange(std::size_t start, std::size_t count) {
    return ServerGameEntitySpan(gameEntities).subspan(start, count);
}


//
// ServerEntity SEARCH utilities.
//
ServerEntity* SVG_PickTarget(char* targetName);
ServerEntity* SVG_Find(ServerEntity* from, int32_t fieldofs, const char* match); // C++20: Added const to char*

// Find entities within a given radius.
// Moved to gamemodes. This allows for them to customize what actually belongs in a certain radius.
// All that might sound silly, but the key here is customization.
//BaseServerEntityVector SVG_FindEntitiesWithinRadius(vec3_t org, float rad, uint32_t excludeSolidFlags = Solid::Not);
// Find entities based on their field(key), and field(value).
ServerGameEntity* SVG_FindServerEntityByKeyValue(const std::string& fieldKey, const std::string& fieldValue, ServerGameEntity* lastServerEntity = nullptr);


//
// Server ServerEntity handling.
//
void    SVG_InitServerEntity(ServerEntity* e);
void    SVG_FreeServerEntity(ServerEntity* e);

ServerEntity* SVG_GetWorldServerServerEntity();
ServerEntity* SVG_Spawn(void);

ServerEntity* SVG_CreateTargetChangeLevel(char* map);

// Admer: quick little template function to spawn entities, until we have this code in a local game class :)
template<typename ServerEntityClass>
inline ServerEntityClass* SVG_CreateClassServerEntity(ServerEntity* edict = nullptr, bool allocateNewEdict = true) {
    ServerEntityClass* ServerEntity = nullptr;
    // If a null ServerEntity was passed, create a new one
    if (nullptr == edict) {
        if (allocateNewEdict) {
            edict = SVG_Spawn();
        } else {
            gi.DPrintf("WARNING: tried to spawn a class ServerEntity when the edict is null\n");
            return nullptr;
        }
    }
    // Abstract classes will have AllocateInstance as nullptr, hence we gotta check for that
    if (ServerEntityClass::ClassInfo.AllocateInstance) {
        ServerEntity = static_cast<ServerEntityClass*>(ServerEntityClass::ClassInfo.AllocateInstance(edict)); // Entities that aren't in the type info system will error out here
        edict->className = ServerEntity->GetTypeInfo()->className;
        if (nullptr == g_baseEntities[edict->state.number]) {
            g_baseEntities[edict->state.number] = ServerEntity;
        } else {
            gi.DPrintf("ERROR: edict %i is already taken\n", edict->state.number);
        }
    }
    return ServerEntity;
}


//
// ClassServerEntity handling.
//
ServerGameEntity* SVG_GetWorldClassServerEntity();
ServerGameEntity* SVG_SpawnServerGameEntity(ServerEntity* ent, const std::string& className);
void SVG_FreeClassServerEntity(ServerEntity* ent);

#endif // __SVGAME_ENTITIES_H__