/*
// LICENSE HERE.

//
// DebrisServerEntity.cpp
//
//
*/
#include "../../g_local.h"              // SVGame.
#include "../../effects.h"              // Effects.
#include "../../entities.h"             // Entities.
#include "../../player/client.h"        // Player Client functions.
#include "../../player/animations.h"    // Include Player Client Animations.
#include "../../player/view.h"          // Include Player View functions..
#include "../../utils.h"                // Util funcs.

// Class Entities.
#include "../base/ServerGameEntity.h"
#include "DebrisServerEntity.h"

// Constructor/Deconstructor.
DebrisServerEntity::DebrisServerEntity(ServerEntity* svServerEntity)
    : ServerGameEntity(svServerEntity) {

}
DebrisServerEntity::~DebrisServerEntity() {

}

//
//===============
// PlayerClient::Precache
//
//===============
//
void DebrisServerEntity::Precache() {
    Base::Precache();
}

//
//===============
// PlayerClient::Spawn
//
//===============
//
void DebrisServerEntity::Spawn() {
    // Spawn.
    Base::Spawn();
}

//
//===============
// DebrisServerEntity::Respawn
//
//===============
//
void DebrisServerEntity::Respawn() {
    Base::Respawn();
}

//
//===============
// DebrisServerEntity::PostSpawn
//
//===============
//
void DebrisServerEntity::PostSpawn() {
    Base::PostSpawn();
}

//
//===============
// DebrisServerEntity::Think
//
//===============
//
void DebrisServerEntity::Think() {
    // Parent class Think.
    Base::Think();
}

//===============
// DebrisServerEntity::SpawnKey
//
// DebrisServerEntity spawn key handling.
//===============
void DebrisServerEntity::SpawnKey(const std::string& key, const std::string& value) {
    // Parent class spawnkey.
    Base::SpawnKey(key, value);
}

//===============
// DebrisServerEntity::DebrisServerEntityDie
//
// Spawn gibs to make things gore like :P
//===============
void DebrisServerEntity::DebrisServerEntityDie(ServerGameEntity* inflictor, ServerGameEntity* attacker, int damage, const vec3_t& point) {
    // Save to queue for removal.
    Remove();
}