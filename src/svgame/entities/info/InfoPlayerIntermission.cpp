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
#include "../base/SynchedEntityBase.h.h"

#include "InfoPlayerStart.h"
#include "InfoPlayerIntermission.h"


// Constructor/Deconstructor.
InfoPlayerIntermission::InfoPlayerIntermission(ServerEntity* svEntity) 
    : InfoPlayerStart(svEntity) {

}
InfoPlayerIntermission::~InfoPlayerIntermission() {

}

// Interface functions. 
//===============
// InfoPlayerStart::Precache
//
//===============
void InfoPlayerIntermission::Precache() {
    Base::Precache();
}

//===============
// InfoPlayerStart::Spawn
//
//===============
void InfoPlayerIntermission::Spawn() {
    Base::Spawn();
}

//===============
// InfoPlayerIntermission::PostSpawn
//
//===============
void InfoPlayerIntermission::PostSpawn() {
    Base::PostSpawn();
}

//===============
// InfoPlayerIntermission::Think
//
//===============
void InfoPlayerIntermission::Think() {
    // Parent think.
    Base::Think();
}

//===============
// InfoPlayerIntermission::SpawnKey
//
//===============
void InfoPlayerIntermission::SpawnKey(const std::string& key, const std::string& value) {
    Base::SpawnKey(key, value);
}
