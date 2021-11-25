/*
// LICENSE HERE.

// FuncDoor.cpp
*/

#include "../../g_local.h"
#include "../../effects.h"
#include "../../entities.h"
#include "../../utils.h"
#include "../../physics/stepmove.h"
#include "../../brushfuncs.h"

#include "../base/ServerGameEntity.h"
#include "../base/SVGBaseTrigger.h"
#include "../base/SVGBaseMover.h"

#include "../trigger/TriggerAutoDoor.h"

#include "FuncAreaportal.h"
#include "FuncDoor.h"

//===============
// FuncDoor::ctor
//===============
FuncDoor::FuncDoor( ServerEntity* entity ) 
	: Base( entity ) {

}

//===============
// FuncDoor::Precache
//===============
void FuncDoor::Precache() {
    Base::Precache();

    // Set up the default sounds
    if ( GetSound() != 1 ) {
        moveInfo.startSoundIndex = gi.SoundIndex( "doors/dr1_strt.wav" );
        moveInfo.middleSoundIndex = gi.SoundIndex( "doors/dr1_mid.wav" );
        moveInfo.endSoundIndex = gi.SoundIndex( "doors/dr1_end.wav" );
    }
}

//===============
// FuncDoor::Spawn
//===============
void FuncDoor::Spawn() {
    Base::Spawn();

    SetMoveDirection( GetAngles()/*, resetAngles = true*/ );
    SetMoveType( MoveType::Push );
    SetSolid( Solid::BSP );
    SetModel( GetModel() );

    SetThinkCallback( &ServerGameEntity::SVGBaseEntityThinkNull );
    SetBlockedCallback( &FuncDoor::DoorBlocked );
    SetUseCallback( &FuncDoor::DoorUse );

    if ( !GetSpeed() ) {
        SetSpeed( 100.0f );
    }
    //if ( game.gameMode->IsClass( GameModeDeathmatch::ClassInfo ) ) {
    //    SetSpeed( GetSpeed() * 2.0f );
    //}
    if ( !GetAcceleration() ) {
        SetAcceleration( GetSpeed() );
    }
    if ( !GetDeceleration() ) {
        SetDeceleration( GetSpeed() );
    }
    if ( !GetWaitTime() ) {
        SetWaitTime( 3.0f );
    }
    if ( !GetLip() ) {
        SetLip( 8.0f );
    }
    if ( !GetDamage() ) {
        SetDamage( 2 );
    }

    // Calculate the end position, with the assumption that start pos = origin
    SetStartPosition( GetOrigin() );
    SetEndPosition( CalculateEndPosition() );
    // This should never happen
    if ( GetStartPosition() == GetEndPosition() ) {
        gi.DPrintf( "WARNING: func_door has same start & end position\n" );
        return;
    }

    // If it starts open, swap the positions
    if ( GetSpawnFlags() & FuncDoor::SF_StartOpen ) {
        SwapPositions();
    }

    moveInfo.state = MoverState::Bottom;

    // If the mapper specified health, then make this door
    // openable by shooting it
    if ( GetHealth() ) {
        SetTakeDamage( TakeDamage::Yes );
        SetDieCallback( &FuncDoor::DoorShotOpen );
        SetMaxHealth( GetHealth() );
    } else if ( nullptr == serverEntity->targetName ) {
        gi.SoundIndex( MessageSoundPath );
        SetTouchCallback( &FuncDoor::DoorTouch );
    }

    moveInfo.speed = GetSpeed();
    moveInfo.acceleration = GetAcceleration();
    moveInfo.deceleration = GetDeceleration();
    moveInfo.wait = GetWaitTime();
    moveInfo.startOrigin = GetStartPosition();
    moveInfo.startAngles = GetAngles();
    moveInfo.endOrigin = GetEndPosition();
    moveInfo.endAngles = GetAngles();

    if ( GetSpawnFlags() & SF_Toggle ) {
        serverEntity->state.effects |= EntityEffectType::AnimCycleAll2hz;
    }
    if ( GetSpawnFlags() & SF_YAxis ) {
        serverEntity->state.effects |= EntityEffectType::AnimCycleAll30hz;
    }

    // To simplify logic elsewhere, make non-teamed doors into a team of one
    if ( !GetTeam() ) {
        SetTeamMasterEntity( this );
    }

    LinkEntity();
}

