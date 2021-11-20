/*
// LICENSE HERE.

// FuncTrain.cpp
*/

#include "../../g_local.h"
#include "../../entities.h"
#include "../../effects.h"

#include "../base/SVGBaseTrigger.h"
#include "../base/SVGBaseMover.h"

#include "../path/PathCorner.h"
#include "FuncTrain.h"

//===============
// FuncTrain::ctor
//===============
FuncTrain::FuncTrain( ServerEntity* ServerEntity )
 : Base( ServerEntity ) {

}

//===============
// FuncTrain::Spawn
//===============
void FuncTrain::Spawn() {
	Base::Spawn();

	SetMoveType( MoveType::Push );
	SetSolid( Solid::BSP );
	SetAngles( vec3_zero() );

	if ( spawnFlags & SF_StopWhenBlocked ) {
		damage = 0;
	} else if ( !damage ) {
		damage = 100;
	}

	SetModel( GetModel() );

	if ( !GetSpeed() ) {
		SetSpeed( 100.0f );
	}

	moveInfo.acceleration = GetSpeed();
	moveInfo.deceleration = GetSpeed();

	LinkServerEntity();

	if ( targetStr.empty() ) {
		gi.DPrintf( "func_train without a target at %s\n", vec3_to_cstr( GetAbsoluteCenter() ) );
	}
}

//===============
// FuncTrain::PostSpawn
//===============
void FuncTrain::PostSpawn() {
	if ( targetStr.empty() ) {
		return;
	}

	ServerGameEntity* ent = SVG_FindServerEntityByKeyValue( "targetname", targetStr );
	if ( nullptr == ent ) {
		gi.DPrintf( "FuncTrain: target '%s' not found, maybe you made a typo?\n", targetStr.c_str() );
		return;
	}

	if ( !ent->IsSubclassOf<PathCorner>() ) {
		gi.DPrintf( "FuncTrain: target '%s' is not a path ServerEntity\n", targetStr.c_str() );
		return;
	}

	SetUseCallback( &FuncTrain::TrainUse );

	serverEntity->state.origin = ent->GetOrigin() - GetMins();
	LinkServerEntity();

	// This train has no name, trigger it immediately
	if ( targetNameStr.empty() ) {
		spawnFlags |= SF_StartOn;
	}

	if ( spawnFlags & SF_StartOn ) {
		SetNextThinkTime( level.time + FRAMETIME );
		SetThinkCallback( &FuncTrain::NextCornerThink );
		activator = this;
	}
}

//===============
// FuncTrain::SpawnKey
// 
// I've put this here in case we add new KVs
//===============
void FuncTrain::SpawnKey( const std::string& key, const std::string& value ) {
	if ( key == "speed" ) {
		ParseFloatKeyValue( key, value, speed );
	} else {
		return Base::SpawnKey( key, value );
	}
}

//===============
// FuncTrain::TrainUse
//===============
void FuncTrain::TrainUse( ServerGameEntity* other, ServerGameEntity* activator ) {
	this->activator = activator;

	if ( spawnFlags & SF_StartOn ) {
		if ( ~spawnFlags & SF_Toggled ) {
			return;
		}

		spawnFlags &= ~SF_StartOn;
		SetVelocity( vec3_zero() );
		SetNextThinkTime( 0.0f );
	} else {
		if ( nullptr != currentPathServerEntity ) {
			ResumePath();
		} else {
			NextCornerThink();
		}
	}

}

