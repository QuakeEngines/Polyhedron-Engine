/*
// LICENSE HERE.

//
// ServerGameEntity.h
//
// Base entity class, where the fun begins. All entities are inherited from this,
// one way or the other :)
//
*/
#pragma once

// It makes sense to include TypeInfo in ServerGameEntity.h, 
// because this class absolutely requires it
#include "../../TypeInfo.h"

class ServerGameEntity {
public:
    //------------------------------------------------------------
    //
    // Dispatch Callback Function Pointers.
    //
    //------------------------------------------------------------
    using ThinkCallbackPointer      = void(ServerGameEntity::*)(void);
    using UseCallbackPointer        = void(ServerGameEntity::*)(ServerGameEntity* other, ServerGameEntity* activator);
    using TouchCallbackPointer      = void(ServerGameEntity::*)(ServerGameEntity* self, ServerGameEntity* other, cplane_t* plane, csurface_t* surf);
    using BlockedCallbackPointer    = void(ServerGameEntity::*)(ServerGameEntity* other);
    using TakeDamageCallbackPointer = void(ServerGameEntity::*)(ServerGameEntity* other, float kick, int32_t damage);
    using DieCallbackPointer        = void(ServerGameEntity::*)(ServerGameEntity* inflictor, ServerGameEntity* attacker, int damage, const vec3_t& point);

    //------------------------------------------------------------
    //
    // Construct/Destructor.
    //
    //------------------------------------------------------------
    ServerGameEntity(ServerEntity* svEntity);
    virtual ~ServerGameEntity();


    //------------------------------------------------------------
    //
    // Runtime Type Information.
    //
    //------------------------------------------------------------
    DefineTopAbstractClass( ServerGameEntity );

    // Checks if this entity class is exactly the given class
    // @param entityClass: an entity class which must inherint from ServerGameEntity
    template<typename entityClass>
    bool IsClass() const { // every entity has a ClassInfo, thanks to the DefineXYZ macro
        return GetTypeInfo()->IsClass( entityClass::ClassInfo );
    }

    // Checks if this entity class is a subclass of another, or is the same class
    // @param entityClass: an entity class which must inherint from ServerGameEntity
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
    void Use(ServerGameEntity* other, ServerGameEntity* activator);
    void Die(ServerGameEntity* inflictor, ServerGameEntity* attacker, int damage, const vec3_t& point);
    void Blocked(ServerGameEntity* other);
    void Touch(ServerGameEntity* self, ServerGameEntity* other, cplane_t* plane, csurface_t* surf);
    void TakeDamage(ServerGameEntity* other, float kick, int32_t damage);
    

    //------------------------------------------------------------
    //
    // ServerEntity interaction functions.
    //
    //------------------------------------------------------------
    //  Calls Use on this entity's targets, and deletes its killtargets if any
    //  @param activatorOverride: if nullptr, the entity's own activator is used and if the entity's own activator is nullptr, then this entity itself is the activator
    void UseTargets( ServerGameEntity* activatorOverride = nullptr );


    //------------------------------------------------------------
    //
    // Getters.
    //
    //------------------------------------------------------------
    // @returns The entity's center in world coordinates.
    inline vec3_t GetAbsoluteCenter(){
        return vec3_scale( GetAbsoluteMax() + GetAbsoluteMin(), 0.5f );
    }

    // @returns The entity's mins in world coordinates.
    inline const vec3_t& GetAbsoluteMin() {
        return serverEntity->absMin;
    }
    // @returns The entity's maxs in world coordinates.
    inline const vec3_t& GetAbsoluteMax() {
        return serverEntity->absMax;
    }

    // @returns The entity which activated this entity. (If any)
    inline ServerGameEntity* GetActivator() {
        return activator;
    }
    
    // @returns The angles of where this entity is pointing at.
    inline const vec3_t& GetAngles() {
        return serverEntity->state.angles;
    }

    // @returns The current angular velocity of where this entity is pointing at.
    inline const vec3_t& GetAngularVelocity() {
        return angularVelocity;
    }

    // @returns The local center of the bounding box.s
    inline vec3_t GetCenter() {
        return vec3_scale( GetMaxs() + GetMins(), 0.5f );
    }

