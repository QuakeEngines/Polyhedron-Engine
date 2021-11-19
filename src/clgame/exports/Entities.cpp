#include "../clg_local.h"

#include "../clg_effects.h"
#include "../clg_entities.h"
#include "../clg_input.h"
#include "../clg_main.h"
#include "../clg_media.h"
#include "../clg_parse.h"
#include "../clg_predict.h"
#include "../clg_screen.h"
#include "../clg_tents.h"
#include "../clg_view.h"

#include "shared/interfaces/IClientGameExports.h"
#include "../ClientGameExports.h"
#include "Entities.h"

// WID: TODO: Gotta fix this one too.
extern qhandle_t cl_sfx_footsteps[4];

//---------------
// ClientGameEntities::Event
//
//---------------
void ClientGameEntities::Event(int32_t number) {
    clientServerEntity* cent = &cs->entities[number];

    // EF_TELEPORTER acts like an event, but is not cleared each frame
    if ((cent->current.effects & ServerEntityEffectType::Teleporter) && CLG_FRAMESYNC) {
        CLG_TeleporterParticles(cent->current.origin);
    }

    switch (cent->current.eventID) {
    case ServerEntityEvent::ItemRespawn:
        clgi.S_StartSound(NULL, number, CHAN_WEAPON, clgi.S_RegisterSound("items/respawn1.wav"), 1, ATTN_IDLE, 0);
        CLG_ItemRespawnParticles(cent->current.origin);
        break;
    case ServerEntityEvent::PlayerTeleport:
        clgi.S_StartSound(NULL, number, CHAN_WEAPON, clgi.S_RegisterSound("misc/tele1.wav"), 1, ATTN_IDLE, 0);
        CLG_TeleportParticles(cent->current.origin);
        break;
    case ServerEntityEvent::Footstep:
        if (cl_footsteps->integer)
            clgi.S_StartSound(NULL, number, CHAN_BODY, cl_sfx_footsteps[rand() & 3], 1, ATTN_NORM, 0);
        break;
    case ServerEntityEvent::FallShort:
        clgi.S_StartSound(NULL, number, CHAN_AUTO, clgi.S_RegisterSound("player/land1.wav"), 1, ATTN_NORM, 0);
        break;
    case ServerEntityEvent::Fall:
        clgi.S_StartSound(NULL, number, CHAN_AUTO, clgi.S_RegisterSound("*fall2.wav"), 1, ATTN_NORM, 0);
        break;
    case ServerEntityEvent::FallFar:
        clgi.S_StartSound(NULL, number, CHAN_AUTO, clgi.S_RegisterSound("*fall1.wav"), 1, ATTN_NORM, 0);
        break;
    }
}