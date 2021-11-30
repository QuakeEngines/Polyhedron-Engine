/*
// LICENSE HERE.

//
// GibEntity.h
//
// Base entity for gibs.
//
*/
#pragma once


struct ServerEntity;
class SynchedEntityBase.h;
class SynchedEntityBase;

class GibEntity : public SynchedEntityBase {
public:
    // Constructor/Deconstructor.
    GibEntity(SynchedEntityBase* svEntity);
    virtual ~GibEntity();

    DefineMapClassSelfConstruct("GibEntity", SynchedEntityBase, SynchedEntityBase);

    //
    // Interface functions. 
    //
    virtual void Precache() final;    // Precaches data.
    virtual void Spawn() final;       // Spawns the entity.
    virtual void Respawn() final;     // Respawns the entity.
    virtual void PostSpawn() final;   // PostSpawning is for handling entity references, since they may not exist yet during a spawn period.
    virtual void Think() final;       // General entity thinking routine.

    virtual void SpawnKey(const std::string& key, const std::string& value)  final;

    //
    // GibEntity functions.
    // 
    // WID: These need more restructuring etc, rethinking. Doing a KISS rewrite atm ;-)
    // 
    // Can be used to clip the gib velocity.
    void ClipGibVelocity(vec3_t& velocity);

    //
    // Callback functions.
    //
    //
    void GibEntityThink();
    void GibEntityDie(SynchedEntityBase * inflictor, SynchedEntityBase * attacker, int damage, const vec3_t& point);
    void GibEntityTouch(SynchedEntityBase * self, SynchedEntityBase * other, cplane_t* plane, csurface_t* surf);

protected:

private:

};
