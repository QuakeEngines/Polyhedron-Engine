// License here.
#pragma once

struct ServerEntity;

//---------------------------------------------------------
// EntityBase represents a game entity and all of the data 
// and logic it contains to make it data to make an entity function
// as long as it has a proper backing object for its entity state.
// 
// Synced entities will use a ServerEntity slot as a backing entity, 
// allowing the server to sync the entity to clients.
// 
// Private entities will use their own internal entity state, so they aren't 
// visible to the server. 
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

    DefineTopAbstractClass(EntityBase);

public:

    // Checks if this entity class is exactly the given class
    // @param entityClass: an entity class which must inherint from SynchedEntityBase.h
    template<typename entityClass>
    bool IsClass() const { // every entity has a ClassInfo, thanks to the DefineXYZ macro
        return GetTypeInfo()->IsClass( entityClass::ClassInfo );
    }

    // Checks if this entity class is a subclass of another, or is the same class
    // @param entityClass: an entity class which must inherint from SynchedEntityBase.h
    template<typename entityClass>
    bool IsSubclassOf() const {
        return GetTypeInfo()->IsSubclassOf( entityClass::ClassInfo );
    }

    //------------------------------------------------------------
    //
    // Interface Functions.
    //
    //------------------------------------------------------------
    virtual void Precache();    // Precaches data.
    virtual void Spawn();       // Spawns the entity.
    virtual void Respawn();     // Respawns the entity.
    virtual void PostSpawn();   // PostSpawning is for handling entity references, since they may not exist yet during a spawn period.
    virtual void Think();       // General entity thinking routine.

    virtual void SpawnKey(const std::string& key, const std::string& value); // Called for each key:value when parsing the entity dictionary.

    //------------------------------------------------------------
    //
    // Dispatch Callback Functions.
    //
    //------------------------------------------------------------
    // // Admer: these should all be prefixed with Dispatch
    void Use(SynchedEntityBase * other, SynchedEntityBase * activator);
    void Die(SynchedEntityBase * inflictor, SynchedEntityBase * attacker, int damage, const vec3_t& point);
    void Blocked(SynchedEntityBase * other);
    void Touch(SynchedEntityBase * self, SynchedEntityBase * other, cplane_t* plane, csurface_t* surf);
    void TakeDamage(SynchedEntityBase * other, float kick, int32_t damage);

    //------------------------------------------------------------
    //
    // ServerEntity interaction functions.
    //
    //------------------------------------------------------------
    //  Calls Use on this entity's targets, and deletes its killtargets if any
    //  @param activatorOverride: if nullptr, the entity's own activator is used and if the entity's own activator is nullptr, then this entity itself is the activator
    void UseTargets( SynchedEntityBase * activatorOverride = nullptr );

    //------------------------------------------------------------
    //
    // Getters.
    //
    //------------------------------------------------------------
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

    // Set the 'effects' value.
    inline void SetEffects(const uint32_t &effects) {
        entityHandle->state.effects = effects;
    }

    // Return the 'eventID' value.
    inline void SetEventID(const uint8_t &eventID) {
        entityHandle->state.eventID = eventID;
    }

    // Set the 'inuse' value.
    inline void SetInUse(const qboolean& inUse) {
        entityHandle->inUse = inUse;
    }

    // Set the 'linkCount' value.
    inline void SetLinkCount(const int32_t &linkCount) {
        entityHandle->linkCount = linkCount;
    }

    // Set the 'mins' value.
    inline void SetMins(const vec3_t& mins) {
        entityHandle->mins = mins;
    }

    // Set the 'maxs' value.
    inline void SetMaxs(const vec3_t& maxs) {
        entityHandle->maxs = maxs;
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

    // Set another copy of a serverEntity its state.
    inline void SetState(const EntityState &state) {
        entityHandle->state = state;
    }
};