// License here.
#pragma once

namespace ServerEntityFilterFunctions {
    // @returns true in case the (server-)ServerEntity is in use.
    inline bool ServerEntityInUse (const ServerEntity& ent) { return ent.inUse; }
    // @returns true in case the (server-)ServerEntity has a client attached to it.
    inline bool ServerEntityHasClient(ServerEntity& ent) { return static_cast<bool>(ent.client); }
    // @returns true in case the (server-)ServerEntity has a Class ServerEntity attached to it.
    inline bool ServerEntityHasClassEntity(ServerEntity& ent) { return static_cast<bool>(ent.className.empty()); }
};

//
// Actual filters to use with GetGameEntityRange, ..., ... TODO: What other functions?
//
namespace ServerEntityFilters {
    using namespace std::views;

    inline auto InUse = std::views::filter( &ServerEntityFilterFunctions::EntityInUse );
    inline auto HasClient = std::views::filter( &ServerEntityFilterFunctions::EntityHasClient );
    inline auto HasClassEntity = std::views::filter( &ServerEntityFilterFunctions::EntityHasClassEntity );
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
namespace sgef = EntityFilters; // Shortcut, lesser typing.

//
// C++ using magic.
// 
using EntitySpan = std::span<ServerEntity*>;

// Returns a span containing all ServerEntities in the range of:
// [start] to [start + count].
//
// This span can be quired on by several filters to ensure you only
// acquire a list of entities with specific demands.
template <std::size_t start, std::size_t count>
inline auto GetServerEntityRange() -> std::span<ServerEntity, count> {
    return std::span(g_entities).subspan<start, count>();
}
inline EntitySpan GetServerEntityRange(std::size_t start, std::size_t count) {
    return EntitySpan(g_entities).subspan(start, count);
}