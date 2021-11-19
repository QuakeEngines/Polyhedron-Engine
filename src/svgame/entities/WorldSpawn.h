/*
// LICENSE HERE.

//
// WorldSpawn.h
//
// WorldSpawn ServerEntity definition.
//
*/
#ifndef __SVGAME_ENTITIES_WORLDSPAWN_H__
#define __SVGAME_ENTITIES_WORLDSPAWN_H__

class SVGBaseEntity;

class WorldSpawn : public SVGBaseEntity {
public:
    // Constructor/Deconstructor.
    WorldSpawn(ServerEntity* svServerEntity);
    virtual ~WorldSpawn();

    DefineMapClass( "worldspawn", WorldSpawn, SVGBaseEntity );

    //
    // Interface functions. 
    //
    void Precache() override;    // Precaches data.
    void Spawn() override;       // Spawns the ServerEntity.
    void PostSpawn() override;   // PostSpawning is for handling ServerEntity references, since they may not exist yet during a spawn period.
    void Think() override;       // General ServerEntity thinking routine.

    void SpawnKey(const std::string& key, const std::string& value) override;

    //
    // Callback functions.
    //
    void WorldSpawnThink(void);

private:

};

#endif // __SVGAME_ENTITIES_WORLDSPAWN_H__