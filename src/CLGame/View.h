/*
// LICENSE HERE.

//
// clgame/clg_view.h
//
*/

#ifndef __CLGAME_VIEW_H__
#define __CLGAME_VIEW_H__

void V_Init(void);
void V_Shutdown(void);

void V_AddEntity(r_entity_t* ent);
void V_AddLight(const vec3_t& org, float intensity, float r, float g, float b);
void V_AddLightEx(const vec3_t& org, float intensity, float r, float g, float b, float radius);
void V_AddLightStyle(int style, const vec4_t& value);
void V_AddParticle(rparticle_t* p);

// Externs. Debugging reasons.
extern int         gun_frame;
extern qhandle_t   gun_model;

#endif // __CLGAME_VIEW_H__

