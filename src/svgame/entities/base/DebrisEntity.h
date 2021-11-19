/*
// LICENSE HERE.

//
// DebrisServerEntity.h
//
// Base ServerEntity for debris.
//
*/
#ifndef __SVGAME_ENTITIES_BASE_DEBRISServerEntity_H__
#define __SVGAME_ENTITIES_BASE_DEBRISServerEntity_H__

class SVGBaseEntity;

class DebrisServerEntity : public SVGBaseEntity {
public:
    // Constructor/Deconstructor.
    DebrisServerEntity(ServerEntity* svServerEntity);
    virtual ~DebrisServerEntity();

    DefineClass(DebrisServerEntity, SVGBaseEntity);

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
    // DebrisServerEntity functions.
    // 
    void CalculateVelocity(SVGBaseEntity* other, const int32_t& damage);

    //
    // Callback functions.
    //
    //
    void DebrisServerEntityDie(SVGBaseEntity* inflictor, SVGBaseEntity* attacker, int damage, const vec3_t& point);
   
protected:

private:

};

#endif // __SVGAME_ENTITIES_BASE_DEBRISServerEntity_H__