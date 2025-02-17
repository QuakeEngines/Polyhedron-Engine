/*
Copyright (C) 1997-2001 Id Software, Inc.
Copyright (C) 2019, NVIDIA CORPORATION. All rights reserved.

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

#include "Server.h"

/*
=============================================================================

Encode a client frame onto the network channel

=============================================================================
*/

/*
=============
SV_EmitPacketEntities

Writes a delta update of a PackedEntity list to the message.
=============
*/
static void SV_EmitPacketEntities(client_t         *client,
                                  ClientFrame   *from,
                                  ClientFrame   *to,
                                  int              clientEntityNum)
{
    PackedEntity *newent;
    const PackedEntity *oldent;
    unsigned i, oldindex, newindex, from_num_entities;
    int oldnum, newnum;
    EntityStateMessageFlags flags;

    if (!from)
        from_num_entities = 0;
    else
        from_num_entities = from->num_entities;

    newindex = 0;
    oldindex = 0;
    oldent = newent = NULL;
    while (newindex < to->num_entities || oldindex < from_num_entities) {
        if (newindex >= to->num_entities) {
            newnum = 9999;
        } else {
            i = (to->first_entity + newindex) % svs.num_entities;
            newent = &svs.entities[i];
            newnum = newent->number;
        }

        if (oldindex >= from_num_entities) {
            oldnum = 9999;
        } else {
            i = (from->first_entity + oldindex) % svs.num_entities;
            oldent = &svs.entities[i];
            oldnum = oldent->number;
        }

        if (newnum == oldnum) {
            // Delta update from old position. Because the force parm is false,
            // this will not result in any bytes being emitted if the entity has
            // not changed at all. Note that players are always 'newentities',
            // this updates their oldOrigin always and prevents warping in case
            // of packet loss.
            flags = client->esFlags;
            if (newnum <= client->maximumClients) {
                flags = (EntityStateMessageFlags)(flags | MSG_ES_NEWENTITY);
            }
            if (newnum == clientEntityNum) {
                flags = (EntityStateMessageFlags)(flags | MSG_ES_FIRSTPERSON);
                newent->origin = oldent->origin; // VectorCopy(oldent->origin, newent->origin);
                newent->angles = oldent->angles; // VectorCopy(oldent->angles, newent->angles);
            }

            MSG_WriteDeltaEntity(oldent, newent, flags);
            oldindex++;
            newindex++;
            continue;
        }

        if (newnum < oldnum) {
            // this is a new entity, send it from the baseline
            flags = (EntityStateMessageFlags)(client->esFlags | MSG_ES_FORCE | MSG_ES_NEWENTITY); // CPP: Cast
            oldent = client->entityBaselines[newnum >> SV_BASELINES_SHIFT];
            if (oldent) {
                oldent += (newnum & SV_BASELINES_MASK);
            } else {
                oldent = &nullEntityState;
            }
            if (newnum == clientEntityNum) {
                flags = (EntityStateMessageFlags)(flags | MSG_ES_FIRSTPERSON); // CPP: Cast flags |= MSG_ES_FIRSTPERSON;
                newent->origin = oldent->origin; // VectorCopy(oldent->origin, newent->origin);
                newent->angles = oldent->angles; // VectorCopy(oldent->angles, newent->angles);
            }

            MSG_WriteDeltaEntity(oldent, newent, flags);
            newindex++;
            continue;
        }

        if (newnum > oldnum) {
            // the old entity isn't present in the new message
            MSG_WriteDeltaEntity(oldent, NULL, MSG_ES_FORCE);
            oldindex++;
            continue;
        }
    }

    MSG_WriteShort(0);      // end of packetentities
}

static ClientFrame *get_last_frame(client_t *client)
{
    ClientFrame *frame;

    if (client->lastFrame <= 0) {
        // client is asking for a retransmit
        client->framesNoDelta++;
        return NULL;
    }

    client->framesNoDelta = 0;

    if (client->frameNumber - client->lastFrame >= UPDATE_BACKUP) {
        // client hasn't gotten a good message through in a long time
        Com_DPrintf("%s: delta request from out-of-date packet.\n", client->name);
        return NULL;
    }

    // we have a valid message to delta from
    frame = &client->frames[client->lastFrame & UPDATE_MASK];
    if (frame->number != client->lastFrame) {
        // but it got never sent
        Com_DPrintf("%s: delta request from dropped frame.\n", client->name);
        return NULL;
    }

    if (svs.next_entity - frame->first_entity > svs.num_entities) {
        // but entities are too old
        Com_DPrintf("%s: delta request from out-of-date entities.\n", client->name);
        return NULL;
    }

    return frame;
}

