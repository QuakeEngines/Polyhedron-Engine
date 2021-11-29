/*
Copyright (C) 1997-2001 Id Software, Inc.

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License along
with this program; if not, write to the Free Software Foundation, Inc.,
51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*/
#include "g_local.h"
#include "Entities.h"
#include "ChaseCamera.h"

#include "Entities/Base/SynchedEntityBase.h"
#include "Entities/Base/PlayerEntity.h"

void SVG_UpdateChaseCam(PlayerEntity *ent)
{
    ServerGameEntity* target;


    // Fetch owner vector.
    vec3_t vecOwner = target->GetState().origin;

    // is our chase target gone?
    if (!ent->GetClient()->chaseTarget->IsInUse()
        || ent->GetClient()->chaseTarget->GetClient()->respawn.isSpectator) {
        ServerGameEntity *oldTarget = ent->GetClient()->chaseTarget;
        SVG_ChaseNext(ent);
        if (ent->GetClient()->chaseTarget == oldTarget) {
            ent->GetClient()->chaseTarget = nullptr;
            ent->GetClient()->playerState.pmove.flags &= ~PMF_NO_PREDICTION;
            return;
        }
    }

    target = ent->GetClient()->chaseTarget;

    vecOwner.z += target->GetViewHeight();

    vec3_t newAngles = target->GetClient()->aimAngles;
    vec3_t angles = target->GetClient()->aimAngles;
    vec3_t forward, right;

    if (angles[vec3_t::Pitch] > 56)
        angles[vec3_t::Pitch] = 56;
    AngleVectors(angles, &forward, &right, NULL);
    VectorNormalize(forward);

    vec3_t o;
    vecOwner = vec3_fmaf(forward, -30, o);

    if (o[2] < target->GetState().origin.z + 20)
        o[2] = target->GetState().origin.z + 20;

    // jump animation lifts
    if (!target->GetGroundEntity())
        o[2] += 16;

    SVGTrace trace = SVG_Trace(vecOwner, vec3_zero(), vec3_zero(), o, target, CONTENTS_MASK_SOLID);

    vec3_t goal = trace.endPosition;

    goal = vec3_fmaf(forward, 2, goal);

    // pad for floors and ceilings
    o = goal;

    o[2] += 6;
    trace = SVG_Trace(goal, vec3_zero(), vec3_zero(), o, target, CONTENTS_MASK_SOLID);
    if (trace.fraction < 1) {
        VectorCopy(trace.endPosition, goal);
        goal[2] -= 6;
    }

    VectorCopy(goal, o);
    o[2] -= 6;
    trace = SVG_Trace(goal, vec3_zero(), vec3_zero(), o, target, CONTENTS_MASK_SOLID);
    if (trace.fraction < 1) {
        VectorCopy(trace.endPosition, goal);
        goal[2] += 6;
    }

    if (target->GetDeadFlag())
        ent->GetClient()->playerState.pmove.type = EnginePlayerMoveType::Dead;
    else
        ent->GetClient()->playerState.pmove.type = EnginePlayerMoveType::Freeze;

    ent->SetOrigin(goal);

    ent->GetClient()->playerState.pmove.deltaAngles = target->GetClient()->aimAngles - ent->GetClient()->respawn.commandViewAngles;

    if (target->GetDeadFlag()) {
        ent->GetClient()->playerState.pmove.viewAngles[vec3_t::Roll] = 40;
        ent->GetClient()->playerState.pmove.viewAngles[vec3_t::Pitch] = -15;
        ent->GetClient()->playerState.pmove.viewAngles[vec3_t::Yaw] = target->GetClient()->killerYaw;
    } else {
        ent->GetClient()->playerState.pmove.viewAngles = target->GetClient()->aimAngles;
        ent->GetClient()->aimAngles = target->GetClient()->aimAngles;
    }

    ent->SetViewHeight(0);
    ent->GetClient()->playerState.pmove.flags |= PMF_NO_PREDICTION;
    ent->LinkEntity();
}

void SVG_ChaseNext(PlayerEntity *ent)
{
    //ServerClient* client = ent->GetClient();

    //// Return if we got none at all to start with.
    //if (!client->chaseTarget)
    //    return;

    //ServerGameEntity *nextChaseEntity = nullptr;
    //
    //int32_t startClientNumber = client->chaseTarget->GetNumber();
    //int32_t i = client->chaseTarget - serverGameEntities[client->chaseTarget->GetNumber()];
    //do {
    //    i++;
    //    if (i > maximumClients->value)
    //        i = 1;
    //    nextChaseEntity = serverGameEntities[startClientNumber + i];
    //    if (!nextChaseEntity->IsInUse())
    //        continue;
    //    if (!nextChaseEntity->GetClient()->respawn.isSpectator)
    //        break;
    //} while (nextChaseEntity != client->chaseTarget);

    //client->chaseTarget = nextChaseEntity;
    //client->updateChase = true;
}

void SVG_ChasePrev(PlayerEntity*ent)
{
    //int i;
    //ServerGameEntity *e;
    //ServerClient* client = ent->GetClient();

    //if (!client->chaseTarget)
    //    return;

    //i = client->chaseTarget - serverGameEntities[0];
    //do {
    //    i--;
    //    if (i < 1)
    //        i = maximumClients->value;
    //    e = serverGameEntities[] + i;
    //    if (!e->inUse)
    //        continue;
    //    if (!e->client->respawn.isSpectator)
    //        break;
    //} while (e != client->chaseTarget);

    //client->chaseTarget = e;
    //client->updateChase = true;
}

void SVG_GetChaseTarget(PlayerEntity *ent)
{
    //int i;
    //ServerEntity *other;
    //ServerClient* client = ent->GetClient();

    //for (i = 1; i <= maximumClients->value; i++) {
    //    other = g_entities + i;
    //    if (other->inUse && !other->client->respawn.isSpectator) {
    //        client->chaseTarget = other;
    //        client->updateChase = true;
    //        SVG_UpdateChaseCam(ent);
    //        return;
    //    }
    //}
    //gi.CenterPrintf(ent->GetEntityServerHandle(), "No other players to chase.");
}

