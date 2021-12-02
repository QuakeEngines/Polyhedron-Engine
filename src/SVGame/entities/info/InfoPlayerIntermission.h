/*
// LICENSE HERE.

//
// InfoPlayerIntermission.h
//
//
*/
#pragma once

class SynchedEntityBase;
class InfoPlayerStart;

class InfoPlayerIntermission : public InfoPlayerStart {
public:
    // Constructor/Deconstructor.
    InfoPlayerIntermission(ServerEntity* svEntity);
    virtual ~InfoPlayerIntermission();

    DefineMapClassSelfConstruct( "info_player_intermission", InfoPlayerIntermission, InfoPlayerStart );

    // Interface functions. 
    void Precache() final;    // Precaches data.
    void Spawn() final;       // Spawns the entity.
    void PostSpawn() final;   // PostSpawning is for handling entity references, since they may not exist yet during a spawn period.
    void Think() final;       // General entity thinking routine.

    void SpawnKey(const std::string& key, const std::string& value)  override;

private:

};
