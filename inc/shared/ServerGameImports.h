// License here.
#pragma once

class ServerEntity;
struct trace_t;

//
// functions provided by the main engine
//
struct ServerGameImports {
    //---------------------------------------------------------------------
    // API Version.
    // 
    // The version numbers will always be equal to those that were set in 
    // CMake at the time of building the engine/game(dll/so) binaries.
    // 
    // In an ideal world, we comply to proper version releasing rules.
    // For Polyhedron FPS, the general following rules apply:
    // --------------------------------------------------------------------
    // MAJOR: Ground breaking new features, you can expect anything to be 
    // incompatible at that.
    // 
    // MINOR : Everytime we have added a new feature, or if the API between
    // the Client / Server and belonging game counter-parts has actually 
    // changed.
    // 
    // POINT : Whenever changes have been made, and the above condition 
    // is not met.
    //---------------------------------------------------------------------
    struct {
        int32_t major;
        int32_t minor;
        int32_t point;
    } apiversion;

    // special messages
    void (* q_printf(2, 3) BPrintf)(int printlevel, const char *fmt, ...);
    void (* q_printf(1, 2) DPrintf)(const char *fmt, ...);
    void (* q_printf(3, 4) CPrintf)(ServerEntity *svEnt, int printlevel, const char *fmt, ...);
    void (* q_printf(2, 3) CenterPrintf)(ServerEntity *svEnt, const char *fmt, ...);
    void (*Sound)(ServerEntity *svEnt, int channel, int soundindex, float volume, float attenuation, float timeofs);
    void (*PositionedSound)(vec3_t origin, ServerEntity *svEnt, int channel, int soundinedex, float volume, float attenuation, float timeofs);

    // config strings hold all the index strings, the lightstyles,
    // and misc data like the sky definition and cdtrack.
    // All of the current configstrings are sent to clients when
    // they connect, and changes are sent to all connected clients.
    void (*configstring)(int num, const char *string);

    void (* q_noreturn q_printf(1, 2) Error)(const char *fmt, ...);

    // the *index functions create configstrings and some internal server state
    int (*ModelIndex)(const char *name);
    int (*SoundIndex)(const char *name);
    int (*ImageIndex)(const char *name);

    void (*SetModel)(ServerEntity *svEnt, const char *name);

    // collision detection
    trace_t (* q_gameabi Trace)(const vec3_t &start, const vec3_t &mins, const vec3_t &maxs, const vec3_t &end, ServerEntity *svPassent, int contentmask);
    int (*PointContents)(const vec3_t &point);
    qboolean (*InPVS)(const vec3_t &p1, const vec3_t &p2);
    qboolean (*InPHS)(const vec3_t &p1, const vec3_t &p2);
    void (*SetAreaPortalState)(int portalnum, qboolean open);
    qboolean (*AreasConnected)(int area1, int area2);

    // an ServerEntity will never be sent to a client or used for collision
    // if it is not passed to LinkServerEntity.  If the size, position, or
    // solidity changes, it must be relinked.
    void (*LinkServerEntity)(ServerEntity *svEnt);
    void (*UnlinkServerEntity)(ServerEntity *svEnt);     // call before removing an interactive edict
    int (*BoxEntities)(const vec3_t &mins, const vec3_t &maxs, ServerEntity **list, int maxcount, int areatype);

    // network messaging
    void (*Multicast)(const vec3_t &origin, int32_t to);
    void (*Unicast)(ServerEntity *svEnt, qboolean reliable);
    void (*WriteChar)(int c);
    void (*WriteByte)(int c);
    void (*WriteShort)(int c);
    void (*WriteLong)(int c);
    void (*WriteFloat)(float f);
    void (*WriteString)(const char *s);
    void (*WriteVector3)(const vec3_t &pos);

    // managed memory allocation
    void *(*TagMalloc)(size_t size, unsigned tag);
    void (*TagFree)(void *block);
    void (*FreeTags)(unsigned tag);

    // console variable interaction
    cvar_t *(*cvar)(const char *var_name, const char *value, int flags);
    cvar_t *(*cvar_set)(const char *var_name, const char *value);
    cvar_t *(*cvar_forceset)(const char *var_name, const char *value);

    // ClientCommand and SVG_ServerCommand parameter access
    int (*argc)(void);
    const char *(*argv)(int n);     // C++20: char*
    const char *(*args)(void);      // concatenation of all argv >= 1 // C++20: char*

                                    // N&C: Stuff Cmd.
    void (*StuffCmd) (ServerEntity* svPlayerEnt, const char* pszCommand); // C++20: STRING: Added const to char*

                                                                          // add commands to the server console as if they were typed in
                                                                          // for map changing, etc
    void (*AddCommandString)(const char *text);

    void (*DebugGraph)(float value, int color);
};

extern ServerGameImports gi;