/*
// LICENSE HERE.

//
// BodyCorpse.h
//
// Class entity to accommodate body corpses with.
// These serve for client entities when they die, and go into the body queue.
//
*/
#ifndef __SVGAME_ENTITIES_BASE_BODYCORPSE_H__
#define __SVGAME_ENTITIES_BASE_BODYCORPSE_H__

class SynchedBasedEntity ;

class BodyCorpse : public SynchedBasedEntity {
public:
    // Constructor/Deconstructor.
    BodyCorpse(ServerEntity* svEntity);
    virtual ~BodyCorpse();

    DefineClass(BodyCorpse, SynchedBasedEntity, ServerGameEntity);

    //
    // Interface functions. 
    //
    void Precache() final;    // Precaches data.
    void Spawn() final;       // Spawns the entity.
    void Respawn() final;     // Respawns the entity.
    void PostSpawn() final;   // PostSpawning is for handling entity references, since they may not exist yet during a spawn period.
    void Think() final;       // General entity thinking routine.

    void SpawnKey(const std::string& key, const std::string& value) final;

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