/*
// LICENSE HERE.

//
// InfoPlayerStart.h
//
//
*/
#pragma once

class ServerGameEntity;

class InfoPlayerStart : public ServerGameEntity {
public:
    // Constructor/Deconstructor.
    InfoPlayerStart(ServerEntity* svEntity);
    virtual ~InfoPlayerStart();

    DefineMapClass( "info_player_start", InfoPlayerStart, ServerGameEntity );

    // Interface functions. 
    void Precache();    // Precaches data.
    void Spawn();       // Spawns the entity.
    void PostSpawn();   // PostSpawning is for handling entity references, since they may not exist yet during a spawn period.
    void Think();       // General entity thinking routine.

    void SpawnKey(const std::string& key, const std::string& value)  override;

private:

};
