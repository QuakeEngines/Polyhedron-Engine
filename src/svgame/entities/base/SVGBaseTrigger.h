/*
// LICENSE HERE.

//
// SVGBaseTrigger.h
//
// Base Trigger class, for brush and point entities. (Yes we can do this.)
//
*/
#ifndef __SVGAME_ENTITIES_BASE_SVGBASETRIGGER_H__
#define __SVGAME_ENTITIES_BASE_SVGBASETRIGGER_H__

class SVGBaseTrigger : public ServerGameEntity {
public:
    //
    // Constructor/Deconstructor.
    //
    SVGBaseTrigger(ServerEntity* svEntity);
    virtual ~SVGBaseTrigger();

    DefineAbstractClass( SVGBaseTrigger, ServerGameEntity );

    //
    // Interface functions. 
    //
    virtual void Precache() override;    // Precaches data.
    virtual void Spawn() override;       // Spawns the entity.
    virtual void Respawn() override;     // Respawns the entity.
    virtual void PostSpawn() override;   // PostSpawning is for handling entity references, since they may not exist yet during a spawn period.
    virtual void Think() override;       // General entity thinking routine.

    virtual void SpawnKey(const std::string& key, const std::string& value)  override;

    //
    // Trigger functions.
    //
    void UseTargets(ServerGameEntity* activator);

    //
    // Get/Set
    // 
    // Return the 'activatorEntity' entity pointer.
    ServerGameEntity* GetActivator() {
        return activatorEntity;
    }

    //
    // ServerEntity Set Functions.
    //
    // Set the 'activatorEntity' pointer.
    inline void SetActivator(ServerGameEntity* activator) {
        this->activatorEntity = activator;
    }

protected:
    /* legacy trigger architecture */
    //float m_flDelay;
    //virtual void(entity, int) Trigger;
    //virtual void(entity, int, float) UseTargets;

    ///* master feature */
    //virtual int(void) GetValue;
    //virtual int(void) GetMaster;

    ///* spawn setup helpers */
    //virtual void(void) InitBrushTrigger;
    //virtual void(void) InitPointTrigger;
    virtual void InitBrushTrigger();
    virtual void InitPointTrigger();

    //
    // Other base entity members. (These were old fields in edict_T back in the day.)
    //


    // Kill target when triggered.
    //std::string killTargetStr;
    
    // Message when triggered.
    //std::string messageStr;

    // Master trigger entity.
    //std::string masterStr;

    // Timestamp that the trigger has been called at.
    //
    // ServerEntity pointers.
    // 
    //// ServerEntity that activated this entity, NULL if none.
    ServerGameEntity* activatorEntity;
    //// Current active enemy, NULL if not any.    
    //ServerGameEntity* enemyEntity;
    //// Ground entity we're standing on.
    //ServerGameEntity* groundEntity;
    //// Old enemy, NULL if not any.
    //ServerGameEntity* oldEnemyEntity;
    //// Team Chain Pointer.
    //ServerGameEntity* teamChainEntity;
    //// Master Pointer.
    //ServerGameEntity* teamMasterEntity;

public:


protected:
    //
    // Callback function pointers.
    //
    //ThinkCallbackPointer        thinkFunction;
    //UseCallbackPointer          useFunction;
    //TouchCallbackPointer        touchFunction;
    //BlockedCallbackPointer      blockedFunction;
    //TakeDamageCallbackPointer   takeDamageFunction;
    //DieCallbackPointer          dieFunction;
};

#endif // __SVGAME_ENTITIES_BASE_CBASEENTITY_H__