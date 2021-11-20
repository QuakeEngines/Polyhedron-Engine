/*
// LICENSE HERE.

// TriggerGravity.cpp
*/

#include "../../g_local.h"
#include "../../effects.h"
#include "../../entities.h"
#include "../../utils.h"

#include "../base/ServerGameEntity.h"
#include "../base/SVGBaseTrigger.h"

#include "TriggerGravity.h"

//===============
// TriggerGravity::ctor
//===============
TriggerGravity::TriggerGravity( ServerEntity* ServerEntity )
	: Base( ServerEntity ) {

}

//===============
// TriggerGravity::Spawn
//===============
void TriggerGravity::Spawn() {
    if ( GetGravity() == 0.0f ) {
        gi.DPrintf( "trigger_gravity without gravity set at %s\n", vec3_to_cstr( GetOrigin() ) );
        Remove();
        return;
    }

    InitBrushTrigger();
	SetTouchCallback( &TriggerGravity::GravityTouch );
}

//===============
// TriggerGravity::SpawnKey
//===============
void TriggerGravity::SpawnKey( const std::string& key, const std::string& value ) {
    if ( key == "gravity" ) {
        SetGravity( std::stof( value ) );
    } else {
        return Base::SpawnKey( key, value );
    }
}

//===============
// TriggerGravity::GravityTouch
//===============
void TriggerGravity::GravityTouch( ServerGameEntity* self, ServerGameEntity* other, cplane_t* plane, csurface_t* surf ) {
	other->SetGravity( GetGravity() );
}
