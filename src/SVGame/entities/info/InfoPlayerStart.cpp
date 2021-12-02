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


// Constructor/Deconstructor.
InfoPlayerStart::InfoPlayerStart(ServerEntity *serverEntity) 
    : SynchedEntityBase(serverEntity) {

}
InfoPlayerStart::~InfoPlayerStart() {

}

// Interface functions. 
//===============
// InfoPlayerStart::Precache
//
//===============
void InfoPlayerStart::Precache() {
    Base::Precache();
}

//===============
// InfoPlayerStart::Spawn
//
//===============
void InfoPlayerStart::Spawn() {
    Base::Spawn();
}

//===============
// InfoPlayerStart::PostSpawn
//
//===============
void InfoPlayerStart::PostSpawn() {
    Base::PostSpawn();
}

//===============
// InfoPlayerStart::Think
//
//===============
void InfoPlayerStart::Think() {
    // Parent think.
    Base::Think();
}

//===============
// InfoPlayerStart::SpawnKey
//
//===============
void InfoPlayerStart::SpawnKey(const std::string& key, const std::string& value) {
    Base::SpawnKey(key, value);
}