/*
==================
SV_WriteFrameToClient_Enhanced
==================
*/
void SV_WriteFrameToClient(client_t *client) {
 
    ClientFrame  *frame, *oldframe;
    PlayerState *oldPlayerState;
    uint32_t        extraflags;
    int             delta, suppressed;
    byte            *b1, *b2;
    PlayerStateMessageFlags    psFlags;
    int             clientEntityNum;

    // this is the frame we are creating
    frame = &client->frames[client->frameNumber & UPDATE_MASK];

    // this is the frame we are delta'ing from
    oldframe = get_last_frame(client);
    if (oldframe) {
        oldPlayerState = &oldframe->playerState;
        delta = client->frameNumber - client->lastFrame;
    } else {
        oldPlayerState = NULL;
        delta = 31;
    }

    // first byte to be patched
    b1 = (byte*)SZ_GetSpace(&msg_write, 1); // CPP: Cast

    MSG_WriteLong((client->frameNumber & FRAMENUM_MASK) | (delta << FRAMENUM_BITS));

    // second byte to be patched
    b2 = (byte*)SZ_GetSpace(&msg_write, 1); // CPP: Cast

    // send over the areaBits
    MSG_WriteByte(frame->areaBytes);
    MSG_WriteData(frame->areaBits, frame->areaBytes);

    // ignore some parts of playerstate if not recording demo
    psFlags = (PlayerStateMessageFlags)0; // CPP: Cast
    if (frame->playerState.pmove.type < EnginePlayerMoveType::Dead) {
        if (!(frame->playerState.pmove.flags & PMF_NO_PREDICTION)) {
            psFlags = (PlayerStateMessageFlags)(psFlags | MSG_PS_IGNORE_VIEWANGLES);  // CPP: Cast
        }
    } else {
        // lying dead on a rotating platform?
        psFlags = (PlayerStateMessageFlags)(psFlags | MSG_PS_IGNORE_DELTAANGLES);  // CPP: Cast
    }

    // Fetch client entity number.
    clientEntityNum = 0;
    if (frame->playerState.pmove.type < EnginePlayerMoveType::Dead) {
        clientEntityNum = frame->clientNumber + 1;
    }
    suppressed = client->frameFlags;


    // delta encode the playerstate
    extraflags = MSG_WriteDeltaPlayerstate(oldPlayerState, &frame->playerState, psFlags);

    int clientNumber = oldframe ? oldframe->clientNumber : 0;
    if (clientNumber != frame->clientNumber) {
        extraflags |= EPS_CLIENTNUM;
        MSG_WriteByte(frame->clientNumber);
    }

    // save 3 high bits of extraflags
    *b1 = svc_frame | (((extraflags & 0x70) << 1));

    // save 4 low bits of extraflags
    *b2 = (suppressed & SUPPRESSCOUNT_MASK) |
          ((extraflags & 0x0F) << SUPPRESSCOUNT_BITS);

    client->suppressCount = 0;
    client->frameFlags = 0;

    // delta encode the entities
    SV_EmitPacketEntities(client, oldframe, frame, clientEntityNum);
}


/*
=============================================================================

Build a client frame structure

=============================================================================
*/