//===============
// FuncDoor::PostSpawn
// 
// func_door in Q2 originally used spawn think functions
// to achieve this. If the entity had health or had a 
// targetname, it'd calculate its move speed, else
// it'd spawn a door trigger around itself
//===============
void FuncDoor::PostSpawn() {
    if ( GetHealth() || !targetNameStr.empty() ) {
        CalculateMoveSpeed();
    } else {
        SpawnDoorTrigger();
    }
}

//===============
// FuncDoor::DoorUse
//===============
void FuncDoor::DoorUse( ServerGameEntity* other, ServerGameEntity* activator ) {
    if ( GetFlags() & EntityFlags::TeamSlave ) {
        return;
    }

    // This should never happen
    if ( GetStartPosition() == GetEndPosition() ) {
        gi.DPrintf( "WARNING: func_door has same start & end position\n" );
        return;
    }

    if ( GetSpawnFlags() & SF_Toggle ) {
        if ( moveInfo.state == MoverState::Up || moveInfo.state == MoverState::Top ) {
            // Trigger all paired doors
            for ( ServerGameEntity* ent = this; nullptr != ent; ent = ent->GetTeamChainEntity() ) {
                if ( ent->IsSubclassOf<FuncDoor>() ) {
                    ent->SetMessage( "" );
                    ent->SetTouchCallback( nullptr );
                    static_cast<FuncDoor*>( ent )->DoorGoDown();
                }
            }

            return;
        }
    }

    // Trigger all paired doors
    for ( ServerGameEntity* ent = this; nullptr != ent; ent = ent->GetTeamChainEntity() ) {
        if ( ent->IsSubclassOf<FuncDoor>() ) {
            ent->SetMessage( "" );
            ent->SetTouchCallback( nullptr );
            static_cast<FuncDoor*>( ent )->DoorGoUp( activator );
        }
    }
}

//===============
// FuncDoor::DoorShotOpen
//===============
void FuncDoor::DoorShotOpen( ServerGameEntity* inflictor, ServerGameEntity* attacker, int damage, const vec3_t& point ) {
    ServerGameEntity* ent;
    for ( ent = GetTeamMasterEntity(); nullptr != ent; ent = GetTeamChainEntity() ) {
        ent->SetHealth( GetMaxHealth() );
        ent->SetTakeDamage( TakeDamage::No );
    }

    GetTeamMasterEntity()->Use( attacker, attacker );
}

//===============
// FuncDoor::DoorBlocked
//===============
void FuncDoor::DoorBlocked( ServerGameEntity* other ) {
    ServerGameEntity* ent;
    
    if ( !(other->GetServerFlags() & EntityServerFlags::Monster) && !(other->GetClient()) ) {
        // Give it a chance to go away on its own terms (like gibs)
        SVG_InflictDamage( other, this, this, vec3_zero(), other->GetOrigin(), vec3_zero(), 10000, 1, 0, MeansOfDeath::Crush );
        // If it's still there, nuke it
        if ( other->GetHealth() > 0 || other->GetSolid() != Solid::Not ) {
            SVG_BecomeExplosion1( other );
        }
    }

    SVG_InflictDamage( other, this, this, vec3_zero(), other->GetOrigin(), vec3_zero(), GetDamage(), 1, 0, MeansOfDeath::Crush );

    if ( GetSpawnFlags() & SF_Crusher ) {
        return;
    }

    // If a door has a negative wait, it would never come back if blocked,
    // so let it just squash the object to death real fast
    if ( moveInfo.wait >= 0 ) {
        if ( moveInfo.state == MoverState::Down ) {
            for ( ent = GetTeamMasterEntity(); nullptr != ent; ent = GetTeamChainEntity() ) {
                if ( ent->IsSubclassOf<FuncDoor>() ) {
                    static_cast<FuncDoor*>( ent )->DoorGoUp( ent->GetActivator() );
                }
            }
        } else {
            for ( ent = GetTeamMasterEntity(); nullptr != ent; ent = GetTeamChainEntity() ) {
                if ( ent->IsSubclassOf<FuncDoor>() ) {
                    static_cast<FuncDoor*>( ent )->DoorGoDown();
                }
            }
        }
    }
}

