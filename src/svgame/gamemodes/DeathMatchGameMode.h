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
    virtual void PutClientInServer(PlayerEntity* ent) override;
    virtual qboolean CanDamage(PlayerEntity* targ, ServerGameEntity* inflictor) override;
    virtual void ClientBegin(PlayerEntity* serverEntity) override;
    virtual void ClientBeginServerFrame(PlayerEntity* serverEntity) override;
    
    virtual void RespawnClient(PlayerEntity* ent) override;
    virtual void RespawnSpectator(PlayerEntity* ent);

    virtual void ClientUpdateObituary(PlayerEntity* self, ServerGameEntity* inflictor, ServerGameEntity* attacker) override;

private:

};

#endif // __SVGAME_GAMEMODES_DEATHMATCHGAMEMODE_H__