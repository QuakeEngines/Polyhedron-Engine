/*
// LICENSE HERE.

//
// TriggerAlways.cpp
//
// This trigger will always fire.  It is activated by the world.
//
*/
#include "../../ServerGameLocal.h"     // SVGame.
#include "../../Effects.h"     // Effects.
#include "../../Utilities.h"       // Util funcs.
#include "../base/SynchedEntityBase.h"
#include "../base/BaseTrigger.h"
#include "TriggerAlways.h"

//
// Spawn Flags.
// 

// Constructor/Deconstructor.
TriggerAlways::TriggerAlways(ServerEntity* svEntity) : BaseTrigger(svEntity) {
	//
	// All callback functions best be nullptr.
	//

	//
	// Set all entity pointer references to nullptr.
	//

	//
	// Default values for members.
	//
	//lastHurtTime = 0.f;
}
TriggerAlways::~TriggerAlways() {

}

// Interface functions. 
//
//===============
// TriggerAlways::Precache
//
//===============
//
void TriggerAlways::Precache() {
	Base::Precache();
}

//
//===============
// TriggerAlways::Spawn
//
//===============
//
void TriggerAlways::Spawn() {
	// Spawn base trigger.
	Base::Spawn();

	// Initialize Brush Trigger.
	InitPointTrigger();

	
	//self->noiseIndex = gi.SoundIndex("world/electro.wav");
	SetTouchCallback(&TriggerAlways::TriggerAlwaysTouch);

	// In case the entity can be "used", set it to hurt those who use it as well.
	SetUseCallback(&TriggerAlways::TriggerAlwaysUse);

	gi.DPrintf("TriggerHurt::Spawn!\n");
	LinkEntity();
}

//
//===============
// TriggerAlways::Respawn
// 
//===============
//
void TriggerAlways::Respawn() {
	Base::Respawn();
}

//
//===============
// TriggerAlways::PostSpawn
// 
//===============
//
void TriggerAlways::PostSpawn() {
	Base::PostSpawn();
}

//
//===============
// TriggerAlways::Think
//
//===============
//
void TriggerAlways::Think() {
	Base::Think();
}

void TriggerAlways::SpawnKey(const std::string& key, const std::string& value) {
	// Parent class spawnkey.
	// We don't want it to reposition this fucker.?
	Base::SpawnKey(key, value);
}

//
//===============
// TriggerAlways::TriggerAlwaysTouch
//
// 'Touch' callback, to hurt the entities touching it.
//===============
//
void TriggerAlways::TriggerAlwaysTouch(SynchedEntityBase * self, SynchedEntityBase * other, cplane_t* plane, csurface_t* surf) {
	if (this == other)
		return;

	gi.DPrintf("TriggerAlwaysTouch!\n");
}

//
//===============
// TriggerAlways::TriggerAlwaysUse
//
// 'Use' callback, to trigger it on/off.
//===============
//
void TriggerAlways::TriggerAlwaysUse(SynchedEntityBase * other, SynchedEntityBase * activator) {

}