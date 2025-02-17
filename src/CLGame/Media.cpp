// LICENSE HERE.

//
// clg_media.c
//
//
// Media load handling, usually happens when the renderer initializes, or
// restarts (Think about changing screen mode, or other settings).
//
#include "ClientGameLocal.h"

#include "Effects.h"
#include "Media.h"
#include "Main.h"
#include "Screen.h"
#include "TemporaryEntities.h"
#include "View.h"

//
//===============
// CLG_RegisterVWepModels
// 
// Register view weapon models, coming from server.
//===============
//
void CLG_RegisterVWepModels()
{
    int         i;
    char        *name;

    cl->numWeaponModels = 1;
    strcpy(cl->weaponModels[0], "weapon.md2");

    // only default model when vwep is off
     if (!cl_vwep->integer) {
         return;
     }
    
    for (i = 2; i < MAX_MODELS; i++) {
        name = cl->configstrings[ConfigStrings::Models+ i];
        if (!name[0]) {
            break;
        }
        if (name[0] != '#') {
            continue;
        }

        // special player weapon model
        strcpy(cl->weaponModels[cl->numWeaponModels++], name + 1);

        if (cl->numWeaponModels == MAX_CLIENTWEAPONMODELS) {
            break;
        }
    }
}

//
//===============
// CLG_LoadClientInfo
// 
// Breaks up playerskin into name (optional), model and skin components.
// If model or skin are found to be invalid, replaces them with sane defaults.
//===============
//
static void CLG_ParsePlayerSkin(char* name, char* model, char* skin, const char* s)
{
    size_t len;
    char* t;

    // configstring parsing guarantees that playerskins can never
    // overflow, but still check the length to be entirely fool-proof
    len = strlen(s);
    if (len >= MAX_QPATH) {
        Com_Error(ERR_DROP, "%s: oversize playerskin", __func__);
    }

    // isolate the player's name
    t = (char*)strchr(s, '\\'); // CPP: Cast
    if (t) {
        len = t - s;
        strcpy(model, t + 1);
    }
    else {
        len = 0;
        strcpy(model, s);
    }

    // copy the player's name
    if (name) {
        memcpy(name, s, len);
        name[len] = 0;
    }

    // isolate the model name
    t = strchr(model, '/');
    if (!t)
        t = strchr(model, '\\');
    if (!t)
        goto default_model;
    *t = 0;

    // isolate the skin name
    strcpy(skin, t + 1);

    // fix empty model to male
    if (t == model)
        strcpy(model, "male");

    // apply restrictions on skins
    if (cl_noskins->integer == 2 || !COM_IsPath(skin))
        goto default_skin;

    if (cl_noskins->integer || !COM_IsPath(model))
        goto default_model;

    return;

default_skin:
    if (!Q_stricmp(model, "female")) {
        strcpy(model, "female");
        strcpy(skin, "athena");
    }
    else {
    default_model:
        strcpy(model, "male");
        strcpy(skin, "grunt");
    }
}


