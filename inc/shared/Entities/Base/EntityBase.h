// License here.
#pragma once

struct ServerEntity;

//---------------------------------------------------------
// EntityBase - Points to a server entity handle.
//---------------------------------------------------------
class EntityBase
{
protected:
    // Handle to the server entity. (Assumed to be internal)
    ServerEntity  *entityHandle;
    
    // Constructor.
    EntityBase(ServerEntity* serverEntityHandle);

    // Destructor.
    virtual ~EntityBase();

public:
    // Return the 'renderEffects' value.
    inline const int32_t GetRenderEffects() {
        return entityHandle->state.renderEffects;
    }

    // Get the 'pathTarget' entity value.
    // Overridden by PathCorner
    // TODO: replace this ugly workaround with some component system
    inline virtual const char* GetPathTarget() {
        return nullptr;
    }

    // Return the 'skinNumber' value.
    inline const int32_t GetSkinNumber() {
        return entityHandle->state.skinNumber;
    }

    // Return the 'size' value.
    inline const vec3_t& GetSize() {
        return entityHandle->size;
    }

    // Return the 'solid' value.
    inline const uint32_t GetSolid() {
        return entityHandle->solid;
    }

    // Return the 'spawnFlags' value.
    inline const int32_t GetServerFlags() {
        return entityHandle->serverFlags;
    }

    // Return a reference to the serverEntity its state.
    inline EntityState& GetState() {
        return entityHandle->state;
    }

    // Return the 'sound' value.
    inline const int32_t GetSound() {
        return entityHandle->state.sound;
    }
    // Set the 'linkCount' value.
    inline void SetLinkCount(const int32_t &linkCount) {
        entityHandle->linkCount = linkCount;
    }

    // Set the 'mins' value.
    inline void SetMins(const vec3_t& mins) {
        entityHandle->mins = mins;
    }

    // Set the 'modelIndex, modelIndex1, modelIndex2, modelIndex3' values.
    inline void SetModelIndex(const int32_t& index) {
        entityHandle->state.modelIndex = index;
    }
    inline void SetModelIndex2(const int32_t& index) {
        entityHandle->state.modelIndex2 = index;
    }
    inline void SetModelIndex3(const int32_t& index) {
        entityHandle->state.modelIndex3 = index;
    }
    inline void SetModelIndex4(const int32_t& index) {
        entityHandle->state.modelIndex4 = index;
    }

    // Set the 'origin' value.
    inline void SetOldOrigin(const vec3_t& oldOrigin) {
        entityHandle->state.oldOrigin = oldOrigin;
    }

    // Set the 'origin' value.
    inline void SetOrigin(const vec3_t& origin) {
        entityHandle->state.origin = origin;
    }

    // Set the 'renderEffects' value.
    inline void SetRenderEffects(const int32_t& renderEffects) {
        entityHandle->state.renderEffects = renderEffects;
    }

    // Set the 'serverFlags' value.
    inline void SetServerFlags(const int32_t &serverFlags) {
        entityHandle->serverFlags = serverFlags;
    }

    // Set the 'skinNumber' value.
    inline void SetSkinNumber(const int32_t& skinNumber) {
        entityHandle->state.skinNumber = skinNumber;
    }

    // Sest the 'size' value.
    inline void SetSize(const vec3_t& size) {
        entityHandle->size = size;
    }

    // Set the 'solid' value.
    inline void SetSolid(const uint32_t &solid) {
        entityHandle->solid = solid;
    }

    // Sets the 'sound' value.
    inline void SetSound(const int32_t& sound) {
        entityHandle->state.sound = sound;
    }
    //vec3_t &GetOrigin() { return entityHandle->state.origin; }
    //void SetOrigin(const vec3_t &o) { entityHandle->state.origin = o; }
};