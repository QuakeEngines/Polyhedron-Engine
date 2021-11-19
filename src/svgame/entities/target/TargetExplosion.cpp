/*
// LICENSE HERE.

// TargetExplosion.cpp
*/

#include "../../g_local.h"
#include "../../effects.h"
#include "../../entities.h"
#include "../../utils.h"

#include "../base/SVGBaseEntity.h"

#include "TargetExplosion.h"

//===============
// TargetExplosion::ctor
//===============
TargetExplosion::TargetExplosion( ServerEntity* ServerEntity )
	: Base( ServerEntity ) {

}

//===============
// TargetExplosion::Spawn
//===============
void TargetExplosion::Spawn() {
	SetUseCallback( &TargetExplosion::ExplosionUse );
	SetServerFlags( ServerEntityServerFlags::NoClient );
}

//===============
// TargetExplosion::ExplosionUse
//===============
void TargetExplosion::ExplosionUse( SVGBaseEntity* other, SVGBaseEntity* activator ) {
	this->activator = activator;

	if ( !GetDelayTime() ) {
		ExplosionThink();
		return;
	}

	SetThinkCallback( &TargetExplosion::ExplosionThink );
	SetNextThinkTime( level.time + GetDelayTime() );
}

//===============
// TargetExplosion::ExplosionThink
//===============
void TargetExplosion::ExplosionThink() {
	gi.WriteByte( SVG_CMD_TEMP_ServerEntity );
	gi.WriteByte( TempServerEntityEvent::Explosion1 );
	gi.WriteVector3( GetOrigin() );
	gi.Multicast( GetOrigin(), MultiCast::PHS );

	SVG_InflictRadiusDamage( this, activator, GetDamage(), nullptr, GetDamage() + 40.0f, MeansOfDeath::Explosive );

	float save;
	save = GetDelayTime();
	SetDelayTime( 0.0f );
	UseTargets();
	SetDelayTime( save );
}
