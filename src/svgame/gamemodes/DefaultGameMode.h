/*
// LICENSE HERE.

//
// DefaultGameMode.h
//
// Default game mode to run, allows for all sorts of stuff.
//
*/
#ifndef __SVGAME_GAMEMODES_DEFAULTGAMEMODE_H__
#define __SVGAME_GAMEMODES_DEFAULTGAMEMODE_H__

#include "IGameMode.h"

class DefaultGameMode : public IGameMode {
public:
    // Constructor/Deconstructor.
    DefaultGameMode();
    virtual ~DefaultGameMode() override;

    //
    // Functions defining game rules. Such as, CanDamage, Can... IsAllowedTo...
    //
    virtual void OnLevelExit() override;

    //
    // Combat GameRules checks.
    //
    virtual qboolean GetServerEntityTeamName(SVGBaseEntity* ent, std::string &teamName) override;
    virtual qboolean OnSameTeam(SVGBaseEntity* ent1, SVGBaseEntity* ent2) override;
    virtual qboolean CanDamage(SVGBaseEntity* targ, SVGBaseEntity* inflictor) override;
    virtual BaseServerEntityVector FindBaseEnitiesWithinRadius(const vec3_t& origin, float radius, uint32_t excludeSolidFlags) override;

    //
    // Combat GameMode actions.
    //
    virtual void ServerEntityKilled(SVGBaseEntity* target, SVGBaseEntity* inflictor, SVGBaseEntity* attacker, int32_t damage, vec3_t point) override;
    virtual void InflictDamage(SVGBaseEntity* target, SVGBaseEntity* inflictor, SVGBaseEntity* attacker, const vec3_t& dmgDir, const vec3_t& point, const vec3_t& normal, int32_t damage, int32_t knockBack, int32_t dflags, int32_t mod) override;
    virtual void InflictRadiusDamage(SVGBaseEntity* inflictor, SVGBaseEntity* attacker, float damage, SVGBaseEntity* ignore, float radius, int32_t mod) override;
    virtual void SetCurrentMeansOfDeath(int32_t meansOfDeath) override;
    virtual const int32_t& GetCurrentMeansOfDeath() override;

    //
    // Random Gameplay Functions.
    //
    virtual void SpawnClientCorpse(SVGBaseEntity* ent) override;
    virtual void SpawnTempDamageServerEntity(int32_t type, const vec3_t& origin, const vec3_t& normal, int32_t damage) override;
    virtual vec3_t CalculateDamageVelocity(int32_t damage) override;
    
    //
    // Client related callbacks.
    // 
    virtual qboolean ClientConnect(ServerEntity* serverEntity, char *userinfo) override;
    virtual void ClientBegin(ServerEntity* serverEntity) override;
    virtual void ClientBeginServerFrame(ServerEntity *serverEntity) override;
    virtual void ClientEndServerFrame(ServerEntity *serverEntity) override;
    virtual void ClientDisconnect(PlayerClient* ent) override;
    virtual void ClientUserinfoChanged(ServerEntity* ent, char *userinfo) override;
    virtual void ClientUpdateObituary(SVGBaseEntity* self, SVGBaseEntity* inflictor, SVGBaseEntity* attacker) override;

    //
    // Client related functions/utilities.
    // 
    virtual void InitializeClientPersistentData(ServersClient* client) override;
    virtual void InitializeClientRespawnData(ServersClient *client) override;

    virtual void SelectClientSpawnPoint(ServerEntity* ent, vec3_t& origin, vec3_t& angles, const std::string &classname) override;
    virtual void PutClientInServer(ServerEntity *ent) override;
    virtual void RespawnClient(PlayerClient* ent) override;

    // Some information that should be persistant, like health,
    // is still stored in the edict structure, so it needs to
    // be mirrored out to the client structure before all the
    // edicts are wiped.
    virtual void SaveClientServerEntityData(void) override;
    // Fetch client data that was stored between previous ServerEntity wipe session.
    virtual void FetchClientServerEntityData(ServerEntity* ent) override;

private:

};

#endif // __SVGAME_GAMEMODES_DEFAULTGAMEMODE_H__