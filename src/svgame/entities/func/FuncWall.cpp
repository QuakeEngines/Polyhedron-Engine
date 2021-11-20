/*
// LICENSE HERE.

// TriggerRelay.cpp
*/

#include "../../g_local.h"
#include "../../effects.h"
#include "../../entities.h"
#include "../../utils.h"

#include "../base/ServerGameEntity.h"

#include "FuncWall.h"

//===============
// FuncWall::ctor
//===============
FuncWall::FuncWall( ServerEntity* ServerEntity )
	: Base( ServerEntity ) {

}

//===============
// FuncWall::Spawn
//===============
void FuncWall::Spawn() {
    Base::Spawn();

    SetMoveType( MoveType::Push );
    SetModel( GetModel() );

    if ( GetSpawnFlags() & SF_Animated ) {
        serverEntity->state.effects |= ServerEntityEffectType::AnimCycleAll2hz;
    } else if ( GetSpawnFlags() & SF_AnimatedFast ) {
        serverEntity->state.effects |= ServerEntityEffectType::AnimCycleAll30hz;
    }

    // Just a wall
    if ( !(GetSpawnFlags() & 7) ) {
        SetSolid( Solid::BSP );
        LinkServerEntity();
        return;
    }

    // ???
    if ( !(GetSpawnFlags() & SF_TriggerSpawn) ) {
        spawnFlags |= SF_TriggerSpawn;
    }

    // Yell if the spawnflags are weird
    if ( (GetSpawnFlags() & SF_StartOn) && !(GetSpawnFlags() & SF_Toggle) ) {
        gi.DPrintf( "func_wall has StartOn without Toggle!!!\n" );
        spawnFlags |= SF_Toggle;
    }

    SetUseCallback( &FuncWall::WallUse );

    if ( GetSpawnFlags() & SF_StartOn ) {
        SetSolid( Solid::BSP );
    } else {
        SetSolid( Solid::Not );
        SetServerFlags( GetServerFlags() | ServerEntityServerFlags::NoClient );
    }

    LinkServerEntity();
}

//===============
// FuncWall::WallUse
//===============
void FuncWall::WallUse( ServerGameEntity* other, ServerGameEntity* activator ) {
    if ( GetSolid() == Solid::Not ) {
        SetSolid( Solid::BSP );
        SetServerFlags( GetServerFlags() & ~ServerEntityServerFlags::NoClient );
        SVG_KillBox( this );
    } else {
        SetSolid( Solid::Not );
        SetServerFlags( GetServerFlags() | ServerEntityServerFlags::NoClient );
    }

    LinkServerEntity();

    if ( !(GetSpawnFlags() & SF_Toggle) ) {
        SetUseCallback( nullptr );
    }
}
