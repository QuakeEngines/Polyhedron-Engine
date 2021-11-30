/*
// LICENSE HERE.

//
// BlasterBolt.h
//
//
*/
#pragma once

struct ServerEntity;
class EntityBase;
class SynchedEntityBase;

class BlasterBolt : public SynchedEntityBase{
public:
    // Constructor/Deconstructor.
    BlasterBolt();
    virtual ~BlasterBolt();

    DefineClass( BlasterBolt, SynchedEntityBase );

    //
    // Interface functions. 
    //
    virtual void Precache() override;    // Precaches data.
    virtual void Spawn() override;       // Spawns the entity.
    virtual void Respawn() override;     // Respawns the entity.
    virtual void PostSpawn() override;   // PostSpawning is for handling entity references, since they may not exist yet during a spawn period.
    virtual void Think() override;       // General entity thinking routine.

    virtual void SpawnKey(const std::string& key, const std::string& value)  override;

    //
    // Callback functions.
    //
    //
    void BlasterBoltTouch(SynchedEntityBase * self, SynchedEntityBase * other, cplane_t* plane, csurface_t* surf);

    //
    // Get/Set
    //
    

protected:

private:

};