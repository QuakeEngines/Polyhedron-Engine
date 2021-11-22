/*
// LICENSE HERE.

// FuncAreaportal.cpp
*/

#include "../../g_local.h"
#include "../../effects.h"
#include "../../entities.h"
#include "../../utils.h"
#include "../../physics/stepmove.h"
#include "../../brushfuncs.h"

#include "../base/ServerGameEntity.h"

#include "FuncAreaportal.h"

//===============
// FuncAreaportal::ctor
//===============
FuncAreaportal::FuncAreaportal( ServerEntity* entity )
	: Base( entity ) {

}

//===============
// FuncAreaportal::Spawn
//===============
void FuncAreaportal::Spawn() {
	gi.SetAreaPortalState( GetStyle(), false );
}

//===============
// FuncAreaportal::SpawnKey
//===============
void FuncAreaportal::SpawnKey( const std::string& key, const std::string& value ) {
	if ( key == "style" ) {
		ParseIntegerKeyValue( key, value, serverEntity->style );
	} else {
		Base::SpawnKey( key, value );
	}
}

//===============
// FuncAreaportal::PortalUse
//===============
void FuncAreaportal::PortalUse( ServerGameEntity* other, ServerGameEntity* activator ) {
	ActivatePortal( !turnedOn );
}

//===============
// FuncAreaportal::ActivatePortal
//===============
void FuncAreaportal::ActivatePortal( bool open ) {
	gi.SetAreaPortalState( GetStyle(), open );
	turnedOn = open;
}