//===============
// FuncDoor::DoorTouch
//===============
void FuncDoor::DoorTouch( ServerGameEntity* self, ServerGameEntity* other, cplane_t* plane, csurface_t* surf ) {
    if ( nullptr == other->GetClient() ) {
        return; // Players only; should we have special flags for monsters et al?
    }

    if ( level.time < debounceTouchTime ) {
        return;
    }

    debounceTouchTime = level.time + 5.0f;

    if ( !messageStr.empty() ) {
        gi.CenterPrintf( other->GetEntityServerHandle(), "%s", messageStr.c_str() );
        gi.Sound( other->GetEntityServerHandle(), CHAN_AUTO, gi.SoundIndex( MessageSoundPath ), 1.0f, ATTN_NORM, 0.0f );
    }
}

//===============
// FuncDoor::DoorGoUp
//===============
void FuncDoor::DoorGoUp( ServerGameEntity* activator ) {
    if ( moveInfo.state == MoverState::Up ) {
        return; // already going up
    }

    if ( moveInfo.state == MoverState::Top ) {
        // Reset top wait time 
        if ( moveInfo.wait >= 0.0f ) {
            SetNextThinkTime( level.time + moveInfo.wait );
        }
        return;
    }

    if ( !(GetFlags() & EntityFlags::TeamSlave) ) {
        if ( moveInfo.startSoundIndex ) {
            gi.Sound( GetEntityServerHandle(), CHAN_NO_PHS_ADD + CHAN_VOICE, moveInfo.startSoundIndex, 1, ATTN_STATIC, 0.0f );
        }
        SetSound( moveInfo.middleSoundIndex );
    }

    moveInfo.state = MoverState::Up;

    DoGoUp();
    UseTargets( activator );
    UseAreaportals( true );
}

//===============
// FuncDoor::DoorGoDown
//===============
void FuncDoor::DoorGoDown() {
    if ( !(GetFlags() & EntityFlags::TeamSlave) ) {
        if ( moveInfo.startSoundIndex ) {
            gi.Sound( GetEntityServerHandle(), CHAN_NO_PHS_ADD + CHAN_VOICE, moveInfo.startSoundIndex, 1, ATTN_STATIC, 0 );
        }
        SetSound( moveInfo.middleSoundIndex );
    }

    if ( GetMaxHealth() ) {
        SetTakeDamage( TakeDamage::Yes );
        SetHealth( GetMaxHealth() );
    }

    moveInfo.state = MoverState::Down;
    DoGoDown();
}

//===============
// FuncDoor::DoGoUp
//===============
void FuncDoor::DoGoUp() {
    BrushMoveCalc( moveInfo.endOrigin, OnDoorHitTop );
}

//===============
// FuncDoor::DoGoDown
//===============
void FuncDoor::DoGoDown() {
    BrushMoveCalc( moveInfo.startOrigin, OnDoorHitBottom );
}

//===============
// FuncDoor::HitTop
//===============
void FuncDoor::HitTop() {
    if ( !(GetFlags() & EntityFlags::TeamSlave) ) {
        if ( moveInfo.endSoundIndex ) {
            gi.Sound( GetEntityServerHandle(), CHAN_NO_PHS_ADD + CHAN_VOICE, moveInfo.endSoundIndex, 1.0f, ATTN_STATIC, 0.0f );
        }
        SetSound( 0 );
    }

    moveInfo.state = MoverState::Top;
    if ( GetSpawnFlags() & SF_Toggle ) {
        return;
    }

    if ( moveInfo.wait >= 0.0f ) {
        SetThinkCallback( &FuncDoor::DoorGoDown );
        SetNextThinkTime( level.time + moveInfo.wait );
    }
}

//===============
// FuncDoor::HitBottom
//===============
void FuncDoor::HitBottom() {
    if ( !(GetFlags() & EntityFlags::TeamSlave) ) {
        if ( moveInfo.endSoundIndex ) {
            gi.Sound( GetEntityServerHandle(), CHAN_NO_PHS_ADD + CHAN_VOICE, moveInfo.endSoundIndex, 1.0f, ATTN_STATIC, 0.0f );
        }
        SetSound( 0 );
    }

    moveInfo.state = MoverState::Bottom;
    UseAreaportals( false ); // close off area portals
}

//===============
// FuncDoor::OnDoorHitTop
//===============
void FuncDoor::OnDoorHitTop( ServerEntity* self ) {
    if ( self->classEntity->IsSubclassOf<FuncDoor>() ) {
        static_cast<FuncDoor*>( self->classEntity )->HitTop();
    }
}

