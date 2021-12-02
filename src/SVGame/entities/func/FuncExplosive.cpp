/*
// LICENSE HERE.

// FuncExplosive.cpp
*/

#include "../../ServerGameLocal.h"
#include "../../Effects.h"
#include "../../Entities.h"
#include "../../Utilities.h"
#include "../../Physics/Stepmove.h"

#include "../Base/SynchedEntityBase.h"
#include "../Base/BaseTrigger.h"
#include "../Base/SVGBaseMover.h"

#include "FuncExplosive.h"

//===============
// FuncExplosive::FuncExplosive
//===============
FuncExplosive::FuncExplosive( ServerEntity* entity ) 
	: SynchedEntityBase( entity ) {
}

//===============
// FuncExplosive::Spawn
//===============
void FuncExplosive::Spawn() {
    SetMoveType( MoveType::Push );
    
    gi.ModelIndex( "models/objects/debris1/tris.md2" );
    gi.ModelIndex( "models/objects/debris2/tris.md2" );
    SetModel( GetModel() );

    if ( GetSpawnFlags() & SF_StartDeactivated ) {
        SetServerFlags( EntityServerFlags::NoClient );
        SetSolid( Solid::Not );
        SetUseCallback( &FuncExplosive::ExplosiveAppearUse );
    } else {
        SetSolid( Solid::BSP );
        if ( !GetTargetName().empty() ) {
            SetUseCallback( &FuncExplosive::ExplosiveUse );
        }
    }

    if ( GetSpawnFlags() & SF_Animated ) {
        serverEntity->state.effects |= EntityEffectType::AnimCycleAll2hz;
    } else if ( GetSpawnFlags() & SF_AnimatedFast ) {
        serverEntity->state.effects |= EntityEffectType::AnimCycleAll30hz;
    }

    if ( useFunction != &FuncExplosive::ExplosiveUse ) {
        if ( !GetHealth() ) {
            SetHealth( 100 );
        }

        SetDieCallback( &FuncExplosive::ExplosiveDeath );
        SetTakeDamage( TakeDamage::Yes );
    }
}

//===============
// FuncExplosive::ExplosiveDeath
//===============
void FuncExplosive::ExplosiveDeath( SynchedEntityBase * inflictor, SynchedEntityBase * attacker, int damage, const vec3_t& point ) {
    vec3_t  origin;
    vec3_t  chunkorigin;
    vec3_t  size;
    int     count;
    int     mass = GetMass() ? GetMass() : 75;

    // bmodel origins are (0 0 0), we need to adjust that here
    size = vec3_scale( GetSize(), 0.5f );
    origin = GetAbsoluteCenter();
    SetOrigin( origin );
    
    SetTakeDamage( TakeDamage::No );

    if ( GetDamage() ) {
        SVG_InflictRadiusDamage( this, attacker, GetDamage(), nullptr, GetDamage() + 40.0f, MeansOfDeath::Explosive );
    }

    // Velocity = attack direction * 150
    vec3_t newVelocity = GetOrigin() - inflictor->GetOrigin();
    newVelocity = vec3_normalize( newVelocity );
    newVelocity = vec3_scale( newVelocity, 150.0f );
    SetVelocity( newVelocity );

    // Start chunks towards the centre
    size = vec3_scale( size, 0.5f );

    // Big chonks
    if ( mass >= 100 ) {
        count = mass / 100;
        if ( count > 8 ) {
            count = 8;
        }
        while ( count-- ) {
            chunkorigin[0] = origin[0] + crandom() * size[0] * 0.5f;
            chunkorigin[1] = origin[0] + crandom() * size[1] * 0.5f;
            chunkorigin[2] = origin[0] + crandom() * size[2] * 0.5f;
            SVG_ThrowDebris( this, "models/objects/debris1/tris.md2", 1, chunkorigin );
        }
    }

    // Small chunks
    count = mass / 25;
    if ( count > 16 ) {
        count = 16;
    }
    while ( count-- ) {
        chunkorigin[0] = origin[0] + crandom() * size[0] * 0.5f;
        chunkorigin[1] = origin[0] + crandom() * size[1] * 0.5f;
        chunkorigin[2] = origin[0] + crandom() * size[2] * 0.5f;
        SVG_ThrowDebris( this, "models/objects/debris2/tris.md2", 2, chunkorigin );
    }

    UseTargets( attacker );

    if ( GetDamage() ) {
        SVG_BecomeExplosion1( this );
    } else {
        Remove();
    }
}

//===============
// FuncExplosive::ExplosiveUse
//===============
void FuncExplosive::ExplosiveUse( SynchedEntityBase * other, SynchedEntityBase * activator ) {
    ExplosiveDeath( other, activator, GetHealth(), vec3_zero() );
}

//===============
// FuncExplosive::ExplosiveAppearUse
//===============
void FuncExplosive::ExplosiveAppearUse( SynchedEntityBase * other, SynchedEntityBase * activator ) {
    SetSolid( Solid::BSP );
    SetServerFlags( GetServerFlags() & ~EntityServerFlags::NoClient );
    SetUseCallback( nullptr );
    SVG_KillBox( this );
    LinkEntity();
}
