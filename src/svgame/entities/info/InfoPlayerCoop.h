/*
// LICENSE HERE.

//
// InfoPlayerCoop.h
//
//
*/
#pragma once

class ServerGameEntity;
class InfoPlayerStart;

class InfoPlayerCoop : public InfoPlayerStart {
public:
    // Constructor/Deconstructor.
    InfoPlayerCoop(ServerEntity* svServerEntity);
    virtual ~InfoPlayerCoop();

    DefineMapClass( "info_player_coop", InfoPlayerCoop, InfoPlayerStart );

    // Interface functions. 
    void Precache();    // Precaches data.
    void Spawn();       // Spawns the ServerEntity.
    void PostSpawn();   // PostSpawning is for handling ServerEntity references, since they may not exist yet during a spawn period.
    void Think();       // General ServerEntity thinking routine.

    void SpawnKey(const std::string& key, const std::string& value)  override;

private:

};