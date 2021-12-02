/*
// LICENSE HERE.

//
// InfoPlayerStart.h
//
//
*/
#pragma once

struct ServerEntity;
class EntityBase;
class SynchedEntityBase;

class InfoPlayerStart : public SynchedEntityBase {
public:
    // Constructor/Deconstructor.
    InfoPlayerStart(ServerEntity* svEntity);
    virtual ~InfoPlayerStart();

    DefineMapClassSelfConstruct( "info_player_start", InfoPlayerStart, SynchedEntityBase);

    // Interface functions. 
    void Precache();    // Precaches data.
    void Spawn();       // Spawns the entity.
    void PostSpawn();   // PostSpawning is for handling entity references, since they may not exist yet during a spawn period.
    void Think();       // General entity thinking routine.

    void SpawnKey(const std::string& key, const std::string& value)  override;

private:

};
