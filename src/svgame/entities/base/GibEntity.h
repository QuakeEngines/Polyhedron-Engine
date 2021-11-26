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
class ServerGameEntity;
class SynchedEntityBase;

class GibEntity : public ServerGameEntity  {
public:
    // Constructor/Deconstructor.
    GibEntity(ServerGameEntity * svEntity);
    virtual ~GibEntity();

    DefineMapClassSelfConstruct("GibEntity", SynchedEntityBase, ServerGameEntity);

    //
    // Interface functions. 
    //
    void Precache() final;    // Precaches data.
    void Spawn() final;       // Spawns the entity.
    void Respawn() final;     // Respawns the entity.
    void PostSpawn() final;   // PostSpawning is for handling entity references, since they may not exist yet during a spawn period.
    void Think() final;       // General entity thinking routine.

    void SpawnKey(const std::string& key, const std::string& value)  final;

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
    void GibEntityDie(ServerGameEntity* inflictor, ServerGameEntity* attacker, int damage, const vec3_t& point);
    void GibEntityTouch(ServerGameEntity* self, ServerGameEntity* other, cplane_t* plane, csurface_t* surf);

protected:

private:

};
