/*
// LICENSE HERE.

//
// PlayerStart.cpp
//
//
*/
// Common Includes.
#include "../../g_local.h"
#include "../../effects.h"
#include "../../entities.h"
#include "../../utils.h"
#include "../../brushfuncs.h"

// Class Entities.
#include "../base/ServerGameEntity.h"

#include "InfoPlayerStart.h"


// Constructor/Deconstructor.
InfoPlayerStart::InfoPlayerStart(ServerEntity* svEntity) 
    : ServerGameEntity(svEntity) {

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
