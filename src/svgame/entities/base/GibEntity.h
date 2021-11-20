/*
// LICENSE HERE.

//
// GibServerEntity.h
//
// Base ServerEntity for gibs.
//
*/
#ifndef __SVGAME_ENTITIES_BASE_GIBServerEntity_H__
#define __SVGAME_ENTITIES_BASE_GIBServerEntity_H__

class ServerGameEntity;

class GibServerEntity : public ServerGameEntity {
public:
    // Constructor/Deconstructor.
    GibServerEntity(ServerEntity* svServerEntity);
    virtual ~GibServerEntity();

    DefineClass(GibServerEntity, ServerGameEntity);

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
    // GibServerEntity functions.
    // 
    // WID: These need more restructuring etc, rethinking. Doing a KISS rewrite atm ;-)
    // 
    // Can be used to clip the gib velocity.
    void ClipGibVelocity(vec3_t& velocity);

    //
    // Callback functions.
    //
    //
    void GibServerEntityThink();
    void GibServerEntityDie(ServerGameEntity* inflictor, ServerGameEntity* attacker, int damage, const vec3_t& point);
    void GibServerEntityTouch(ServerGameEntity* self, ServerGameEntity* other, cplane_t* plane, csurface_t* surf);

protected:

private:

};

#endif // __SVGAME_ENTITIES_BASE_GIBServerEntity_H__