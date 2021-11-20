// LICENSE HERE.

//
// misc.c
//
//
// Contains misc definitions.
//

#include "g_local.h"         // Include SVGame funcs.
#include "entities.h"
#include "utils.h"           // Include Utilities funcs.
#include "effects.h"

// Game Mode interface.
#include "gamemodes/IGameMode.h"

// Class Entities.
#include "entities/base/ServerGameEntity.h"
#include "entities/base/PlayerClient.h"
#include "entities/base/DebrisServerEntity.h"
#include "entities/base/GibServerEntity.h"


//=================
// SVG_ThrowClientHead
// 
// Throws a gib ServerEntity around at the location of "self".
//=================
void SVG_ThrowGib(ServerGameEntity*self, const char *gibname, int damage, int type)
{
    // Create a gib ServerEntity.
    GibServerEntity* gibClassServerEntity = SVG_CreateClassServerEntity<GibServerEntity>();

    // Set size.
    vec3_t size = vec3_scale(self->GetSize(), 0.5f);
    gibClassServerEntity->SetSize(size);
    
    // Generate the origin to start from.
    vec3_t origin = self->GetAbsoluteMin() + self->GetSize();

    // Add some random values to it, so they all differ.
    origin.x += crandom() * size.x;
    origin.y += crandom() * size.y;
    origin.z += crandom() * size.z;

    // Set the origin.
    gibClassServerEntity->SetOrigin(origin);

    // Set the model.
    gibClassServerEntity->SetModel(gibname);

    // Set solid and other properties.
    gibClassServerEntity->SetSolid(Solid::Not);
    gibClassServerEntity->SetEffects(gibClassServerEntity->GetEffects() | ServerEntityEffectType::Gib);
    gibClassServerEntity->SetFlags(gibClassServerEntity->GetFlags() | ServerEntityFlags::NoKnockBack);
    gibClassServerEntity->SetTakeDamage(TakeDamage::Yes);
    gibClassServerEntity->SetDieCallback(&GibServerEntity::GibServerEntityDie);

    // Default velocity scale for non organic materials.
    float velocityScale = 1.f;

    // Is it an organic gib type?
    if (type == GIB_ORGANIC) {
        // Then we pick a different movetype ;-)
        gibClassServerEntity->SetMoveType(MoveType::Toss);

        // Most of all, we setup a touch callback too ofc.
        gibClassServerEntity->SetTouchCallback(&GibServerEntity::GibServerEntityTouch);

        // Adjust the velocity scale.
        velocityScale = 0.5f;
    } else {
        // Pick a different movetype, bouncing. No touch callback :)
        gibClassServerEntity->SetMoveType(MoveType::Bounce);
    }

    // Comment later...
    vec3_t velocityDamage = game.gameMode->CalculateDamageVelocity(damage);

    // Reassign 'velocityDamage' and multiply 'self->GetVelocity' to scale, and then 
    // adding it on to 'velocityDamage' its old value.
    vec3_t gibVelocity = vec3_fmaf(self->GetVelocity(), velocityScale, velocityDamage);

    // Be sure to clip our velocity, just in case.
    gibClassServerEntity->ClipGibVelocity(velocityDamage);

    // Last but not least, set our velocity.
    gibClassServerEntity->SetVelocity(velocityDamage);

    // Generate angular velocity.
    vec3_t angularVelocity = {
        random() * 600.f,
        random() * 600.f,
        random() * 600.f
    };

    // Set angular velocity.
    gibClassServerEntity->SetAngularVelocity(angularVelocity);

    // Setup the Gib think function and its think time.
    gibClassServerEntity->SetThinkCallback(&ServerGameEntity::SVGBaseServerEntityThinkRemove);
    gibClassServerEntity->SetNextThinkTime(level.time + 10 + random() * 10);

    // Link ServerEntity into the world.
    gibClassServerEntity->LinkServerEntity();
}

