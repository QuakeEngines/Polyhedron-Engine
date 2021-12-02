/*
// LICENSE HERE.

// TargetTempEntity.cpp
*/

#include "../../ServerGameLocal.h"
#include "../../Effects.h"
#include "../../Entities.h"
#include "../../Utilities.h"

#include "../base/SynchedEntityBase.h"

#include "TargetTempEntity.h"

//===============
// TargetTempEntity::ctor
//===============
TargetTempEntity::TargetTempEntity( ServerEntity* entity )
	: Base( entity ) {

}

//===============
// TargetTempEntity::Spawn
//===============
void TargetTempEntity::Spawn() {
	SetUseCallback( &TargetTempEntity::TempEntityUse );
}

//===============
// TargetTempEntity::TempEntityUse
//===============
void TargetTempEntity::TempEntityUse( SynchedEntityBase * other, SynchedEntityBase * activator ) {
	gi.WriteByte( SVG_CMD_TEMP_ENTITY );
	gi.WriteByte( GetStyle() );
	gi.WriteVector3( GetOrigin() );
	gi.Multicast( GetOrigin(), MultiCast::PVS );
}
