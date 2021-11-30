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
*/
#pragma once

//--------------------------------------------------------
// Include all our requirements from ServerEntity, to our
// SynchedEntityBasewhich depends on SynchedEntityBase.
// 
// Other ServerGameEntities exist too, based on the same philosophy.
// Some people just want to be left alone, so we let them.
// 
// Sometimes they don't and mayne we a
//--------------------------------------------------------
// Include our shared entity classes.
#include "Shared/Entities.h"

// ServerGame Specific.
#include "Entities/Base/EntityBase.h"
#include "Entities/Base/SynchedEntityBase.h"

// Predeclare
#include "Shared/Entities/TypeInfo.h"


//
// Filter function namespace that actually contains the entity filter implementations.
// 
namespace EntityFilterFunctions {
    // @returns true in case the (server-)ServerEntity is in use.
    //inline bool EntityInUse (const ServerEntity& ent) { return ent.inUse; }
    // @returns true in case the (server-)ServerEntity has a client attached to it.
    inline bool ServerEntityHasClient(ServerEntity& ent) { return static_cast<bool>(ent.client); }
    
    // @returns true in case the (server-)ServerEntity has a Class ServerEntity attached to it.
    inline bool SynchedGameEntityHasClassEntity(SynchedEntityBase& ent) { return static_cast<bool>(ent.GetClassName().empty()); }
    // Returns true in case the (server-)ServerEntity has a client attached to it.
    inline bool SynchedGameEntityHasClient(SynchedEntityBase * ent) { return ent->GetClient(); }
    // Returns true in case the BaseEntity has a ground entity set to it.
    inline bool SynchedGameEntityHasGroundEntity(SynchedEntityBase* ent) { return ent->GetGroundEntity(); }
    // Returns true in case the BaseEntity is properly linked to a server entity.
    //line bool ServerGameEntityHasServerEntity(SynchedEntityBase * ent) { return ent->GetEntityServerHandle(); }
    // Returns true if the BaseEntity contains the sought for targetname.
    inline bool ServerGameEntityHasTargetName(SynchedEntityBase * ent) { return ent->GetTargetName() != "" && !ent->GetTargetName().empty(); }
    // Returns true in case the BaseEntity has a client attached to it.
    //inline bool ServerGameEntityInUse(SynchedEntityBase * ent) { return ent->IsInUse(); }
    // Returns true if the BaseEntity is NOT a nullptr.
    //inline bool ServerGameEntityIsValidPointer(SynchedEntityBase * ent) { return ent != nullptr; }

    // Returns true in case the BaseEntity has the queried for classname.
    //inline bool BaseEntityHasClass(SynchedEntityBase * ent, std::string classname) { return ent->GetClassName() == classname; }
};

//
// Actual filters to use with GetEntityRange, ..., ... TODO: What other functions?
//
namespace ServerGameEntityFilters {
    using namespace std::views;

    // BaseEntity Filters to employ by pipelining. Very nice and easy method of doing loops.
    inline auto HasGroundEntity = std::views::filter( &EntityFilterFunctions::SynchedGameEntityHasGroundEntity);
    inline auto HasClient = std::views::filter ( &EntityFilterFunctions::SynchedGameEntityHasClassEntity );

    // WID: TODO: This one actually has to move into EntityFilterFunctions, and then
    // be referred to from here. However, I am unsure how to do that as of yet.
    inline auto HasClassName(const std::string& classname) {
        return std::ranges::views::filter(
            [classname /*need a copy!*/](SynchedEntityBase  * ent) {
                return ent->GetClassName() == classname;
            }
        );
    }

    // WID: TODO: This one actually has to move into EntityFilterFunctions, and then
    // be referred to from here. However, I am unsure how to do that as of yet.
    inline auto HasKeyValue(const std::string& fieldKey, const std::string& fieldValue) {
        return std::ranges::views::filter(
            [fieldKey, fieldValue /*need a copy!*/](SynchedEntityBase *ent) {
                if (ent) {
                    //EntityDictionary& dictionary = ent->GetEntityDictionary();

                    //if (dictionary.find(fieldKey) != dictionary.end()) {
                    //    if (dictionary[fieldKey] == fieldValue) {
                    //        return true;
                    //    }
                    //}
                    return false;
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
            [](EntityBase * ent) {
                return ent->IsClass<ClassType>();
            }
        );
    }

    template <typename ClassType>
    auto IsSubclassOf() {
        return std::ranges::views::filter(
            [](EntityBase * ent) {
                return ent->IsSubclassOf<ClassType>();
            }
        );
    }

    // WID: TODO: This one actually has to move into EntityFilterFunctions, and then
    // be referred to from here. However, I am unsure how to do that as of yet.
    inline auto WithinRadius(vec3_t origin, float radius, uint32_t excludeSolidFlags) {
        return std::ranges::views::filter(
            [origin, radius, excludeSolidFlags/*need a copy!*/](SynchedEntityBase * ent) {
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
    //inline auto Standard = (IsValidPointer | HasServerEntity | InUse);
};
namespace SvgEF = ServerGameEntityFilters; // Shortcut, lesser typing.

//
// C++ using magic.
// 
using ServerGameEntitySpan = std::span<SynchedEntityBase *>;

// Returns a span containing all ServerEntities in the range of:
// [start] to [start + count].
//
// This span can be quired on by several filters to ensure you only
// acquire a list of entities with specific demands.
template <std::size_t start, std::size_t count>
inline auto GetServerEntityRange() -> std::span<SynchedEntityBase, count> {
    return std::span(serverGameEntities).subspan<start, count>();
}
inline ServerGameEntitySpan GetServerEntityRange(std::size_t start, std::size_t count) {
    return ServerGameEntitySpan(serverGameEntities).subspan(start, count);
}




//
// C++ using magic.
//
using GameEntitySpan = std::span<SynchedEntityBase *>;
using GameEntityVector = std::vector<SynchedEntityBase *>;

// Returns a span containing all ServerGameEntities in the range of:
// [start] to [start + count].
//
// This span can be quired on by several filters to ensure you only
// acquire a list of entities with specific demands.
template <std::size_t start, std::size_t count>
inline auto GetGameEntityRange() -> std::span<SynchedEntityBase *, count> {
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
SynchedEntityBase * SVG_FindEntityByKeyValue(const std::string& fieldKey, const std::string& fieldValue, SynchedEntityBase * lastEntity = nullptr);


//
// Server ServerEntity handling.
//
void    SVG_InitEntity(ServerEntity* e);
void    SVG_FreeEntity(ServerEntity* e);

ServerEntity* SVG_GetWorldServerEntity();
ServerEntity* SVG_Spawn(void);

ServerEntity* SVG_CreateTargetChangeLevel(char* map);

// Admer: quick little template function to spawn entities, until we have this code in a local game class :)
template<typename entityClass, typename... Args>
inline entityClass* SVG_CreateClassEntity(Args&& ...args) {
    return new entityClass(std::forward(args)...);
}


//
// ClassEntity handling.
//
SynchedEntityBase * SVG_GetWorldSpawnEntity();
SynchedEntityBase * SVG_SpawnClassEntity(ServerEntity* ent, const std::string& className);
void SVG_FreeClassEntity(ServerEntity* ent);
