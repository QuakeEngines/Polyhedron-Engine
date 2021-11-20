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
    SVGBaseTrigger(ServerEntity* svServerEntity);
    virtual ~SVGBaseTrigger();

    DefineAbstractClass( SVGBaseTrigger, ServerGameEntity );

    //
    // Interface functions. 
    //
    virtual void Precache() override;    // Precaches data.
    virtual void Spawn() override;       // Spawns the ServerEntity.
    virtual void Respawn() override;     // Respawns the ServerEntity.
    virtual void PostSpawn() override;   // PostSpawning is for handling ServerEntity references, since they may not exist yet during a spawn period.
    virtual void Think() override;       // General ServerEntity thinking routine.

    virtual void SpawnKey(const std::string& key, const std::string& value)  override;

    //
    // Trigger functions.
    //
    void UseTargets(ServerGameEntity* activator);

    //
    // Get/Set
    // 
    // Return the 'activatorServerEntity' ServerEntity pointer.
    ServerGameEntity* GetActivator() {
        return activatorServerEntity;
    }

    //
    // ServerEntity Set Functions.
    //
    // Set the 'activatorServerEntity' pointer.
    inline void SetActivator(ServerGameEntity* activator) {
        this->activatorServerEntity = activator;
    }

protected:
    /* legacy trigger architecture */
    //float m_flDelay;
    //virtual void(ServerEntity, int) Trigger;
    //virtual void(ServerEntity, int, float) UseTargets;

    ///* master feature */
    //virtual int(void) GetValue;
    //virtual int(void) GetMaster;

    ///* spawn setup helpers */
    //virtual void(void) InitBrushTrigger;
    //virtual void(void) InitPointTrigger;
    virtual void InitBrushTrigger();
    virtual void InitPointTrigger();

    //
    // Other base ServerEntity members. (These were old fields in edict_T back in the day.)
    //


    // Kill target when triggered.
    //std::string killTargetStr;
    
    // Message when triggered.
    //std::string messageStr;

    // Master trigger ServerEntity.
    //std::string masterStr;

    // Timestamp that the trigger has been called at.
    //
    // ServerEntity pointers.
    // 
    //// ServerEntity that activated this ServerEntity, NULL if none.
    ServerGameEntity* activatorServerEntity;
    //// Current active enemy, NULL if not any.    
    //ServerGameEntity* enemyServerEntity;
    //// Ground ServerEntity we're standing on.
    //ServerGameEntity* groundServerEntity;
    //// Old enemy, NULL if not any.
    //ServerGameEntity* oldEnemyServerEntity;
    //// Team Chain Pointer.
    //ServerGameEntity* teamChainServerEntity;
    //// Master Pointer.
    //ServerGameEntity* teamMasterServerEntity;

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

#endif // __SVGAME_ENTITIES_BASE_CBASEServerEntity_H__