//
//===============
// CLG_LoadClientInfo
// 
// Loads up the data for the given client. Here you can set the default
// models that it'll load, or totally disable clients from doing their
// own.
//
// Think about a mod where you have a class system, you can load the info
// here.
//===============
//
void CLG_LoadClientInfo(ClientInfo* ci, const char* str)
{
    int         i;
    char        model_name[MAX_QPATH];
    char        skin_name[MAX_QPATH];
    char        model_filename[MAX_QPATH];
    char        skin_filename[MAX_QPATH];
    char        weapon_filename[MAX_QPATH];
    char        icon_filename[MAX_QPATH];

    CLG_ParsePlayerSkin(ci->name, model_name, skin_name, str);

    // model file
    Q_concat(model_filename, sizeof(model_filename),
        "players/", model_name, "/tris.md2", NULL);
    ci->model = clgi.R_RegisterModel(model_filename);
    if (!ci->model && Q_stricmp(model_name, "male")) {
        strcpy(model_name, "male");
        strcpy(model_filename, "players/male/tris.md2");
        ci->model = clgi.R_RegisterModel(model_filename);
    }

    // skin file
    Q_concat(skin_filename, sizeof(skin_filename),
        "players/", model_name, "/", skin_name, ".pcx", NULL);
    ci->skin = clgi.R_RegisterSkin(skin_filename);

    // if we don't have the skin and the model was female,
    // see if athena skin exists
    if (!ci->skin && !Q_stricmp(model_name, "female")) {
        strcpy(skin_name, "athena");
        strcpy(skin_filename, "players/female/athena.pcx");
        ci->skin = clgi.R_RegisterSkin(skin_filename);
    }

    // if we don't have the skin and the model wasn't male,
    // see if the male has it (this is for CTF's skins)
    if (!ci->skin && Q_stricmp(model_name, "male")) {
        // change model to male
        strcpy(model_name, "male");
        strcpy(model_filename, "players/male/tris.md2");
        ci->model = clgi.R_RegisterModel(model_filename);

        // see if the skin exists for the male model
        Q_concat(skin_filename, sizeof(skin_filename),
            "players/male/", skin_name, ".pcx", NULL);
        ci->skin = clgi.R_RegisterSkin(skin_filename);
    }

    // if we still don't have a skin, it means that the male model
    // didn't have it, so default to grunt
    if (!ci->skin) {
        // see if the skin exists for the male model
        strcpy(skin_name, "grunt");
        strcpy(skin_filename, "players/male/grunt.pcx");
        ci->skin = clgi.R_RegisterSkin(skin_filename);
    }

    // weapon file
    for (i = 0; i < cl->numWeaponModels; i++) {
        Q_concat(weapon_filename, sizeof(weapon_filename),
            "players/", model_name, "/", cl->weaponModels[i], NULL);
        ci->weaponmodel[i] = clgi.R_RegisterModel(weapon_filename);
        if (!ci->weaponmodel[i] && !Q_stricmp(model_name, "cyborg")) {
            // try male
            Q_concat(weapon_filename, sizeof(weapon_filename),
                "players/male/", cl->weaponModels[i], NULL);
            ci->weaponmodel[i] = clgi.R_RegisterModel(weapon_filename);
        }
    }

    // icon file
    Q_concat(icon_filename, sizeof(icon_filename),
        "/players/", model_name, "/", skin_name, "_i.pcx", NULL);
    ci->icon = clgi.R_RegisterPic2(icon_filename);

    strcpy(ci->model_name, model_name);
    strcpy(ci->skin_name, skin_name);

    // base info should be at least partially valid
    if (ci == &cl->baseClientInfo)
        return;

    // must have loaded all data types to be valid
    if (!ci->skin || !ci->icon || !ci->model || !ci->weaponmodel[0]) {
        ci->skin = 0;
        ci->icon = 0;
        ci->model = 0;
        ci->weaponmodel[0] = 0;
        ci->model_name[0] = 0;
        ci->skin_name[0] = 0;
    }
}

//
//===============
// CLG_SetSky
// 
// Sets the sky based on the configstring.
//===============
//
void CLG_SetSky(void)
{
    float       rotate;
    vec3_t      axis;

    rotate = atof(cl->configstrings[ConfigStrings::SkyRotate]);
    if (sscanf(cl->configstrings[ConfigStrings::SkyAxis], "%f %f %f",
        &axis[0], &axis[1], &axis[2]) != 3) {
        Com_DPrint("Couldn't parse ConfigStrings::SkyAxis\n");
        VectorClear(axis);
    }

    clgi.R_SetSky(cl->configstrings[ConfigStrings::Sky], rotate, axis);
}

//
//=============================================================================
//
// CLIENT MODULE MEDIA ENTRY FUNCTIONS.
//
//=============================================================================
//
