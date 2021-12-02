/*
// LICENSE HERE.

//
// InfoPlayerDeathmatch.cpp
//
//
*/
// Common Includes.
#include "../../ServerGameLocal.h"
#include "../../Effects.h"
#include "../../Entities.h"
#include "../../Utilities.h"

// Class Entities.
#include "../Base/SynchedEntityBase.h"

#include "InfoPlayerStart.h"
#include "InfoPlayerDeathMatch.h"


// Constructor/Deconstructor.
InfoPlayerDeathmatch::InfoPlayerDeathmatch(ServerEntity* svEntity) 
    : InfoPlayerStart(svEntity) {

}
InfoPlayerDeathmatch::~InfoPlayerDeathmatch() {

}

// Interface functions. 
//===============
// InfoPlayerDeathmatch::Precache
//
//===============
void InfoPlayerDeathmatch::Precache() {
    Base::Precache();
}

//===============
// InfoPlayerDeathmatch::Spawn
//
//===============
void InfoPlayerDeathmatch::Spawn() {
    Base::Spawn();
}

//===============
// InfoPlayerDeathmatch::PostSpawn
//
//===============
void InfoPlayerDeathmatch::PostSpawn() {
    Base::PostSpawn();
}

//===============
// InfoPlayerDeathmatch::Think
//
//===============
void InfoPlayerDeathmatch::Think() {
    // Parent think.
    Base::Think();
}

//===============
// InfoPlayerDeathmatch::SpawnKey
//
//===============
void InfoPlayerDeathmatch::SpawnKey(const std::string& key, const std::string& value) {
    Base::SpawnKey(key, value);
}