//===============
// FuncTrain::NextCornerThink
//===============
void FuncTrain::NextCornerThink() {
	ServerGameEntity* ServerEntity = nullptr;
	vec3_t destination;
	bool first = true;
	bool again = true;

	// Train encountered teleporting path_corners, so pick the next one each time
	// Originally, this used a goto
	while ( again )
	{
		again = false;

		if ( targetStr.empty() ) {
			return;
		}

		ServerEntity = SVG_FindServerEntityByKeyValue( "targetname", GetTarget() );
		if ( nullptr == ServerEntity ) {
			gi.DPrintf( "FuncTrain::NextCornerThink: Target '%s' doesn't exist\n", GetTarget().c_str() );
			return;
		}
		
		// QUESTIONABLE: Are mappers gonna use non-path_corner ents?
		// We'll probably be rewriting this logic anyway someday...
		if ( !ServerEntity->IsClass<PathCorner>() ) {
			gi.DPrintf( "FuncTrain::NextCornerThink: Target '%s' isn't a path_corner\n", GetTarget().c_str() );
			return;
		}
		
		SetTarget( ServerEntity->GetTarget() );

		if ( ServerEntity->GetSpawnFlags() & PathCorner::SF_Teleport ) {
			if ( !first ) {
				gi.DPrintf( "Connected teleport path_corners, see '%s' at '%s'\n", ServerEntity->GetTypeInfo()->mapClass, vec3_to_cstr( ServerEntity->GetOrigin() ) );
				return;
			}

			first = false;
			again = true; // loop it
			SetOrigin( ServerEntity->GetOrigin() - GetMins() );
			SetOldOrigin( GetOrigin() );
			SetEventID( ServerEntityEvent::OtherTeleport );
			LinkServerEntity();
		}
	}

	moveInfo.wait = ServerEntity->GetWaitTime();
	currentPathServerEntity = static_cast<PathCorner*>(ServerEntity);

	destination = ServerEntity->GetOrigin() - GetMins();
	moveInfo.state = MoverState::Top;
	moveInfo.startOrigin = GetOrigin();
	moveInfo.endAngles = destination;

	BrushMoveCalc( destination, &FuncTrain::OnWaitAtCorner );
	spawnFlags |= SF_StartOn;
}

//===============
// FuncTrain::ResumePath
//===============
void FuncTrain::ResumePath() {
	vec3_t destination = currentPathServerEntity->GetOrigin() - GetMins();

	moveInfo.state = MoverState::Top;
	moveInfo.startOrigin = GetOrigin();
	moveInfo.endOrigin = destination;

	BrushMoveCalc( destination, &FuncTrain::OnWaitAtCorner );
	spawnFlags |= SF_StartOn;
}

//===============
// FuncTrain::WaitAtCorner
//===============
void FuncTrain::WaitAtCorner() {
	// Trigger stuff that is associated with the current path corner
	if ( currentPathServerEntity->GetPathTarget() ) {
		// Temporarily swap target and pathTarget
		std::string nextCorner = currentPathServerEntity->GetTarget();
		currentPathServerEntity->SetTarget( currentPathServerEntity->GetPathTarget() );
		currentPathServerEntity->UseTargets( activator );
		currentPathServerEntity->SetTarget( nextCorner );

		// Do not proceed if we got killed by a killtarget
		if ( GetServerFlags() & ServerEntityServerFlags::Remove ) {
			return;
		}
	}

	if ( moveInfo.wait ) {
		if ( moveInfo.wait > 0.0f ) {
			SetNextThinkTime( level.time + moveInfo.wait );
			SetThinkCallback( &FuncTrain::NextCornerThink );
		} else if ( GetSpawnFlags() & SF_Toggled ) {
			NextCornerThink();
			spawnFlags &= ~SF_StartOn;
			SetVelocity( vec3_zero() );
			SetNextThinkTime( 0.0f );
		}

		if ( !(GetFlags() & ServerEntityFlags::TeamSlave) ) {
			if ( moveInfo.endSoundIndex ) {
				gi.Sound( serverEntity, CHAN_NO_PHS_ADD + CHAN_VOICE, moveInfo.endSoundIndex, 1, ATTN_STATIC, 0 );
			}
			SetSound( 0 );
		}
	} else {
		NextCornerThink();
	}
}

//===============
// FuncTrain::OnWaitAtCorner
//===============
void FuncTrain::OnWaitAtCorner( ServerEntity* ent ) {
	if ( ent->classServerEntity->IsSubclassOf<FuncTrain>() ) {
		static_cast<FuncTrain*>( ent->classServerEntity )->WaitAtCorner();
	}
}

//===============
// FuncTrain::TrainBlocked
//===============
void FuncTrain::TrainBlocked( ServerGameEntity* other ) {
	if ( !(other->GetServerFlags() & ServerEntityServerFlags::Monster) && !other->GetClient() ) {
		// Give it a chance to go away on its own terms (like gibs)
		SVG_InflictDamage( other, this, this, vec3_zero(), other->GetOrigin(), vec3_zero(), 100000, 1, 0, MeansOfDeath::Crush );
		// If it's still there, nuke it
		if ( other ) {
			SVG_BecomeExplosion1( other );
		}

		return;
	}

	if ( level.time < damageDebounceTime || !GetDamage() ) {
		return;
	}

	damageDebounceTime = level.time + 0.5f;
	SVG_InflictDamage( other, this, this, vec3_zero(), other->GetOrigin(), vec3_zero(), GetDamage(), 1, 0, MeansOfDeath::Crush );
}
