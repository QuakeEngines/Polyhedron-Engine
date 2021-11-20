/*
// LICENSE HERE.

//
// GibServerEntity.cpp
//
//
*/
#include "../../g_local.h"              // SVGame.
#include "../../effects.h"              // Effects.
#include "../../entities.h"             // Entities.
#include "../../player/client.h"        // Player Client functions.
#include "../../player/animations.h"    // Include Player Client Animations.
#include "../../player/view.h"          // Include Player View functions..
#include "../../utils.h"                // Util funcs.

// Class Entities.
#include "../base/ServerGameEntity.h"
#include "GibServerEntity.h"

// Constructor/Deconstructor.
GibServerEntity::GibServerEntity(ServerEntity* svServerEntity)
    : ServerGameEntity(svServerEntity) {

}
GibServerEntity::~GibServerEntity() {

}

//
//===============
// PlayerClient::Precache
//
//===============
//
void GibServerEntity::Precache() {
    Base::Precache();
}

//
//===============
// PlayerClient::Spawn
//
//===============
//
void GibServerEntity::Spawn() {
    // Spawn.
    Base::Spawn();
}

//
//===============
// GibServerEntity::Respawn
//
//===============
//
void GibServerEntity::Respawn() {
    Base::Respawn();
}

//
//===============
// GibServerEntity::PostSpawn
//
//===============
//
void GibServerEntity::PostSpawn() {
    Base::PostSpawn();
}

//
//===============
// GibServerEntity::Think
//
//===============
//
void GibServerEntity::Think() {
    // Parent class Think.
    Base::Think();
}

//===============
// GibServerEntity::SpawnKey
//
// GibServerEntity spawn key handling.
//===============
void GibServerEntity::SpawnKey(const std::string& key, const std::string& value) {
    // Parent class spawnkey.
    Base::SpawnKey(key, value);
}

//===============
// GibServerEntity::ClipGibVelocity
//
// Clips gib velocity, in case it goes out of control that is.
//===============
void GibServerEntity::ClipGibVelocity(vec3_t &velocity) {
    // Y Axis.
    if (velocity.x < -300)
        velocity.x = -300;
    else if (velocity.x > 300)
        velocity.x = 300;
    
    // Y Axis.
    if (velocity.y < -300)
        velocity.y = -300;
    else if (velocity.y > 300)
        velocity.y = 300;

    // Z Axis.
    if (velocity.z < 200)
        velocity.z = 200;
    else if (velocity.z > 500)
        velocity.y = 500;
}

//===============
// GibServerEntity::CalculateVelocityForDamage
//
// 'other' is the actual ServerEntity that is spawning these gibs.
//===============
//float GibServerEntity::CalculateVelocityForDamage(ServerGameEntity *other, const int32_t damage, vec3_t &velocity) {
//    // Calculate the velocity based on the damage passed over.
//    velocity = {
//        100.f * crandom(),
//        100.f * crandom(),
//        200.f + 100.f * random()
//    };
//
//    // Set velocity scale value based on the intensity of the amount of 'damage'.
//    float velocityScale = 1.2f;
//    if (damage < 50)
//        velocityScale = 0.7f;
//    
//    // Calculate velocity for damage.
//    velocity = vec3_scale(velocity, 0.7);
//
//    // Return.
//    return velocityScale;
//}

//===============
// GibServerEntity::GibServerEntityThink
//
//===============
void GibServerEntity::GibServerEntityThink() {
    // Increase frame and set a new think time.
    SetFrame(GetFrame() + 1);
    SetNextThinkTime(level.time + FRAMETIME);

    // Play frames for these meshes, cut the crap at frame 10.
    if (GetFrame() == 10) {
        SetThinkCallback(&ServerGameEntity::SVGBaseServerEntityThinkRemove);
        SetNextThinkTime(level.time + 8 + random() * 10);
    }
}

//===============
// GibServerEntity::GibServerEntityTouch
//
//===============
void GibServerEntity::GibServerEntityTouch(ServerGameEntity* self, ServerGameEntity* other, cplane_t* plane, csurface_t* surf) {
    vec3_t  right;

    if (!GetGroundServerEntity())
        return;

    // Reset touch callback to nullptr.
    SetTouchCallback(nullptr);

    // Did we get a plane passed?
    if (plane) {
        SVG_Sound(this, CHAN_VOICE, gi.SoundIndex("misc/fhit3.wav"), 1, ATTN_NORM, 0);

        vec3_t normalAngles = vec3_euler(plane->normal);
        vec3_vectors(normalAngles, NULL, &right, NULL);
        vec3_t right = vec3_euler(GetState().angles);

        if (GetModelIndex() == sm_meat_index) {
            SetFrame(GetFrame() + 1);
            SetThinkCallback(&GibServerEntity::GibServerEntityThink);
            SetNextThinkTime(level.time + FRAMETIME);
        }
    }
}

//===============
// GibServerEntity::GibServerEntityDie
//
// Savely call Remove so it queues up for removal without causing 
// serverEntity/classServerEntity conflicts.
//===============
void GibServerEntity::GibServerEntityDie(ServerGameEntity* inflictor, ServerGameEntity* attacker, int damage, const vec3_t& point) {
    // Time to queue it for removal.
    Remove();
}