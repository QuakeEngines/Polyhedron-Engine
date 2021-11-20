/*
// LICENSE HERE.

//
// SVGBaseTrigger.cpp
//
//
*/
#include "../../g_local.h"		// SVGame.
#include "../../effects.h"		// Effects.
#include "../../entities.h"		// Entities.
#include "../../utils.h"		// Util funcs.

// Class Entities.
#include "ServerGameEntity.h"
#include "SVGBaseTrigger.h"

// Included for delayed use.
#include "../trigger/TriggerDelayedUse.h"

// Constructor/Deconstructor.
SVGBaseTrigger::SVGBaseTrigger(ServerEntity* svServerEntity) : ServerGameEntity(svServerEntity) {
	//
	// All callback functions best be nullptr.
	//
	//thinkFunction = nullptr;


	//
	// Set all ServerEntity pointer references to nullptr.
	//
	activatorServerEntity = nullptr;
	//activatorServerEntity = nullptr;
	//enemyServerEntity = nullptr;
	//groundServerEntity = nullptr;
	//oldEnemyServerEntity = nullptr;
	//teamChainServerEntity = nullptr;
	//teamMasterServerEntity = nullptr;

	//
	// Default values for members.
	//


	//moveType = MoveType::None;

	//// Velocity.
	//velocity = vec3_zero();
	//angularVelocity = vec3_zero();
	//mass = 0;
	//groundServerEntityLinkCount = 0;
	//health = 0;
	//maxHealth = 0;
	//deadFlag = DEAD_NO;
}
SVGBaseTrigger::~SVGBaseTrigger() {

}

// Interface functions. 
//
//===============
// SVGBaseTrigger::Precache
//
//===============
//
void SVGBaseTrigger::Precache() {
	Base::Precache();
}

//
//===============
// SVGBaseTrigger::Spawn
//
//===============
//
void SVGBaseTrigger::Spawn() {
	Base::Spawn();
}

//
//===============
// SVGBaseTrigger::Respawn
// 
//===============
//
void SVGBaseTrigger::Respawn() {
	Base::Respawn();
}

//
//===============
// SVGBaseTrigger::PostSpawn
// 
//===============
//
void SVGBaseTrigger::PostSpawn() {
	Base::PostSpawn();
}

//
//===============
// SVGBaseTrigger::Think
//
//===============
//
void SVGBaseTrigger::Think() {
	Base::Think();
}

//
//===============
// SVGBaseTrigger::InitBrushTrigger
//
//===============
//
void SVGBaseTrigger::InitBrushTrigger() {
	SetModel(GetModel());
	SetMoveType(MoveType::None);
	SetSolid(Solid::Trigger);
	
	SetServerFlags(ServerEntityServerFlags::NoClient);
}

//
//===============
// SVGBaseTrigger::InitPointTrigger
//
//===============
//
void SVGBaseTrigger::InitPointTrigger() {
	const vec3_t HULL_MINS = { -16.f, -16.f, -36.f };
	const vec3_t HULL_MAXS = { 16.f,  16.f,  36.f };

	SetSize(HULL_MINS + HULL_MAXS);
	SetMoveType(MoveType::None);
	SetSolid(Solid::Trigger);

	// Ensure we got the proper no client flags.
	SetServerFlags(ServerEntityServerFlags::NoClient);
}

//
//===============
// SVGBaseTrigger::SpawnKey
//
//===============
//
void SVGBaseTrigger::SpawnKey(const std::string& key, const std::string& value) {
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
// SVGBaseTrigger::UseTargets
//
// The activator is the ServerEntity who is initiating the firing. If not set as
// a function argument, it will use whichever is set in the ServerEntity itself.
//
// If self.delay is set, a DelayedUse ServerEntity will be created that will actually
// do the SUB_UseTargets after that many seconds have passed.
//
// Centerprints any self.message to the activator.
//
// Search for (string)targetName in all entities that (string)target and
// calls their Use function.
//===============
//
void SVGBaseTrigger::UseTargets(ServerGameEntity* activator) {
	//
	// Check for a delay
	//
    if (GetDelayTime()) {
		// Create a temporary DelayedTrigger ServerEntity, to fire at a latter time.
	    SVGBaseTrigger *triggerDelay = SVG_CreateClassServerEntity<TriggerDelayedUse>();
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
	if (GetMessage().length() && !(activator->GetServerFlags() & ServerEntityServerFlags::Monster)) {
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
		ServerGameEntity* triggerServerEntity = nullptr;

		//while (triggerServerEntity = SVG_FindServerEntityByKeyValue("targetname", GetKillTarget(), triggerServerEntity))
		// Loop over the total ServerEntity range, ensure that we're checking for the right filters.
		for (auto* triggerServerEntity : GetBaseServerEntityRange<0, MAX_EDICTS>()
			| bef::IsValidPointer
			| bef::HasServerServerEntity
			| bef::InUse
			| bef::HasKeyValue("targetname", GetKillTarget())) {

			// It is going to die, free it.
			SVG_FreeServerEntity(triggerServerEntity->GetServerEntity());

			if (!IsInUse()) {
				gi.DPrintf("ServerEntity was removed while using killtargets\n");
				return;
			}
		}
	}
	
	//
	// Fire targets
	//
	if (GetTarget().length()) {
		// Loop over the total ServerEntity range, ensure that we're checking for the right filters.
		for (auto* triggerServerEntity : GetBaseServerEntityRange<0, MAX_EDICTS>()
			| bef::IsValidPointer
			| bef::HasServerServerEntity
			| bef::InUse
			| bef::HasKeyValue("targetname", GetTarget())) {
			
			// Doors fire area portals in a special way. So we skip those.
			if (triggerServerEntity->GetClassName() == "func_areaportal"
				&& (GetClassName() == "func_door" || GetClassName() == "func_door_rotating")) {
				continue;
			}

			// Do not ALLOW an ServerEntity to use ITSELF. :)
			if (triggerServerEntity == this) {
				gi.DPrintf("WARNING: ServerEntity #%i used itself.\n", GetServerEntity()->state.number);
			} else {
				triggerServerEntity->Use(this, activator);
			}

			// Make sure it is in use, if not, debug.
			if (!triggerServerEntity->IsInUse()) {
                gi.DPrintf("WARNING: ServerEntity #%i was removed while using targets\n", GetServerEntity()->state.number);
                return;
			}
		}
	}
}