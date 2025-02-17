/*
// LICENSE HERE.

//
// clg_types.h
//
// Contains shared structures between the client and the game module.
//
*/
#ifndef __INC_SHARED_CLTYPES_H__
#define __INC_SHARED_CLTYPES_H__

//
//=============================================================================
//
// SHARED ENGINE/CLIENT DEFINITIONS.
//
// These should never be tampered with, unless you intend to recompile the
// whole engine afterwards, with the risk of possibly breaking any 
// compatibility with current mods.
//=============================================================================
//
//
// CLIENT STRUCTURES - GAME MODULE NEEDS TO KNOW ABOUT.
//
constexpr uint32_t BUTTON_STATE_HELD = (1 << 0);
constexpr uint32_t BUTTON_STATE_DOWN = (1 << 1);
constexpr uint32_t BUTTON_STATE_UP   = (1 << 2);

//
// Keybinding  management.
//
typedef struct {
    uint32_t keys[2]; // keys holding it down
    uint32_t downtime; // msec timeStamp
    uint32_t msec; // msec down this frame
    uint8_t state; // button state.
} KeyBinding;

//
// Explosion particle entity effect structure.
//
typedef struct {
	enum {
		ex_free,
		ex_explosion,
		ex_misc,
		ex_flash,
		ex_mflash,
		ex_poly,
		ex_poly2,
		ex_light,
		ex_blaster,
		ex_flare
	} type;

	r_entity_t  ent;
	int32_t     frames;
	float       light;
	vec3_t      lightcolor;
	float       start;
	int32_t     baseFrame;
	int32_t     frameTime; /* in milliseconds */
} explosion_t;

// Maximum amount of explosions.
constexpr uint32_t MAX_EXPLOSIONS = 32;

// No Particle Settings.
constexpr uint32_t NOPART_GRENADE_EXPLOSION = 1;
constexpr uint32_t NOPART_GRENADE_TRAIL = 2;
constexpr uint32_t NOPART_ROCKET_EXPLOSION = 4;
constexpr uint32_t NOPART_ROCKET_TRAIL = 8;
constexpr uint32_t NOPART_BLOOD = 16;

// No Explosion settings.
constexpr uint32_t NOEXP_GRENADE = 1;
constexpr uint32_t NOEXP_ROCKET = 2;

//
// Local client entity structure, temporary entities.
//
struct ClientEntity {
    EntityState    current;
    EntityState    prev;        // will always be valid, but might just be a copy of current

    vec3_t          mins, maxs;

    int32_t         serverFrame;// if not current, this ent isn't in the frame

    int32_t         trailcount; // for diminishing grenade trails
    vec3_t          lerpOrigin; // for trails (variable hz)

    int32_t         id;
};

//
// Temporarl Entity parameters.
// Used for parsing EFFECTS in the client.
//
struct tent_params_t {
    int32_t type;
    vec3_t position1;
    vec3_t position2;
    vec3_t offset;
    vec3_t dir;
    int32_t count;
    int32_t color;
    int32_t entity1;
    int32_t entity2;
    int32_t time;
};

//
// MuzzleFlash parameters.
// Used for parsing MUZZLEFLASHE messages in the client.
//
struct mz_params_t {
    int32_t entity;
    int32_t weapon;
    int32_t silenced;
};

//
// Sound parameters.
// Used for parsing SOUND messages in the client.
//
struct snd_params_t {
    int32_t flags;
    int32_t index;
    int32_t entity;
    int32_t channel;
    vec3_t  pos;
    float   volume;
    float   attenuation;
    float   timeofs;
};

//
// Client Sustain structure.
//
struct cl_sustain_t {
    int32_t id;
    int32_t type;
    int32_t endTime;
    int32_t nextThinkTime;
    int32_t thinkinterval;
    vec3_t  org;
    vec3_t  dir;
    int32_t color;
    int32_t count;
    int32_t magnitude;
    void    (*Think)(cl_sustain_t *self);
};

//
// Client Particle Structure.
//
struct cparticle_t {
    cparticle_t    *next;

    float   time;

    vec3_t  org;
    vec3_t  vel;
    vec3_t  acceleration;
    int32_t color;      // -1 => use rgba
    float   alpha;
    float   alphavel;
    color_t rgba;
	float   brightness;
};

