/*
// LICENSE HERE.

//
// BodyCorpse.cpp
//
//
*/
#include "../../ServerGameLocal.h"              // SVGame.
#include "../../Effects.h"              // Effects.
#include "../../Entities.h"             // Entities.
#include "../../player/client.h"        // Player Client functions.
#include "../../player/animations.h"    // Include Player Client Animations.
#include "../../player/view.h"          // Include Player View functions..
#include "../../Utilities.h"                // Util funcs.

// Class Entities.
#include "../base/SynchedEntityBase.h"
#include "../base/SynchBasedEntity.h"
#include "BodyCorpse.h"

// Constructor/Deconstructor.
BodyCorpse::BodyCorpse(ServerEntity * svEntity)
    : SynchedBasedEntity(svEntity) {

}
BodyCorpse::~BodyCorpse() {

}

//
//===============
// PlayerEntity::Precache
//
//===============
//
void BodyCorpse::Precache() {
    Base::Precache();
}

//
//===============
// PlayerEntity::Spawn
//
//===============
//
void BodyCorpse::Spawn() {
    // Spawn.
    Base::Spawn();
}

//
//===============
// BodyCorpse::Respawn
//
//===============
//
void BodyCorpse::Respawn() {
    Base::Respawn();
}

//
//===============
// BodyCorpse::PostSpawn
//
//===============
//
void BodyCorpse::PostSpawn() {
    Base::PostSpawn();
}

//
//===============
// BodyCorpse::Think
//
//===============
//
void BodyCorpse::Think() {
    // Parent class Think.
    Base::Think();
}

//===============
// BodyCorpse::SpawnKey
//
// BodyCorpse spawn key handling.
//===============
void BodyCorpse::SpawnKey(const std::string& key, const std::string& value) {
    // Parent class spawnkey.
    Base::SpawnKey(key, value);
}

//===============
// BodyCorpse::BodyCorpseTouch
//
// 'Touch' callback, I am unsure what to use it for but I can imagine it being...
// like picking up their items or something? I suppose we could do that...
//===============
void BodyCorpse::BodyCorpseTouch(SynchedEntityBase * self, SynchedEntityBase * other, cplane_t* plane, csurface_t* surf) {

}

//===============
// BodyCorpse::BodyCorpseDie
//
// Spawn gibs to make things gore like :P
//===============
void BodyCorpse::BodyCorpseDie(SynchedEntityBase * inflictor, SynchedEntityBase * attacker, int damage, const vec3_t& point) {
    //int n;

    // In case health is low enough...
    if (GetHealth() < -40) {
        // Play sound.
        SVG_Sound(this, CHAN_BODY, gi.SoundIndex("misc/udeath.wav"), 1, ATTN_NORM, 0);

        // Toss gibs.
        for (int32_t i = 0; i < 4; i++)
            SVG_ThrowGib(this, "models/objects/gibs/sm_meat/tris.md2", damage, GIB_ORGANIC);

        // Ensure its origin goes -48, it is a lame hack but hey...
        vec3_t origin = GetOrigin();
        origin.z -= 48;
        SetOrigin(origin);
    
        // Toss head around.
        //SVG_ThrowClientHead(self, damage);

        // Ensure we take no damage no more.
        SetTakeDamage(TakeDamage::No);
    }


    // Set the ehrm.. think free thing.
    //SetThinkCallback(&SynchedEntityBase.h::SVGBaseEntityThinkRemove);
    //SetNextThinkTime(level.time + FRAMETIME);
    // Remove body.
    //SetModelIndex(0);
    Remove();
}