/*
// LICENSE HERE.

//
// PlayerStart.cpp
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
#include "InfoPlayerCoop.h"

// Constructor/Deconstructor.
InfoPlayerCoop::InfoPlayerCoop(ServerEntity* svEntity) 
    : InfoPlayerStart(svEntity) {

}
InfoPlayerCoop::~InfoPlayerCoop() {

}

// Interface functions. 
//===============
// InfoPlayerStart::Precache
//
//===============
void InfoPlayerCoop::Precache() {
    Base::Precache();
}

//===============
// InfoPlayerStart::Spawn
//
//===============
void InfoPlayerCoop::Spawn() {
    Base::Spawn();
}

//===============
// InfoPlayerCoop::PostSpawn
//
//===============
void InfoPlayerCoop::PostSpawn() {
    Base::PostSpawn();
}

//===============
// InfoPlayerCoop::Think
//
//===============
void InfoPlayerCoop::Think() {
    // Parent think.
    Base::Think();
}

//===============
// InfoPlayerCoop::SpawnKey
//
//===============
void InfoPlayerCoop::SpawnKey(const std::string& key, const std::string& value) {
    Base::SpawnKey(key, value);
}
