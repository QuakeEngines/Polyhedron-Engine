/*
// LICENSE HERE.

//
// TriggerDelayedUse.h
//
// Trigger that is used for delayed use callback firing.
//
*/
#ifndef __SVGAME_ENTITIES_TRIGGER_TRIGGERDELAYEDUSE_H__
#define __SVGAME_ENTITIES_TRIGGER_TRIGGERDELAYEDUSE_H__

class TriggerDelayedUse : public SVGBaseTrigger {
public:
    //
    // Constructor/Deconstructor.
    //
    TriggerDelayedUse(ServerEntity* svServerEntity);
    virtual ~TriggerDelayedUse();

    DefineClass( TriggerDelayedUse, SVGBaseTrigger );

    //
    // Interface functions. 
    //
    void Precache() override;    // Precaches data.
    void Spawn() override;       // Spawns the ServerEntity.
    void Respawn() override;     // Respawns the ServerEntity.
    void PostSpawn() override;   // PostSpawning is for handling ServerEntity references, since they may not exist yet during a spawn period.
    void Think() override;       // General ServerEntity thinking routine.

    void SpawnKey(const std::string& key, const std::string& value)  override;

    //
    // Callback functions.
    //
    void TriggerDelayedUseThink(void);

    //
    // Get/Set
    // 

protected:
    //
    // Other base ServerEntity members. (These were old fields in edict_T back in the day.)
    //
    // The time this ServerEntity has last been hurting anyone else. It is used for the slow damage flag.
    //float lastHurtTime;

    //
    // ServerEntity pointers.
    // 

public:

};

#endif // __SVGAME_ENTITIES_TRIGGER_TRIGGERDELAYEDUSE_H__