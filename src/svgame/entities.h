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

//
// Filter function namespace that actually contains the entity filter implementations.
// 
namespace EntityFilterFunctions {
    // @returns true in case the (server-)ServerEntity is in use.
    inline bool EntityInUse (const ServerEntity& ent) { return ent.inUse; }
    // @returns true in case the (server-)ServerEntity has a client attached to it.
    inline bool EntityHasClient(ServerEntity& ent) { return static_cast<bool>(ent.client); }
    // @returns true in case the (server-)ServerEntity has a Class ServerEntity attached to it.
    inline bool EntityHasClassEntity(ServerEntity& ent) { return static_cast<bool>(ent.className.empty()); }

    // Returns true in case the (server-)ServerEntity has a client attached to it.
    inline bool BaseEntityHasClient(ServerGameEntity* ent) { return ent->GetClient(); }
    // Returns true in case the BaseEntity has a ground entity set to it.
    inline bool BaseEntityHasGroundEntity(ServerGameEntity* ent) { return ent->GetGroundEntity(); }
    // Returns true in case the BaseEntity is properly linked to a server entity.
    inline bool BaseEntityHasServerEntity(ServerGameEntity* ent) { return ent->GetServerEntity(); }
    // Returns true if the BaseEntity contains the sought for targetname.
    inline bool BaseEntityHasTargetName(ServerGameEntity* ent) { return ent->GetTargetName() != "" && !ent->GetTargetName().empty(); }
    // Returns true in case the BaseEntity has a client attached to it.
    inline bool BaseEntityInUse(ServerGameEntity* ent) { return ent->IsInUse(); }
    // Returns true if the BaseEntity is NOT a nullptr.
    inline bool BaseEntityIsValidPointer(ServerGameEntity* ent) { return ent != nullptr; }

    // Returns true in case the BaseEntity has the queried for classname.
    //inline bool BaseEntityHasClass(ServerGameEntity* ent, std::string classname) { return ent->GetClassName() == classname; }
};


//
// Actual filters to use with GetBaseEntityRange, ..., ... TODO: What other functions?
//
namespace EntityFilters {
    using namespace std::views;

    inline auto InUse = std::views::filter( &EntityFilterFunctions::EntityInUse );
    inline auto HasClient = std::views::filter( &EntityFilterFunctions::EntityHasClient );
    inline auto HasClassEntity = std::views::filter( &EntityFilterFunctions::EntityHasClassEntity );
    // WID: TODO: This one actually has to move into EntityFilterFunctions, and then
    // be referred to from here. However, I am unsure how to do that as of yet.
    inline auto HasClassName(const std::string& classname) {
        return std::ranges::views::filter(
            [classname /*need a copy!*/](ServerEntity &ent) {
                return classname == ent.className;
            }
        );
    }
    // WID: TODO: This one actually has to move into EntityFilterFunctions, and then
    // be referred to from here. However, I am unsure how to do that as of yet.
    inline auto HasKeyValue(const std::string& fieldKey, const std::string &fieldValue) {
        return std::ranges::views::filter(
            [fieldKey, fieldValue /*need a copy!*/](ServerEntity& ent) {
                auto& dictionary = ent.entityDictionary;

                if (dictionary.find(fieldKey) != dictionary.end()) {
                    if (dictionary[fieldKey] == fieldValue) {
                        return true;
                    }
                }

                return false;
            }
        );
    }

    inline auto Standard = (InUse);
};
namespace ef = EntityFilters; // Shortcut, lesser typing.


//
// Actual filters to use with GetEntityRange, ..., ... TODO: What other functions?
//
namespace BaseEntityFilters {
    using namespace std::views;

    // BaseEntity Filters to employ by pipelining. Very nice and easy method of doing loops.
    inline auto IsValidPointer = std::views::filter( &EntityFilterFunctions::BaseEntityIsValidPointer );
    inline auto HasServerEntity = std::views::filter( &EntityFilterFunctions::BaseEntityHasServerEntity);
    inline auto HasGroundEntity = std::views::filter( &EntityFilterFunctions::BaseEntityHasGroundEntity);
    inline auto InUse = std::views::filter( &EntityFilterFunctions::BaseEntityInUse );
    inline auto HasClient = std::views::filter ( &EntityFilterFunctions::BaseEntityHasClient );

    // WID: TODO: This one actually has to move into EntityFilterFunctions, and then
    // be referred to from here. However, I am unsure how to do that as of yet.
    inline auto HasClassName(const std::string& classname) {
        return std::ranges::views::filter(
            [classname /*need a copy!*/](ServerGameEntity* ent) {
                return ent->GetClassName() == classname;
            }
        );
    }

    // WID: TODO: This one actually has to move into EntityFilterFunctions, and then
    // be referred to from here. However, I am unsure how to do that as of yet.
    inline auto HasKeyValue(const std::string& fieldKey, const std::string& fieldValue) {
        return std::ranges::views::filter(
            [fieldKey, fieldValue /*need a copy!*/](ServerGameEntity *ent) {
                auto& dictionary = ent->GetEntityDictionary();

                if (dictionary.find(fieldKey) != dictionary.end()) {
                    if (dictionary[fieldKey] == fieldValue) {
                        return true;
                    }
                }

                return false;
            }
        );
    }

    // WID: TODO: This one actually has to move into EntityFilterFunctions, and then
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

    // WID: TODO: This one actually has to move into EntityFilterFunctions, and then
    // be referred to from here. However, I am unsure how to do that as of yet.
    inline auto WithinRadius(vec3_t origin, float radius, uint32_t excludeSolidFlags) {
        return std::ranges::views::filter(
            [origin, radius, excludeSolidFlags/*need a copy!*/](ServerGameEntity* ent) {
                // Find distances between entity origins.
                vec3_t entityOrigin = origin - (ent->GetOrigin() + vec3_scale(ent->GetMins() + ent->GetMaxs(), 0.5f));

                // Do they exceed our radius? Then we haven't find any.
                if (vec3_length(entityOrigin) > radius)
                    return false;

                // Cheers, we found our class entity.
                return true;
            }
        );
    }

    //
    // Summed up pipelines to simplify life with.
    //
    // A wrapper for the most likely 3 widely used, and if forgotten, error prone filters.
    inline auto Standard = (IsValidPointer | HasServerEntity | InUse);
};
namespace bef = BaseEntityFilters; // Shortcut, lesser typing.


//
// C++ using magic.
//
using EntitySpan = std::span<ServerEntity>;
using BaseEntitySpan = std::span<ServerGameEntity*>;

using BaseEntityVector = std::vector<ServerGameEntity*>;

// Returns a span containing all the entities in the range of [start] to [start + count].
template <std::size_t start, std::size_t count>
inline auto GetEntityRange() -> std::span<ServerEntity, count> {
    return std::span(gi.entityPool.entities).subspan<start, count>();
}

// Returns a span containing all base entities in the range of [start] to [start + count].
template <std::size_t start, std::size_t count>
inline auto GetBaseEntityRange() -> std::span<ServerGameEntity*, count> {
    return std::span(g_baseEntities).subspan<start, count>();
}

inline EntitySpan GetEntityRange(std::size_t start, std::size_t count) {
    return EntitySpan(gi.entityPool.entities).subspan(start, count);
}
inline BaseEntitySpan GetBaseEntityRange(std::size_t start, std::size_t count) {
    return BaseEntitySpan(g_baseEntities).subspan(start, count);
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
        if (nullptr == g_baseEntities[edict->state.number]) {
            g_baseEntities[edict->state.number] = entity;
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