    // @returns The entity's classname. Example: info_player_start
    inline const std::string &GetClassName() {
        return this->className;
    }

    // Set the 'className' value.
    inline void SetClassName(const char* className) {
        this->className = className;
    }

    // @returns A pointer to the client belonging to this entity. (If any.)
    gclient_s* GetClient() {
        return serverEntity->client;
    }

    // @returns the entity's current Clipping Mask.
    inline const int32_t GetClipMask() {
        return serverEntity->clipMask;
    }

    // @returns The damage this entity will give if messed with. 
    // an example could be if an entity gets stuck between a platform and a wall.
    inline const int32_t GetDamage() {
        return damage;
    }

    // @returns The current state of this entity's 'deadness'.
    inline const int32_t GetDeadFlag() {
        return deadFlag;
    }

    // @returns The delay before executing a trigger action.s
    inline const float &GetDelayTime() {
        return delayTime;
    }

    // @returns The effects of this entity.
    inline const uint32_t GetEffects() {
        return serverEntity->state.effects;
    }

    // @returns The enemy entity pointer (if any.)
    inline ServerGameEntity* GetEnemy() {
        return enemyEntity;
    }


    // @returns a reference to the 'entityDictionary'.
    virtual inline EntityDictionary &GetEntityDictionary() {
        return serverEntity->entityDictionary;
    }

    // @returns the current entity EventID, these are reset each frame.
    inline const uint8_t GetEventID() {
        return serverEntity->state.eventID;
    }

    // @returns The entity's general flags, coming from the EntityFlags enum.
    inline const int32_t GetFlags() {
        return flags;
    }

    // @returns The current animation frame of the entity.
    inline const int32_t GetFrame() {
        return serverEntity->state.frame;
    }

    // @returns The entity's own gravity.
    inline const float GetGravity() {
        return gravity;
    }

    // @returns The ground entity (if any).
    inline ServerGameEntity* GetGroundEntity() {
        return groundEntity;
    }

    // @returns The entity's ground linkcount.s
    inline int32_t GetGroundEntityLinkCount() {
        return groundEntityLinkCount;
    }

    // @returns The entity's health.
    inline const int32_t GetHealth() {
        return health;
    }

    // @returns The ideal yaw to use for this entity.
    inline const float GetIdealYawAngle() {
        return idealYawAngle;
    }

    // Get the 'inuse' value.
    inline qboolean IsInUse() {
        return serverEntity->inUse;
    }

    // Get the 'killTarget' entity value.
    inline const std::string &GetKillTarget() {
        return killTargetStr;
    }

    // Get the 'linkCount' value.
    inline const int32_t GetLinkCount() {
        // WID: Should we really do this? Fixes a bug when MiscExploboxes are on top of each other and "die".
        if (!serverEntity) {
            return 0;
        }

        return serverEntity->linkCount;
    }

    // Return the 'mass' value.
    inline const int32_t GetMass() {
        return mass;
    }

    // Return the 'maxHealth' value.
    inline const int32_t GetMaxHealth() {
        return maxHealth;
    }

    // Return the bounding box 'maxs' value.
    inline const vec3_t& GetMaxs() {
        return serverEntity->maxs;
    }

    // Return the 'message' value.
    inline const std::string &GetMessage() {
        return messageStr;
    }

    // Return the bounding box 'mins' value.
    inline const vec3_t& GetMins() {
        return serverEntity->mins;
    }
   
    // Return the 'model' value.
    inline const std::string &GetModel() {
        return model;
    }

    // Return the 'modelIndex, modelIndex1, modelIndex2, modelIndex3' values.
    inline const int32_t GetModelIndex() {
        return serverEntity->state.modelIndex;
    }
    inline const int32_t GetModelIndex2() {
        return serverEntity->state.modelIndex2;
    }
    inline const int32_t GetModelIndex3() {
        return serverEntity->state.modelIndex3;
    }
    inline const int32_t GetModelIndex4() {
        return serverEntity->state.modelIndex4;
    }

    // Return the 'movetype' value.
    inline const int32_t GetMoveType() {
        return moveType;
    } 

