/*
// LICENSE HERE.

//
// BaseTrigger.cpp
//
//
*/
#include "../../ServerGameLocal.h"		// SVGame.
#include "../../Effects.h"		// Effects.
#include "../../Entities.h"		// Entities.
#include "../../Utilities.h"		// Util funcs.

// Class Entities.
#include "SynchedEntityBase.h"
#include "BaseTrigger.h"

// Included for delayed use.
#include "../trigger/TriggerDelayedUse.h"

// Constructor/Deconstructor.
BaseTrigger::BaseTrigger() : SynchedEntityBase() {
	//
	// All callback functions best be nullptr.
	//
	//thinkFunction = nullptr;


	//
	// Set all entity pointer references to nullptr.
	//
	activatorEntity = nullptr;
	//activatorEntity = nullptr;
	//enemyEntity = nullptr;
	//groundEntity = nullptr;
	//oldEnemyEntity = nullptr;
	//teamChainEntity = nullptr;
	//teamMasterEntity = nullptr;

	//
	// Default values for members.
	//


	//moveType = MoveType::None;

	//// Velocity.
	//velocity = vec3_zero();
	//angularVelocity = vec3_zero();
	//mass = 0;
	//groundEntityLinkCount = 0;
	//health = 0;
	//maxHealth = 0;
	//deadFlag = DEAD_NO;
}

// Interface functions. 
//
//===============
// BaseTrigger::Precache
//
//===============
//
void BaseTrigger::Precache() {
	Base::Precache();
}

//
//===============
// BaseTrigger::Spawn
//
//===============
//
void BaseTrigger::Spawn() {
	Base::Spawn();
}

//
//===============
// BaseTrigger::Respawn
// 
//===============
//
void BaseTrigger::Respawn() {
	Base::Respawn();
}

//
//===============
// BaseTrigger::PostSpawn
// 
//===============
//
void BaseTrigger::PostSpawn() {
	Base::PostSpawn();
}

//
//===============
// BaseTrigger::Think
//
//===============
//
void BaseTrigger::Think() {
	Base::Think();
}

//
//===============
// BaseTrigger::InitBrushTrigger
//
//===============
//
void BaseTrigger::InitBrushTrigger() {
	SetModel(GetModel());
	SetMoveType(MoveType::None);
	SetSolid(Solid::Trigger);
	
	SetServerFlags(EntityServerFlags::NoClient);
}

//
//===============
// BaseTrigger::InitPointTrigger
//
//===============
//
void BaseTrigger::InitPointTrigger() {
	const vec3_t HULL_MINS = { -16.f, -16.f, -36.f };
	const vec3_t HULL_MAXS = { 16.f,  16.f,  36.f };

	SetSize(HULL_MINS + HULL_MAXS);
	SetMoveType(MoveType::None);
	SetSolid(Solid::Trigger);

	// Ensure we got the proper no client flags.
	SetServerFlags(EntityServerFlags::NoClient);
}

//
//===============
// BaseTrigger::SpawnKey
//
//===============
//
void BaseTrigger::SpawnKey(const std::string& key, const std::string& value) {
	// Wait.
	if (key == "wait") {
		// Parsed float.
		float parsedFloat = 0.f;

		// Parse.
		ParseFloatKeyValue(key, value, parsedFloat);

		// Assign.
		SetWaitTime(parsedFloat);
	}
	// Parent class spawnkey.
	else {
		Base::SpawnKey(key, value);
	}
}

//
//===============
// BaseTrigger::UseTargets
//
// The activator is the entity who is initiating the firing. If not set as
// a function argument, it will use whichever is set in the entity itself.
//
// If self.delay is set, a DelayedUse entity will be created that will actually
// do the SUB_UseTargets after that many seconds have passed.
//
// Centerprints any self.message to the activator.
//
// Search for (string)targetName in all entities that (string)target and
// calls their Use function.
//===============
//
void BaseTrigger::UseTargets(SynchedEntityBase * activator) {
	//
	// Check for a delay
	//
    if (GetDelayTime()) {
		// Create a temporary DelayedTrigger entity, to fire at a latter time.
	    BaseTrigger *triggerDelay = SVG_CreateClassEntity<TriggerDelayedUse>();
		if (!activator)
			gi.DPrintf("TriggerDelayThink with no activator\n");
		triggerDelay->SetActivator(activator);
		triggerDelay->SetMessage(GetMessage());
		triggerDelay->SetTarget(GetTarget());
		triggerDelay->SetKillTarget(GetKillTarget());
		triggerDelay->SetNextThinkTime(level.time + GetDelayTime());
		triggerDelay->SetThinkCallback(&TriggerDelayedUse::TriggerDelayedUseThink);

		// Return, the rest happens by delay.
		return;
	}
	
	//
	// Print the "message"
	//
	if (GetMessage().length() && !(activator->GetServerFlags() & EntityServerFlags::Monster)) {
		// Fetch noise index.
		int32_t noiseIndex = GetNoiseIndex();

		// Print the message.
		SVG_CenterPrint(activator, GetMessage());

		// Play specific noise sound, in case one is set. Default talk1.wav otherwise.
		if (noiseIndex) {
			SVG_Sound(activator, CHAN_AUTO, noiseIndex, 1, ATTN_NORM, 0);
		} else {
			SVG_Sound(activator, CHAN_AUTO, gi.SoundIndex("misc/talk1.wav"), 1, ATTN_NORM, 0);
		}
	}

	//
	// Kill killtargets
	//
	if (GetKillTarget().length()) {
		SynchedEntityBase * triggerEntity = nullptr;

		//while (triggerEntity = SVG_FindEntityByKeyValue("targetname", GetKillTarget(), triggerEntity))
		// Loop over the total entity range, ensure that we're checking for the right filters.
		for (auto* triggerEntity : GetGameEntityRange<0, MAX_EDICTS>()
			| SvgEF::HasKeyValue("targetname", GetKillTarget())) {

			// It is going to die, set it up for removal.
			//SVG_FreeEntity(triggerEntity->GetEntityServerHandle());
			triggerEntity->Remove();
		}
	}
	
	//
	// Fire targets
	//
	if (GetTarget().length()) {
		// Loop over the total entity range, ensure that we're checking for the right filters.
		for (auto* triggerEntity : GetGameEntityRange<0, MAX_EDICTS>()
			| SvgEF::HasKeyValue("targetname", GetTarget())) {
			
			// Doors fire area portals in a special way. So we skip those.
			if (triggerEntity->GetClassName() == "func_areaportal"
				&& (GetClassName() == "func_door" || GetClassName() == "func_door_rotating")) {
				continue;
			}

			// Do not ALLOW an entity to use ITSELF. :)
			if (triggerEntity == this) {
				gi.DPrintf("WARNING: '%s' tried to use itself #%i.\n", GetTypeInfo()->className, GetEntityServerHandle()->state.number);
			} else {
				triggerEntity->Use(this, activator);
			}

			// Make sure it is in use, if not, debug.
			if (!triggerEntity->IsInUse()) {
                gi.DPrintf("WARNING: ServerEntity #%i was removed while using targets\n", GetEntityServerHandle()->state.number);
                return;
			}
		}
	}
}