//=================
// SVG_ThrowClientHead
// 
// Tosses a client head ServerEntity around.
//=================
void SVG_ThrowClientHead(PlayerClient* self, int damage) {
    // Set model based on randomness.
    if (rand() & 1) {
        self->SetModel("models/objects/gibs/head2/tris.md2");
        self->SetSkinNumber(1); // second skin is player
    } else {
        // WID: This just seems odd to me.. but hey. Sure.
        self->SetModel("models/objects/gibs/skull/tris.md2");
        self->SetSkinNumber(0); // Original skin.
    }

    // Let's fetch origin, add some Z, get going.
    vec3_t origin = self->GetOrigin();
    origin.z += 32;
    self->SetOrigin(origin);

    // Set frame back to 0.
    self->SetFrame(0);

    // Set mins/maxs.
    self->SetMins(vec3_t{ -16.f, -16.f, 0.f });
    self->SetMaxs(vec3_t{ 16.f, 16.f, 0.f });

    // Set MoveType and Solid.
    self->SetSolid(Solid::Not);
    self->SetMoveType(MoveType::Bounce);

    // Other properties.
    self->SetTakeDamage(TakeDamage::No);
    self->Base::SetEffects(ServerEntityEffectType::Gib);
    self->Base::SetSound(0);
    self->SetFlags(ServerEntityFlags::NoKnockBack);

    // Calculate the velocity for the given damage, fetch its scale.
    vec3_t velocityDamage = game.gameMode->CalculateDamageVelocity(damage);

    // Add the velocityDamage up to the current velocity.
    self->SetVelocity(self->GetVelocity() + velocityDamage);

    // Bodies in the queue don't have a client anymore.
    ServerClient* client = self->GetClient();
    if (client) {
        client->animation.priorityAnimation = PlayerAnimation::Death;
        client->animation.endFrame = self->GetFrame();
    } else {
        self->SetThinkCallback(nullptr);
        self->SetNextThinkTime(0);
    }

    // Relink ServerEntity, this'll make it... be "not around", but in the "queue".
    self->LinkServerEntity();
}

//=================
// SVG_ThrowDebris
// 
// Thorws a debris piece around.
//=================
void SVG_ThrowDebris(ServerGameEntity *self, const char *modelname, float speed, const vec3_t &origin) // C++20: STRING: Added const to char*
{
    // Chunk ServerEntity.
    ServerGameEntity* chunkServerEntity = SVG_CreateClassServerEntity<DebrisServerEntity>();

    // Set the origin.
    chunkServerEntity->SetOrigin(origin);

    // Set the model.
    chunkServerEntity->SetModel(modelname);

    // Calculate and set the velocity.
    vec3_t velocity = {
        100.f * crandom(),
        100.f * crandom(),
        100.f + 100.f * crandom()
    };
    chunkServerEntity->SetVelocity(vec3_fmaf(self->GetVelocity(), speed, velocity));

    // Set Movetype and Solid.
    chunkServerEntity->SetMoveType(MoveType::Bounce);
    chunkServerEntity->SetSolid(Solid::Not);

    // Calculate and set angular velocity.
    vec3_t angularVelocity = {
        random() * 600,
        random() * 600,
        random() * 600
    };
    chunkServerEntity->SetAngularVelocity(angularVelocity);

    // Set up the thinking machine.
    chunkServerEntity->SetThinkCallback(&ServerGameEntity::SVGBaseServerEntityThinkRemove);
    chunkServerEntity->SetNextThinkTime(level.time + 5 + random() * 5);

    // Setup the other properties.
    chunkServerEntity->SetFrame(0);
    chunkServerEntity->SetFlags(0);
    chunkServerEntity->SetTakeDamage(TakeDamage::Yes);
    chunkServerEntity->SetDieCallback(&DebrisServerEntity::DebrisServerEntityDie);

    // Link it up.
    chunkServerEntity->LinkServerEntity();
}

//=================
// SVG_BecomeExplosion1
// 
// Sends an explosion effect as a TE cmd, and queues the ServerEntity up for removal.
//=================
void SVG_BecomeExplosion1(ServerGameEntity *self)
{
    // Fetch origin.
    vec3_t origin = self->GetOrigin();

    // Execute a TE effect.
    gi.WriteByte(SVG_CMD_TEMP_ServerEntity);
    gi.WriteByte(TempServerEntityEvent::Explosion1);
    gi.WriteVector3(origin);
    gi.Multicast(origin, MultiCast::PVS);

    // Queue for removal.
    //self->Remove();
    //SVG_FreeServerEntity(self->GetServerServerEntity());
}

//=================
// SVG_BecomeExplosion2
// 
// Sends an explosion effect as a TE cmd, and queues the ServerEntity up for removal.
//=================
void SVG_BecomeExplosion2(ServerGameEntity*self)
{
    // Fetch origin.
    vec3_t origin = self->GetOrigin();

    // Execute a TE effect.
    gi.WriteByte(SVG_CMD_TEMP_ServerEntity);
    gi.WriteByte(TempServerEntityEvent::Explosion2);
    gi.WriteVector3(origin);
    gi.Multicast(origin, MultiCast::PVS);
}