    // Return the 'nextThinkTime' value.
    inline const float GetNextThinkTime() {
        return nextThinkTime;
    }

    // Return the 'noiseIndex' value.
    inline const int32_t GetNoiseIndex() {
        return noiseIndex;
    }

    // Return the 'noiseIndex2' value.
    inline const int32_t GetNoiseIndex2() {
        return noiseIndex2;
    }

    inline const int32_t GetNumber() {
        return serverEntity->state.number;
    }

    // Return the 'oldEnemyPtr' entity pointer.
    ServerGameEntity* GetOldEnemy() {
        return oldEnemyEntity;
    }

    // Return the 'oldOrigin' value.
    inline const vec3_t& GetOldOrigin() {
        return serverEntity->state.oldOrigin;
    }

    // Return the 'origin' value.
    inline const vec3_t &GetOrigin() {
        return serverEntity->state.origin;
    }

    // Get the 'owner' value.
    inline ServerGameEntity* GetOwner() {
        return this->ownerEntity;
    }

    // Return the 'renderEffects' value.
    inline const int32_t GetRenderEffects() {
        return serverEntity->state.renderEffects;
    }

    // Get the 'pathTarget' entity value.
    // Overridden by PathCorner
    // TODO: replace this ugly workaround with some component system
    inline virtual const char* GetPathTarget() {
        return nullptr;
    }

    // Return the 'serverFlags' value.
    inline const int32_t GetServerFlags() {
        return serverEntity->serverFlags;
    }

    // Return the 'skinNumber' value.
    inline const int32_t GetSkinNumber() {
        return serverEntity->state.skinNumber;
    }

    // Return the 'size' value.
    inline const vec3_t& GetSize() {
        return serverEntity->size;
    }

    // Return the 'solid' value.
    inline const uint32_t GetSolid() {
        return serverEntity->solid;
    }

    // Return the 'spawnFlags' value.
    inline const int32_t GetSpawnFlags() {
        return spawnFlags;
    }

    // Return a reference to the serverEntity its state.
    inline const EntityState& GetState() {
        return serverEntity->state;
    }
    // Return the 'style' value.
    inline const int32_t GetStyle() {
        return style;
    }

    // Return the 'sound' value.
    inline const int32_t GetSound() {
        return serverEntity->state.sound;
    }

    // Return the 'takeDamage' value.
    inline const int32_t GetTakeDamage() {
        return takeDamage;
    }

    // Return the 'target' entity value.
    inline const std::string& GetTarget() {
        return targetStr;
    }
    // Return the 'targetName' entity value.
    inline const std::string& GetTargetName() {
        return targetNameStr;
    }

    // Return the 'team' entity value.
    inline const std::string &GetTeam() {
        return teamStr;
    }

    // Return the 'teamChain' entity value.
    inline ServerGameEntity* GetTeamChainEntity() {
        return teamChainEntity;
    }

    // Return the 'teamMaster' entity value.
    inline ServerGameEntity *GetTeamMasterEntity() {
        return teamMasterEntity;
    }

    // Return the 'viewHeight' entity value.
    inline const int32_t GetViewHeight() {
        return viewHeight;
    }

    // Return the 'velocity' value.
    inline const vec3_t& GetVelocity() {
        return velocity;
    }

    // Return the 'wait' value.
    inline const float& GetWaitTime() {
        return waitTime;
    }

    // Return the 'waterLevel' value.
    inline const int32_t GetWaterLevel() {
        return waterLevel;
    }

    // Return the 'waterType' value.
    inline const int32_t GetWaterType() {
        return waterType;
    }

    inline const float GetYawSpeed() {
        return yawSpeed;
    }

    //------------------------------------------------------------
    //
    // Setters.
    //
    //------------------------------------------------------------
    // Return the bounding box absolute 'min' value.
    inline void SetAbsoluteMin(const vec3_t &absMin) {
        serverEntity->absMin = absMin;
    }

    // Return the bounding box absolute 'max' value.
    inline void SetAbsoluteMax(const vec3_t &absMax) {
        serverEntity->absMax = absMax;
    }

    // Return the 'angles' value.
    inline void SetAngles(const vec3_t& angles) {
        serverEntity->state.angles = angles;
    }

