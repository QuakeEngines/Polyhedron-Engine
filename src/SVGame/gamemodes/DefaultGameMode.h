/*
// LICENSE HERE.

//
// DefaultGameMode.h
//
// Default game mode to run, allows for all sorts of stuff.
//
*/
#pragma once 

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
    virtual qboolean GetEntityTeamName(SynchedEntityBase* ent, std::string &teamName) override;
    virtual qboolean OnSameTeam(SynchedEntityBase* ent1, SynchedEntityBase* ent2) override;
    virtual qboolean CanDamage(SynchedEntityBase* targ, SynchedEntityBase* inflictor) override;
    virtual BaseEntityVector FindBaseEnitiesWithinRadius(const vec3_t& origin, float radius, uint32_t excludeSolidFlags) override;

    //
    // Combat GameMode actions.
    //
    virtual void EntityKilled(SynchedEntityBase* target, SynchedEntityBase* inflictor, SynchedEntityBase* attacker, int32_t damage, vec3_t point) override;
    virtual void InflictDamage(SynchedEntityBase* target, SynchedEntityBase* inflictor, SynchedEntityBase* attacker, const vec3_t& dmgDir, const vec3_t& point, const vec3_t& normal, int32_t damage, int32_t knockBack, int32_t dflags, int32_t mod) override;
    virtual void InflictRadiusDamage(SynchedEntityBase* inflictor, SynchedEntityBase* attacker, float damage, SynchedEntityBase* ignore, float radius, int32_t mod) override;
    virtual void SetCurrentMeansOfDeath(int32_t meansOfDeath) override;
    virtual const int32_t& GetCurrentMeansOfDeath() override;

    //
    // Random Gameplay Functions.
    //
    virtual void SpawnClientCorpse(SynchedEntityBase* ent) override;
    virtual void SpawnTempDamageEntity(int32_t type, const vec3_t& origin, const vec3_t& normal, int32_t damage) override;
    virtual vec3_t CalculateDamageVelocity(int32_t damage) override;
    
    //
    // Client related callbacks.
    // 
    virtual qboolean ClientConnect(ServerEntity *serverEntity, char *userinfo) override;
    virtual void ClientBegin(ServerEntity *serverEntity) override;
    virtual void ClientBeginServerFrame(ServerEntity * serverEntity) override;
    virtual void ClientEndServerFrame(ServerEntity *serverEntity) override;
    virtual void ClientDisconnect(ServerEntity  * serverEntity) override;
    virtual void ClientUserinfoChanged(PlayerEntity* playerEntity, char *userinfo) override;
    virtual void ClientUpdateObituary(SynchedEntityBase* self, SynchedEntityBase* inflictor, SynchedEntityBase* attacker) override;

    //
    // Client related functions/utilities.
    // 
    virtual void InitializeClientPersistentData(ServerClient* client) override;
    virtual void InitializeClientRespawnData(ServerClient *client) override;

    virtual void SelectClientSpawnPoint(ServerEntity* ent, vec3_t& origin, vec3_t& angles, const std::string &classname) override;
    virtual void PutClientInServer(ServerEntity *ent) override;
    virtual void RespawnClient(ServerEntity* ent) override;

    // Some information that should be persistant, like health,
    // is still stored in the edict structure, so it needs to
    // be mirrored out to the client structure before all the
    // edicts are wiped.
    virtual void SaveClientEntityData(void) override;
    // Fetch client data that was stored between previous entity wipe session.
    virtual void FetchClientEntityData(ServerEntity* ent) override;

private:

};