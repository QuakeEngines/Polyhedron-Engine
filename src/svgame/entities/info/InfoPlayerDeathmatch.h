/*
// LICENSE HERE.

//
// InfoPlayerDeathmatch.h
//
//
*/
#pragma once

class ServerGameEntity;
class InfoPlayerStart;

class InfoPlayerDeathmatch : public InfoPlayerStart {
public:
    // Constructor/Deconstructor.
    InfoPlayerDeathmatch(ServerEntity* svServerEntity);
    virtual ~InfoPlayerDeathmatch();

    DefineMapClass( "info_player_deathmatch", InfoPlayerDeathmatch, InfoPlayerStart );

    // Interface functions. 
    void Precache();    // Precaches data.
    void Spawn();       // Spawns the ServerEntity.
    void PostSpawn();   // PostSpawning is for handling ServerEntity references, since they may not exist yet during a spawn period.
    void Think();       // General ServerEntity thinking routine.

    void SpawnKey(const std::string& key, const std::string& value)  override;

private:

};