    // Set the 'angularVelocity' value.
    inline void SetAngularVelocity(const vec3_t& angularVelocity) {
        this->angularVelocity = angularVelocity;
    }

    // Set the 'mins', and 'maxs' values of the entity bounding box.
    inline void SetBoundingBox(const vec3_t& mins, const vec3_t& maxs) {
        serverEntity->mins = mins;
        serverEntity->maxs = maxs;
    }

    // Return the 'clipmask' value.
    inline void SetClipMask(const int32_t &clipMask) {
        serverEntity->clipMask = clipMask;
    }

    // Set the 'damage' value.
    inline void SetDamage(const int32_t &damage) {
        this->damage = damage;
    }

    // Set the 'deadFlag' value.
    inline void SetDeadFlag(const int32_t& deadFlag) {
        this->deadFlag = deadFlag;
    }

    // Set the 'delayTime' value.
    inline void SetDelayTime(const float& delayTime) {
        this->delayTime = delayTime;
    }

    // Set the 'effects' value.
    inline void SetEffects(const uint32_t &effects) {
        serverEntity->state.effects = effects;
    }

    // Set the 'enemyPtr' pointer.
    inline void SetEnemy(ServerGameEntity* enemy) {
        this->enemyEntity = enemy;
    }

    // Return the 'eventID' value.
    inline void SetEventID(const uint8_t &eventID) {
        serverEntity->state.eventID = eventID;
    }

    // Set the 'flags' value.
    inline void SetFlags(const int32_t &flags) {
        this->flags = flags;
    }

    // Set the 'frame' value.
    inline void SetFrame(const int32_t &frame) {
        serverEntity->state.frame = frame;;
    }

    // Set the 'gravity' value.
    inline void SetGravity(const float &gravity) {
        this->gravity = gravity;
    }

    // Set the 'groundEntitPtr' entity.
    inline void SetGroundEntity(ServerGameEntity* groundEntity) {
        // Set ServerGameEntity variant ground entity.
        this->groundEntity = groundEntity;
    }

    // Set the 'groundEntityLinkCount' value.
    inline void SetGroundEntityLinkCount(int32_t groundEntityLinkCount) {
        // Set it for THIS class entity.
        this->groundEntityLinkCount = groundEntityLinkCount;
    }

    // Set the 'health' value.
    inline void SetHealth(const int32_t &health) {
        this->health = health;
    }

    // Set the 'idealYawAngle' value.
    inline void SetIdealYawAngle(const float& idealYawAngle) {
        this->idealYawAngle = idealYawAngle;
    }

    // Set the 'inuse' value.
    inline void SetInUse(const qboolean& inUse) {
        serverEntity->inUse = inUse;
    }
    
    // Set the 'killTargetSTr' value.
    inline void SetKillTarget(const std::string& killTarget) {
        this->killTargetStr = killTarget;
    }

    // Set the 'linkCount' value.
    inline void SetLinkCount(const int32_t &linkCount) {
        serverEntity->linkCount = linkCount;
    }

    // Set the 'mass' value.
    inline void SetMass(const int32_t &mass) {
        this->mass = mass;
    }

    // Set the 'maxHealth' value.
    inline void SetMaxHealth(const int32_t& maxHealth) {
        this->maxHealth = maxHealth;
    }

    // Set the 'maxs' value.
    inline void SetMaxs(const vec3_t& maxs) {
        serverEntity->maxs = maxs;
    }

    // Set the 'messageStr' value.
    inline void SetMessage(const std::string& message) {
        this->messageStr = message;
    }
    
    // Set the 'mins' value.
    inline void SetMins(const vec3_t& mins) {
        serverEntity->mins = mins;
    }

    // Set the 'modelIndex, modelIndex1, modelIndex2, modelIndex3' values.
    inline void SetModelIndex(const int32_t& index) {
        serverEntity->state.modelIndex = index;
    }
    inline void SetModelIndex2(const int32_t& index) {
        serverEntity->state.modelIndex2 = index;
    }
    inline void SetModelIndex3(const int32_t& index) {
        serverEntity->state.modelIndex3 = index;
    }
    inline void SetModelIndex4(const int32_t& index) {
        serverEntity->state.modelIndex4 = index;
    }

