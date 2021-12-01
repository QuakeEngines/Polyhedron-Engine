/*
// LICENSE HERE.

//
// DeathMatchGameMode.h
//
// Default game mode to run, allows for all sorts of stuff.
//
*/
#ifndef __SVGAME_GAMEMODES_DEATHMATCHGAMEMODE_H__
#define __SVGAME_GAMEMODES_DEATHMATCHGAMEMODE_H__

#include "IGameMode.h"
#include "DefaultGameMode.h"

class DeathMatchGameMode : public DefaultGameMode {
public:
    // Constructor/Deconstructor.
    DeathMatchGameMode();
    virtual ~DeathMatchGameMode() override;

    //
    // Functions defining game rules. Such as, CanDamage, Can... IsAllowedTo...
    //
    // DeathMatch unique function implementations.
    virtual void PutClientInServer(ServerEntity* ent) override;
    virtual qboolean CanDamage(SynchedEntityBase * targ, SynchedEntityBase * inflictor) override;
    virtual void ClientBegin(ServerEntity* serverEntity) override;
    virtual void ClientBeginServerFrame(ServerEntity* serverEntity) override;
    
    virtual void RespawnClient(ServerEntity* ent) override;
    virtual void RespawnSpectator(ServerEntity* ent);

    virtual void ClientUpdateObituary(SynchedEntityBase * self, SynchedEntityBase * inflictor, SynchedEntityBase * attacker) override;

private:

};

#endif // __SVGAME_GAMEMODES_DEATHMATCHGAMEMODE_H__