//
// Client DLight structure.
//
struct cdlight_t {
    int32_t     key;        // so entities can reuse same entry
    vec3_t  color;
    vec3_t  origin;
    float   radius;
    float   die;        // stop lighting after this time
    float   decay;      // drop this each second
	vec3_t  velocity;     // move this far each second
    //float   minlight;   // don't add when contributing less
};

//
// Maximum amount of weapon models allowed.
//
static constexpr int32_t MAX_CLIENTWEAPONMODELS = 20;        // PGM -- upped from 16 to fit the chainfist vwep

//
// Contains all the info about a client we need to know.
//
struct ClientInfo {
    char name[MAX_QPATH];           // The client name.
    char model_name[MAX_QPATH];     // The model name.
    char skin_name[MAX_QPATH];      // The skin name.

    qhandle_t skin;                 // The skin handle.
    qhandle_t icon;                 // The icon handle. 
    qhandle_t model;                // Model handle.

    qhandle_t weaponmodel[MAX_CLIENTWEAPONMODELS];  // The weapon model handles.
};

//
// Used for storing client input commands.
//
struct ClientUserCommandHistory {
    uint32_t timeSent;      // Time sent, for calculating pings.
    uint32_t timeReceived;  // Time received, for calculating pings.
    uint32_t commandNumber; // Current commandNumber for this frame,
};

//
// The server frame structure contains information about the frame
// being sent from the server.
//
struct ServerFrame {
    qboolean valid; // False if delta parsing failed.

    int32_t number; // Sequential identifier, used for delta.
    int32_t delta;  // Delta between frames.

    byte    areaBits[MAX_MAP_AREA_BYTES];   // Area bits of this frame.
    int32_t areaBytes;                      // Area bytes.

    PlayerState playerState;    // The player state.
    int32_t     clientNumber;   // The client number.

    int32_t numEntities;    // The number of entities in the frame.
    int32_t firstEntity;    // The first entity in the frame.
};

//
// This structure contains all (persistent)shared data with the client.
//
struct ClientShared {
    // Stores the entities.
    ClientEntity entities[MAX_ENTITIES];
    int num_entities;
};

//
// Contains the predicted state (view origin, offset, angles, etc) of the client.
//
struct ClientPredictedState {
    // These are the actual predicted results that should align with the server's.
    vec3_t viewOrigin;  // Predicted view origin.
    vec3_t viewOffset;  // Predicted view offset.
    vec3_t viewAngles;  // Predicted view angles.
    float stepOffset;   // Predicted stepping offset. (Up or down)

    // Predicted velocity.
    vec3_t velocity;

    // Ground entity pointer of the predicted frame.
    struct entity_s* groundEntityPtr;

    // Prediction error that is interpolated over the server frame.
    vec3_t error;
};

//
// The client structure is cleared at each level load, and is exposed to
// * the client game module to provide access to media and other client state.
//
struct ClientState {
    ClientState() {
        bsp = nullptr;
    }
    //
    // Client User Command Related.
    // 
    int32_t         timeoutCount;

    // The time we last transmitted a user command.
    uint32_t    lastTransmitTime;
    // The last transmitted command number. This may differ from the one below.
    uint32_t    lastTransmitCmdNumber;
    // The ACTUAL last transmitted number which wasn't stalled by not being ready to send yet.
    uint32_t    lastTransmitCmdNumberReal;
    // Determines whether to send the user command packet asap, and preferably, NOW.
    qboolean    sendPacketNow;

    // Actual current client user command.
    ClientMoveCommand    moveCommand;
    // Actual current client user command list.
    ClientMoveCommand    clientUserCommands[CMD_BACKUP];    // each mesage will send several old clientUserCommands
    // Current command number.
    uint32_t     currentClientCommandNumber;
    // History book of time sent, received, and command number.
    ClientUserCommandHistory clientCommandHistory[CMD_BACKUP];

    // Initial outgoing sequence number.
    int32_t initialSequence;

    // Predicted Client State. (Used for movement.)
    ClientPredictedState predictedState;

    //
    // Entity States.
    // 
    // Solid Entities, these are REBUILT during EACH FRAME.
    ClientEntity *solidEntities[MAX_PACKET_ENTITIES];
    int32_t numSolidEntities;

