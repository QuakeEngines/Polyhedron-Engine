/*
// LICENSE HERE.

// TargetTempServerEntity.cpp
*/

#include "../../g_local.h"
#include "../../effects.h"
#include "../../entities.h"
#include "../../utils.h"

#include "../base/SVGBaseEntity.h"

#include "TargetTempServerEntity.h"

//===============
// TargetTempServerEntity::ctor
//===============
TargetTempServerEntity::TargetTempServerEntity( ServerEntity* ServerEntity )
	: Base( ServerEntity ) {

}

//===============
// TargetTempServerEntity::Spawn
//===============
void TargetTempServerEntity::Spawn() {
	SetUseCallback( &TargetTempServerEntity::TempServerEntityUse );
}

//===============
// TargetTempServerEntity::TempServerEntityUse
//===============
void TargetTempServerEntity::TempServerEntityUse( SVGBaseEntity* other, SVGBaseEntity* activator ) {
	gi.WriteByte( SVG_CMD_TEMP_ServerEntity );
	gi.WriteByte( GetStyle() );
	gi.WriteVector3( GetOrigin() );
	gi.Multicast( GetOrigin(), MultiCast::PVS );
}
