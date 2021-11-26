/*
// LICENSE HERE.

//
// BlasterBolt.h
//
//
*/
#pragma once

struct ServerEntity;
class ServerGameEntity;
class SynchedEntityBase;

class BlasterBolt : public ServerGameEntity {
public:
    // Constructor/Deconstructor.
    BlasterBolt();
    virtual ~BlasterBolt();

    DefineClass( BlasterBolt, ServerGameEntity);

    //
    // Interface functions. 
    //
    void Precache() override;    // Precaches data.
    void Spawn() override;       // Spawns the entity.
    void Respawn() override;     // Respawns the entity.
    void PostSpawn() override;   // PostSpawning is for handling entity references, since they may not exist yet during a spawn period.
    void Think() override;       // General entity thinking routine.

    void SpawnKey(const std::string& key, const std::string& value)  override;

    //
    // Callback functions.
    //
    //
    void BlasterBoltTouch(ServerGameEntity* self, ServerGameEntity* other, cplane_t* plane, csurface_t* surf);

    //
    // Get/Set
    //
    

protected:

private:

};