    // Set the 'model' value.
    inline void SetModel(const std::string &model) {
        // Set model.
        this->model = model;

        // Set the model.
        gi.SetModel(serverEntity, model.c_str());

        // Set model index.
        SetModelIndex(gi.ModelIndex(model.c_str()));
    }

    // Set the 'moveType' value.
    inline void SetMoveType(const int32_t &moveType) {
        this->moveType = moveType;
    }

    // Set the 'nextThinkTime' value.
    inline void SetNextThinkTime(const float& nextThinkTime) {
        this->nextThinkTime = nextThinkTime;
    }

    // Set the 'noiseIndex' value.
    inline void SetNoiseIndex(const int32_t& noiseIndex) {
        this->noiseIndex = noiseIndex;
    }
    
    inline void SetNumber(const int32_t number) {
        serverEntity->state.number = number;
    }

    // Set the 'oldEnemyPtr' pointer.
    inline void SetOldEnemy(ServerGameEntity* oldEnemy) {
        this->oldEnemyEntity = oldEnemy;
    }

    // Set the 'origin' value.
    inline void SetOldOrigin(const vec3_t& oldOrigin) {
        serverEntity->state.oldOrigin = oldOrigin;
    }

    // Set the 'origin' value.
    inline void SetOrigin(const vec3_t& origin) {
        serverEntity->state.origin = origin;
    }

    // Set the 'owner' value.
    inline void SetOwner(ServerGameEntity* owner) {
        this->ownerEntity = owner;
    }

    // Set the 'renderEffects' value.
    inline void SetRenderEffects(const int32_t& renderEffects) {
        serverEntity->state.renderEffects = renderEffects;
    }

    // Set the 'serverFlags' value.
    inline void SetServerFlags(const int32_t &serverFlags) {
        serverEntity->serverFlags = serverFlags;
    }

    // Set the 'skinNumber' value.
    inline void SetSkinNumber(const int32_t& skinNumber) {
        serverEntity->state.skinNumber = skinNumber;
    }

    // Sest the 'size' value.
    inline void SetSize(const vec3_t& size) {
        serverEntity->size = size;
    }

    // Set the 'solid' value.
    inline void SetSolid(const uint32_t &solid) {
        serverEntity->solid = solid;
    }

    // Sets the 'sound' value.
    inline void SetSound(const int32_t& sound) {
        serverEntity->state.sound = sound;
    }

    // Set the 'spawnFlags' value.
    inline void SetSpawnFlags(const int32_t& spawnFlags) {
        this->spawnFlags = spawnFlags;
    }

    // Set another copy of a serverEntity its state.
    inline void SetState(const EntityState &state) {
        serverEntity->state = state;
    }

    // Set the 'style' value.
    inline void SetStyle(const int32_t &style) {
        this->style = style;
    }

    // Set the 'takeDamage' value.
    inline void SetTakeDamage(const int32_t& takeDamage) {
        this->takeDamage = takeDamage;
    }

    // Set the 'target' entity value.
    inline void SetTarget(const std::string& target) {
        this->targetStr = target;
    }
    // Set the 'targetName' entity value.
    inline void SetTargetName(const std::string& targetName) {
        this->targetNameStr = targetName;
    }

    // Set the 'teamChain' entity value.
    inline void SetTeamChainEntity(ServerGameEntity* entity) {
        teamChainEntity = entity;
    }

    // Set the 'teamMaster' entity value.
    inline void SetTeamMasterEntity(ServerGameEntity* entity) {
        teamMasterEntity = entity;
    }

    // Set the 'viewHeight' entity value.
    inline void SetViewHeight(const int32_t& height) {
        this->viewHeight = height;
    }

    // Set the 'velocity' value.
    inline void SetVelocity(const vec3_t &velocity) {
        this->velocity = velocity;
    }

    // Return the 'wait' value.
    inline void SetWaitTime(const float& waitTime) {
        this->waitTime = waitTime;
    }

    // Return the 'waterLevel' value.
    inline void SetWaterLevel(const int32_t &waterLevel) {
        this->waterLevel = waterLevel;
    }