    // Entity Baseline States. These are where to start working from.
    EntityState entityBaselines[MAX_EDICTS];

    // The actual current Entity States.
    EntityState entityStates[MAX_PARSE_ENTITIES];
    int32_t numEntityStates;

    // The current client entity state messaging flags.
    EntityStateMessageFlags    esFlags;

    //
    // Server Frames.
    // 
    // A list of server frames received.
    ServerFrame  frames[UPDATE_BACKUP];
    uint32_t     frameFlags;

    // The actual current server frame.
    ServerFrame frame; // The current(last received frame from the server)
    ServerFrame oldframe; // The previous frame received, right before the current frame.
    int32_t serverTime;
    int32_t serverDelta;

    byte            dcs[CS_BITMAP_BYTES];

    // the client maintains its own idea of view angles, which are
    // sent to the server each frame.  It is cleared to 0 upon entering each level.
    // the server sends a delta each frame which is added to the locally
    // tracked view angles to account for standing on rotating objects,
    // and teleport direction changes
    vec3_t      viewAngles;

    // interpolated movement vector used for local prediction,
    // never sent to server, rebuilt each client frame
    vec3_t      localMove;

    // accumulated mouse forward/side movement, added to both
    // localMove and pending cmd, cleared each time cmd is finalized
    vec2_t      mouseMove;

    int32_t         time;           // this is the time value that the client
                                // is rendering at.  always <= cl.serverTime
    float       lerpFraction;       // between oldframe and frame

    //
    // Client Sound Variables.
    //
    // Used for storing the listener origin of the client.
    vec3_t      listener_origin;

    // Special Effect: UNDERWATER
    qboolean    snd_is_underwater;
    qboolean    snd_is_underwater_enabled;

    //
    // Client Input Variables.
    //
    float       autosens_x;
    float       autosens_y;

    //
    // Client Rendering Variables.
    //
    refdef_t refdef;
    float fov_x;      // Interpolated
    float fov_y;      // Derived from fov_x assuming 4/3 aspect ratio
    int32_t lightLevel;

    // Updated in ClientGameExports::ClientUpdateOrigin.
    vec3_t v_forward, v_right, v_up;    

    qboolean thirdPersonView;

    // Predicted values, used for smooth player entity movement in thirdperson view
    vec3_t playerEntityOrigin;
    vec3_t playerEntityAngles;
    
    //
    // transient data from server
    //
    char    layout[MAX_NET_STRING];     // general 2D overlay
    int32_t inventory[MAX_ITEMS];

    //
    // server state information
    //
    int32_t serverState;    // ss_* constants
    int32_t serverCount;    // server identification for prespawns
    
    int32_t clientNumber;   // never changed during gameplay, set by serverdata packet
    int32_t maximumClients;

    char gamedir[MAX_QPATH];
    char mapName[MAX_QPATH]; // short format - q2dm1, etc

    char baseConfigStrings[ConfigStrings::MaxConfigStrings][MAX_QPATH];
    char configstrings[ConfigStrings::MaxConfigStrings][MAX_QPATH];


#if USE_AUTOREPLY
    uint32_t replyTime;
    uint32_t replyDelta;
#endif
    vec3_t deltaAngles;
    //
    // locally derived information from server state
    //
    bsp_t        *bsp;                  // Pointer to the actual BSP.

    qhandle_t drawModels[MAX_MODELS];   // Handles for loaded draw models (MD2, MD3, ...).
    mmodel_t *clipModels[MAX_MODELS];   // mmodel_t ptr handles for loaded clip models (Brush models).

    struct {
        qhandle_t sounds[MAX_SOUNDS];   // Handles to the loaded sounds.
        qhandle_t images[MAX_IMAGES];   // Handles to the loaded images.
    } precaches;
    ClientInfo    clientInfo[MAX_CLIENTS];    // Client info for all clients.
    ClientInfo    baseClientInfo;             // Local, Player, Client Info.

    char    weaponModels[MAX_CLIENTWEAPONMODELS][MAX_QPATH]; // Weapon Models string paths.
    int32_t numWeaponModels;    // Number of weapon models.
};

#endif // __SHARED_CL_TYPES_H__