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
    virtual qboolean CanDamage(SVGBaseEntity* targ, SVGBaseEntity* inflictor) override;
    virtual void ClientBegin(ServerEntity* serverEntity) override;
    virtual void ClientBeginServerFrame(ServerEntity* serverEntity) override;
    
    virtual void RespawnClient(PlayerClient* ent) override;
    virtual void RespawnSpectator(PlayerClient* ent);

    virtual void ClientUpdateObituary(SVGBaseEntity* self, SVGBaseEntity* inflictor, SVGBaseEntity* attacker) override;

private:

};

#endif // __SVGAME_GAMEMODES_DEATHMATCHGAMEMODE_H__