    // Return the 'waterType' value.
    inline void SetWaterType(const int32_t &waterType) {
        this->waterType = waterType;
    }

    // Yaw Speed. (Should be for monsters...)
    inline void SetYawSpeed(const float& yawSpeed) {
        this->yawSpeed = yawSpeed;
    }

    //------------------------------------------------------------
    // Placeholders for SVGBaseMover and derivates of that class.
    //------------------------------------------------------------
    virtual inline float GetAcceleration() {
        return 0.f;
    }
    virtual inline float GetDeceleration() {
        return 0.f;
    }
    virtual inline float GetSpeed() {
        return 0.f;
    }
    virtual inline const vec3_t& GetStartPosition() {
        return vec3_zero();
    }
    virtual inline const vec3_t& GetEndPosition() {
        return vec3_zero();
    }


    //------------------------------------------------------------
    // 
    // General ServerEntity Functions.
    // 
    //------------------------------------------------------------
    // Link entity to the world for collision testing.
    void LinkEntity();
    
    // Marks the entity to be removed in the next server frame
    // This is preferred to SVG_FreeEntity, as it is safer
    void Remove();

    // Unlink the entity from the world for collision testing.
    void UnlinkEntity();

    // Returns the server entity pointer.
    inline ServerEntity* GetServerEntity() {
        return serverEntity;
    }

    // Used only in SVG_FreeEntity
    inline void SetServerEntity( ServerEntity* svEntity )
    {
        serverEntity = svEntity;
    }

protected:
    //------------------------------------------------------------
    // 
    // ServerEntity Dictionary Value Parsing functions.
    // 
    // All return true on success and will have set the parsed
    // value on the referenced variale. Otherwise, it'll pick a 
    // default, usually 0, 0.f, "", or vec3_zero()
    //------------------------------------------------------------
    qboolean ParseFloatKeyValue(const std::string& key, const std::string& value, float& floatNumber);
    qboolean ParseIntegerKeyValue(const std::string& key, const std::string& value, int32_t& integerNumber);
    qboolean ParseUnsignedIntegerKeyValue(const std::string& key, const std::string& value, uint32_t& unsignedIntegerNumber);
    qboolean ParseStringKeyValue(const std::string& key, const std::string& value, std::string& stringValue);
    qboolean ParseVector3KeyValue(const std::string& key, const std::string& value, vec3_t& vectorValue);

    // The actual server entity this class is a member of.
    ServerEntity *serverEntity;

    //
    // Other base entity members. (These were old fields in edict_T back in the day.)
    //
    // 
    //---------------------------------
    // -- Flags
    // ServerEntity flags, general flags, flags... :) 
    int32_t flags;
    // ServerEntity spawn flags (Such as, is this a dropped item?)
    int32_t spawnFlags;

    //---------------------------------
    // -- Classname.
    std::string className;

    //---------------------------------
    // Sounds.
    int32_t noiseIndex;
    int32_t noiseIndex2;

    //---------------------------------
    // -- Strings.
    // ServerEntity MODEL filename.
    std::string model;
    // ServerEntity team Str.
    std::string teamStr;

    // Trigger kill target string.
    std::string killTargetStr;
    // Trigger target string.
    std::string targetStr;
    // Trigger its own targetname string.
    std::string targetNameStr;
    // Trigger its message string.
    std::string messageStr;

    //---------------------------------
    // -- Types (Move, Water, what have ya? Add in here.)
    // Move Type. (MoveType::xxx)
    int32_t moveType;
    // WaterType::xxxx
    int32_t waterType;
    // WaterLevel::xxxx
    int32_t waterLevel;

    //---------------------------------
    // -- Physics
    // Angle direction: Set in Trenchbroom -1 = up -2 = down.
    //float angle;
    // Velocity.
    vec3_t velocity;
    // Angular Velocity.
    vec3_t angularVelocity;
    // Mass
    int32_t mass;
    // Per entity gravity multiplier (1.0 is normal). TIP: Use for lowgrav artifact, flares
    float gravity;
    
