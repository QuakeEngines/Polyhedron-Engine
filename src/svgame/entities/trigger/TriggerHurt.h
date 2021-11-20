/*
// LICENSE HERE.

//
// TriggerHurt.h
//
// Trigger Hurt brush ServerEntity.
//
*/
#ifndef __SVGAME_ENTITIES_TRIGGER_TRIGGERHURT_H__
#define __SVGAME_ENTITIES_TRIGGER_TRIGGERHURT_H__

class TriggerHurt : public SVGBaseTrigger {
public:
    //
    // Constructor/Deconstructor.
    //
    TriggerHurt(ServerEntity* svServerEntity);
    virtual ~TriggerHurt();

    DefineMapClass( "trigger_hurt", TriggerHurt, SVGBaseTrigger );

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
    // Trigger functions.
    //

    // Callback functions.
    void TriggerHurtTouch(ServerGameEntity* self, ServerGameEntity* other, cplane_t* plane, csurface_t* surf);
    void TriggerHurtUse(ServerGameEntity* other, ServerGameEntity* activator);

    //
    // Get/Set
    // 

protected:
    //
    // Other base ServerEntity members. (These were old fields in edict_t back in the day.)
    //
    // The time this ServerEntity has last been hurting anyone else. It is used for the slow damage flag.
    float lastHurtTime;

    //
    // ServerEntity pointers.
    // 

public:

};

#endif // __SVGAME_ENTITIES_TRIGGER_TRIGGERHURT_H__