/*
=============
SV_BuildClientFrame

Decides which entities are going to be visible to the client, and
copies off the playerstat and areaBits.
=============
*/
void SV_BuildClientFrame(client_t *client)
{
    int         e;
    vec3_t      org;
    Entity     *ent;
    Entity     *clent;
    ClientFrame  *frame;
    PackedEntity *state;
    PlayerState  *ps;
	EntityState  es;
	int         l;
    int         clientarea, clientcluster;
    mleaf_t     *leaf;
    static byte        clientphs[VIS_MAX_BYTES];
    static byte        clientpvs[VIS_MAX_BYTES];
    qboolean    ent_visible;
    int cull_nonvisible_entities = Cvar_Get("sv_cull_nonvisible_entities", "1", CVAR_CHEAT)->integer;

    clent = client->edict;
    if (!clent->client)
        return;        // not in game yet

    // this is the frame we are creating
    frame = &client->frames[client->frameNumber & UPDATE_MASK];
    frame->number = client->frameNumber;
    frame->sentTime = com_eventTime; // save it for ping calc later
    frame->latency = -1; // not yet acked

    client->framesSent++;

    // find the client's PVS
    ps = &clent->client->playerState;
    org = ps->pmove.origin + ps->pmove.viewOffset;

    leaf = CM_PointLeaf(client->cm, org);
    clientarea = CM_LeafArea(leaf);
    clientcluster = CM_LeafCluster(leaf);

    // calculate the visible areas
    frame->areaBytes = CM_WriteAreaBits(client->cm, frame->areaBits, clientarea);

    // grab the current PlayerState
    frame->playerState = *ps;
    //MSG_PackPlayer(&frame->playerState, ps);

    // Grab the current clientNumber
    // MSG: NOTE: !! In case of seeing a client model where one should not
    // it may be worth investigating this piece of code. 
    frame->clientNumber = client->number;
    //if (g_features->integer & GMF_CLIENTNUM) {
    //    frame->clientNumber = clent->client->clientNumber;
    //} else {
    //    frame->clientNumber = client->number;
    //}

	if (clientcluster >= 0)
	{
		CM_FatPVS(client->cm, clientpvs, org, DVIS_PVS2);
		client->lastValidCluster = clientcluster;
	}
	else
	{
		BSP_ClusterVis(client->cm->cache, clientpvs, client->lastValidCluster, DVIS_PVS2);
	}

    BSP_ClusterVis(client->cm->cache, clientphs, clientcluster, DVIS_PHS);

    // build up the list of visible entities
    frame->num_entities = 0;
    frame->first_entity = svs.next_entity;

    for (e = 1; e < client->pool->numberOfEntities; e++) {
        ent = EDICT_POOL(client, e);

        // ignore entities not in use
        if (!ent->inUse) {
            continue;
        }

        // ignore ents without visible models
        if (ent->serverFlags & EntityServerFlags::NoClient)
            continue;

        // ignore ents without visible models unless they have an effect
        if (!ent->state.modelIndex && !ent->state.effects && !ent->state.sound) {
            if (!ent->state.eventID) {
                continue;
            }
            if (ent->state.eventID = EntityEvent::Footstep) {
                continue;
            }
        }

        ent_visible = true;

        // ignore if not touching a PV leaf
        if (ent != clent) {
            // check area
			if (clientcluster >= 0 && !CM_AreasConnected(client->cm, clientarea, ent->areaNumber)) {
                // doors can legally straddle two areas, so
                // we may need to check another one
                if (!CM_AreasConnected(client->cm, clientarea, ent->areaNumber2)) {
                    ent_visible = false;        // Blocked by a door
                }
            }

            if (ent_visible)
            {
                // beams just check one point for PHS
                if (ent->state.renderEffects & RenderEffects::Beam) {
                    l = ent->clusterNumbers[0];
                    if (!Q_IsBitSet(clientphs, l))
                        ent_visible = false;
                }
                else {
                    if (cull_nonvisible_entities && !SV_EntityIsVisible(client->cm, ent, clientpvs)) {
                        ent_visible = false;
                    }

                    if (!ent->state.modelIndex) {
                        // don't send sounds if they will be attenuated away
                        vec3_t    delta;
                        float    len;

                        delta = org - ent->state.origin;
                        len = vec3_length(delta);
                        if (len > 400)
                            ent_visible = false;
                    }
                }
            }
        }

        if(!ent_visible && (!sv_novis->integer || !ent->state.modelIndex))
            continue;
        
		if (ent->state.number != e) {
			Com_WPrintf("%s: fixing ent->state.number: %d to %d\n",
				__func__, ent->state.number, e);
			ent->state.number = e;
		}

		memcpy(&es, &ent->state, sizeof(EntityState));

		if (!ent_visible) {
			// if the entity is invisible, kill its sound
			es.sound = 0;
		}

        // add it to the circular client_entities array
        state = &svs.entities[svs.next_entity % svs.num_entities];
        MSG_PackEntity(state, &es);

        if (ent->state.eventID = EntityEvent::Footstep) {
            ent->state.eventID = 0;
        }

        // hide POV entity from renderer, unless this is player's own entity
        if (e == frame->clientNumber + 1 && ent != clent) {
            state->modelIndex = 0;
        }

        if (ent->owner == clent) {
            //    // don't mark players missiles as solid
            state->solid = 0;
            //} else if (client->esFlags & MSG_ES_LONGSOLID) {
        } else {
            state->solid = sv.entities[e].solid32;
        }

        svs.next_entity++;

        if (++frame->num_entities == MAX_PACKET_ENTITIES) {
            break;
        }
    }
}

