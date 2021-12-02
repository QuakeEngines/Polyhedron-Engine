/*
// LICENSE HERE.

// TriggerPush.cpp
*/

#include "../../ServerGameLocal.h"
#include "../../Effects.h"
#include "../../Entities.h"
#include "../../Utilities.h"

#include "../base/SynchedEntityBase.h"
#include "../base/BaseTrigger.h"
#include "../base/PlayerEntity.h"

#include "TriggerPush.h"

//===============
// TriggerPush::ctor
//===============
TriggerPush::TriggerPush( ServerEntity* entity )
	: Base( entity ) {

}

//===============
// TriggerPush::Spawn
//===============
void TriggerPush::Spawn() {
	if ( !WindSound ) {
		WindSound = gi.SoundIndex( "misc/windfly.wav" );
	}

	InitBrushTrigger();
	SetTouchCallback( &TriggerPush::PushTouch );
	LinkEntity();
}

//===============
// TriggerPush::SpawnKey
//===============
void TriggerPush::SpawnKey( const std::string& key, const std::string& value ) {
	if ( key == "speed" ) {
        ParseFloatKeyValue(key, value, pushForce);
	} else if ( key == "movedir" ) {
        ParseVector3KeyValue( key, value, pushDirection );
	} else {
		return Base::SpawnKey( key, value );
	}
}

//===============
// TriggerPush::PushTouch
//===============
void TriggerPush::PushTouch( SynchedEntityBase * self, SynchedEntityBase * other, cplane_t* plane, csurface_t* surf ) {
    vec3_t newVelocity = vec3_scale( pushDirection, pushForce * 10.0f);
    
    /* TODO:
    if ( other == grenade ) {
        increase push velocity 10x
    } else*/ 
    if ( other->GetHealth() > 0 ) {
        other->SetVelocity( newVelocity );

        // Play sounds on clients
        if ( other->IsClass<PlayerEntity>() ) {
            PlayerEntity* player = static_cast<PlayerEntity*>(other);

            // Don't take fall damage immediately from this
            player->GetClient()->oldVelocity = other->GetVelocity();
            if ( player->GetDebounceSoundTime() < level.time ) {
                player->SetDebounceSoundTime( level.time + 1.5f);
                SVG_Sound( player, CHAN_AUTO, WindSound, 1.0f, ATTN_NORM, 0.0f );
            }
        }
    }

    if ( GetSpawnFlags() & SF_PushOnce ) {
        Remove();
    }
}
