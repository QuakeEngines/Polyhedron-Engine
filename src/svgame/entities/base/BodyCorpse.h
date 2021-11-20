/*
// LICENSE HERE.

//
// BodyCorpse.h
//
// Class ServerEntity to accommodate body corpses with.
// These serve for client entities when they die, and go into the body queue.
//
*/
#ifndef __SVGAME_ENTITIES_BASE_BODYCORPSE_H__
#define __SVGAME_ENTITIES_BASE_BODYCORPSE_H__

class ServerGameEntity;

class BodyCorpse : public ServerGameEntity {
public:
    // Constructor/Deconstructor.
    BodyCorpse(ServerEntity* svServerEntity);
    virtual ~BodyCorpse();

    DefineClass(BodyCorpse, ServerGameEntity);

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
    //
    void BodyCorpseDie(ServerGameEntity* inflictor, ServerGameEntity* attacker, int damage, const vec3_t& point);
    void BodyCorpseTouch(ServerGameEntity* self, ServerGameEntity* other, cplane_t* plane, csurface_t* surf);

    //
    // Get/Set
    //


protected:

private:

};

#endif // __SVGAME_ENTITIES_BASE_BODYCORPSE_H__