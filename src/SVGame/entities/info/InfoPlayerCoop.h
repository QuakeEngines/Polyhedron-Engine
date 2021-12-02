/*
// LICENSE HERE.

//
// InfoPlayerCoop.h
//
//
*/
#pragma once

struct ServerEntity;
class EntityBase;
class SynchedEntityBase;
class InfoPlayerStart;

class InfoPlayerCoop : public InfoPlayerStart {
public:
    // Constructor/Deconstructor.
    InfoPlayerCoop(ServerEntity* svEntity);
    virtual ~InfoPlayerCoop();

    DefineMapClassSelfConstruct( "info_player_coop", InfoPlayerCoop, InfoPlayerStart );

    // Interface functions. 
    void Precache();    // Precaches data.
    void Spawn();       // Spawns the entity.
    void PostSpawn();   // PostSpawning is for handling entity references, since they may not exist yet during a spawn period.
    void Think();       // General entity thinking routine.

    void SpawnKey(const std::string& key, const std::string& value)  override;

private:

};