    //-----------------------------------
    // -- Pointers.
    // Goal ServerEntity.
    ServerEntity* goalEntityPtr;
    // Move Target ServerEntity.
    ServerEntity* moveTargetPtr;
    // The entity that activated this
    ServerGameEntity* activator;
    
    // Yaw Speed. (Should be for monsters...)
    float yawSpeed;
    // Ideal Yaw Angle. (Should be for monsters...)
    float idealYawAngle;

    //------------------------------------
    // Timing.
    // The next 'think' time, determines when to call the 'think' callback.
    float nextThinkTime;
    // Delay before calling trigger execution.
    float delayTime;
    // Wait time before triggering at all, in case it was set to auto.
    float waitTime;

    // Ground ServerEntity link count. (To keep track if it is linked or not.)
    int32_t groundEntityLinkCount;

    //------------------------------------
    // ServerEntity Status.
    // Current health.
    int32_t health;
    // Maximum health.
    int32_t maxHealth;

    //------------------------------------
    // ServerEntity GAME settings.
    // The height above the origin, this is where EYE SIGHT comes from. Ok?
    int32_t viewHeight;
    // Determines how to interpret, take damage like a man or like a ... ? Yeah, pick up soap.
    int32_t takeDamage;
    // Actual damage it does if encountered or fucked around with.
    int32_t damage;
    // Dead Flag. (Are we dead, dying or...?)
    int32_t deadFlag;

    //
    // This one resides here... for now.
    //
    //float delay;

    //
    // Style/
    // 
    int32_t style;

    // ServerEntity pointers.
    // 
    // Current active enemy, NULL if not any.    
    ServerGameEntity *enemyEntity;
    // Ground entity we're standing on.
    ServerGameEntity *groundEntity;
    // Old enemy, NULL if not any.
    ServerGameEntity *oldEnemyEntity;

    // Owner pointer. (Such as, did the player fire a blaster bolt? If so, the owner is...)
    ServerGameEntity* ownerEntity;

    // Team Chain Pointer.
    ServerGameEntity* teamChainEntity;
    // Master Pointer.
    ServerGameEntity* teamMasterEntity;
    
public:
    //
    // Ugly, but effective callback SET methods.
    //
    // Sets the 'Think' callback function.
    template<typename function>
    inline void SetThinkCallback(function f)
    {
        thinkFunction = static_cast<ThinkCallbackPointer>(f);
    }
    inline qboolean HasThinkCallback() {
        return (thinkFunction != nullptr ? true : false);
    }

    // Sets the 'Use' callback function.
    template<typename function>
    inline void SetUseCallback(function f)
    {
        useFunction = static_cast<UseCallbackPointer>(f);
    }

    // Sets the 'Touch' callback function.
    template<typename function>
    inline void SetTouchCallback(function f)
    {
        touchFunction = static_cast<TouchCallbackPointer>(f);
    }
    inline qboolean HasTouchCallback() {
        return (touchFunction != nullptr ? true : false);
    }

    // Sets the 'Blocked' callback function.
    template<typename function>
    inline void SetBlockedCallback(function f)
    {
        blockedFunction = static_cast<BlockedCallbackPointer>(f);
    }

    // Sets the 'SetTakeDamage' callback function.
    template<typename function>
    inline void SetTakeDamageCallback(function f)
    {
        takeDamageFunction = static_cast<TakeDamageCallbackPointer>(f);
    }
    inline qboolean HasTakeDamageCallback() {
        return (takeDamageFunction != nullptr ? true : false);
    }

    // Sets the 'Die' callback function.
    template<typename function>
    inline void SetDieCallback(function f)
    {
        dieFunction = static_cast<DieCallbackPointer>(f);
    }


protected:
    //
    // Callback function pointers.
    //
    ThinkCallbackPointer        thinkFunction;
    UseCallbackPointer          useFunction;
    TouchCallbackPointer        touchFunction;
    BlockedCallbackPointer      blockedFunction;
    TakeDamageCallbackPointer   takeDamageFunction;
    DieCallbackPointer          dieFunction;

public:
    //
    // Callback implementations that can be set by all child entities.
    //
    void SVGBaseEntityThinkRemove(void);
    // "No" thinking
    void SVGBaseEntityThinkNull() { }
};