//===============
// FuncDoor::OnDoorHitBottom
//===============
void FuncDoor::OnDoorHitBottom( ServerEntity* self ) {
    if ( self->classEntity->IsSubclassOf<FuncDoor>() ) {
        static_cast<FuncDoor*>(self->classEntity)->HitBottom();
    }
}

//===============
// FuncDoor::CalculateMoveSpeed
//===============
void FuncDoor::CalculateMoveSpeed() {
    if ( GetFlags() & EntityFlags::TeamSlave ) {
        return; // Only the team master does this
    }

    FuncDoor* ent = nullptr;
    float min;
    float time;
    float newSpeed;
    float ratio;
    float distance;
    
    // Find the smallest distance any member of the team will be moving
    min = fabsf( moveInfo.distance );
    for ( ent = dynamic_cast<FuncDoor*>( GetTeamChainEntity() ); ent; ent = dynamic_cast<FuncDoor*>( ent->GetTeamChainEntity() ) ) {
        distance = fabsf( ent->moveInfo.distance );
        if ( distance < min ) {
            min = distance;
        }
    }

    time = min / GetSpeed();

    // Adjust speeds so they will all complete at the same time
    for ( ent = this; ent; ent = dynamic_cast<FuncDoor*>(ent->GetTeamChainEntity()) ) {
        newSpeed = fabsf( ent->moveInfo.distance ) / time;
        ratio = newSpeed / ent->moveInfo.speed;

        if ( ent->moveInfo.acceleration == ent->moveInfo.speed ) {
            ent->moveInfo.acceleration = newSpeed;
        } else {
            ent->moveInfo.acceleration *= ratio;
        }

        if ( ent->moveInfo.deceleration == ent->moveInfo.speed ) {
            ent->moveInfo.deceleration = ent->moveInfo.speed;
        } else {
            ent->moveInfo.deceleration *= ratio;
        }

        // Update moveInfo variables and class member variables
        ent->SetAcceleration( ent->moveInfo.acceleration );
        ent->SetDeceleration( ent->moveInfo.deceleration );
        ent->moveInfo.speed = newSpeed;
        ent->SetSpeed( newSpeed );
    }
}

//===============
// FuncDoor::SpawnDoorTrigger
// 
// Nameless, non-shootable doors have an invisible bounding box around them, which
// is slightly larger than the door's bounding box.
// 
// This bad boy spawns it, so keep that in mind if you're running out of edict slots.
//===============
void FuncDoor::SpawnDoorTrigger() {
    FuncDoor* teamMember = nullptr;
    ServerGameEntity* trigger = nullptr;
    vec3_t mins = GetMins();
    vec3_t maxs = GetMaxs();

    if ( GetFlags() & EntityFlags::TeamSlave ) {
        return; // Only the team leader spawns a trigger
    }
    
    for ( teamMember = dynamic_cast<FuncDoor*>(GetTeamChainEntity()); teamMember; teamMember = dynamic_cast<FuncDoor*>(teamMember->GetTeamChainEntity()) ) {
        AddPointToBounds( teamMember->GetAbsoluteMin(), mins, maxs );
        AddPointToBounds( teamMember->GetAbsoluteMax(), mins, maxs );
    }

    // Expand the trigger box on the horizontal plane by 60 units
    static const vec3_t HullExpand = { 60.0f, 60.0f, 0.0f };
    mins -= HullExpand;
    maxs += HullExpand;

    // Spawn the auto door trigger
    trigger = TriggerAutoDoor::Create( this, maxs, mins );
    
    if ( GetSpawnFlags() & FuncDoor::SF_StartOpen ) {
        UseAreaportals( true );
    }

    CalculateMoveSpeed();
}

//===============
// FuncDoor::UseAreaportals
//===============
void FuncDoor::UseAreaportals( bool open ) const {
    if ( targetStr.empty() ) {
        return;
    }

    ServerGameEntity* ent = nullptr;
    while ( ent = SVG_FindEntityByKeyValue( "targetname", targetStr, ent ) ) {
        if ( ent->IsClass<FuncAreaportal>() ) {
            static_cast<FuncAreaportal*>(ent)->ActivatePortal( open );
        }
    }
}
