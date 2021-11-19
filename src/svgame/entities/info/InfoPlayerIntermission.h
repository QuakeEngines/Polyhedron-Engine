/*
// LICENSE HERE.

//
// InfoPlayerIntermission.h
//
//
*/
#pragma once

class SVGBaseEntity;
class InfoPlayerStart;

class InfoPlayerIntermission : public InfoPlayerStart {
public:
    // Constructor/Deconstructor.
    InfoPlayerIntermission(ServerEntity* svServerEntity);
    virtual ~InfoPlayerIntermission();

    DefineMapClass( "info_player_intermission", InfoPlayerIntermission, InfoPlayerStart );

    // Interface functions. 
    void Precache();    // Precaches data.
    void Spawn();       // Spawns the ServerEntity.
    void PostSpawn();   // PostSpawning is for handling ServerEntity references, since they may not exist yet during a spawn period.
    void Think();       // General ServerEntity thinking routine.

    void SpawnKey(const std::string& key, const std::string& value)  override;

private:

};
