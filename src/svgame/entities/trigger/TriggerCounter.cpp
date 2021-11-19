/*
// LICENSE HERE.

// TriggerCounter.cpp
*/

#include "../../g_local.h"
#include "../../effects.h"
#include "../../entities.h"
#include "../../utils.h"

#include "../base/SVGBaseEntity.h"
#include "../base/SVGBaseTrigger.h"

#include "TriggerCounter.h"

//===============
// TriggerCounter::ctor
//===============
TriggerCounter::TriggerCounter( ServerEntity* ServerEntity )
	: Base( ServerEntity ) {

}

//===============
// TriggerCounter::Spawn
//===============
void TriggerCounter::Spawn()
{
	SetWaitTime( -1.0f );
	SetUseCallback( &TriggerCounter::CounterUse );
}

//===============
// TriggerCounter::SpawnKey
//===============
void TriggerCounter::SpawnKey( const std::string& key, const std::string& value )
{
	if ( key == "count" ) {
		count = std::stoi( value );
	}
	else {
		return Base::SpawnKey( key, value );
	}
}

//===============
// TriggerCounter::CounterUse
//===============
void TriggerCounter::CounterUse( SVGBaseEntity* other, SVGBaseEntity* activator ) {
	if ( !count ) {
		return;
	}

	count--;

	if ( count ) {
		if ( !(GetSpawnFlags() & SF_NoMessage) ) {
			gi.CenterPrintf( activator->GetServerServerEntity(), "%u more to go...", count );
			gi.Sound( activator->GetServerServerEntity(), CHAN_AUTO, gi.SoundIndex( "misc/talk1.wav" ), 1.0f, ATTN_NORM, 0.0f );
		}
		return;
	}

	if ( !(GetSpawnFlags() & SF_NoMessage) ) {
		gi.CenterPrintf( activator->GetServerServerEntity(), "Sequence completed!" );
		gi.Sound( activator->GetServerServerEntity(), CHAN_AUTO, gi.SoundIndex( "misc/talk1.wav" ), 1.0f, ATTN_NORM, 0.0f );
	}

	this->activator = activator;

	// Mike made a funny decision to put using targets *only* into SVGBaseTrigger
	// which doesn't really make sense when you think about it, so now we have
	// SVGBaseEntity::UseTargets and SVGBaseTrigger::UseTargets
	SVGBaseEntity::UseTargets();
}
