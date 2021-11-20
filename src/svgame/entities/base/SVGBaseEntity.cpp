/*
// LICENSE HERE.

//
// SVGBaseEntity.cpp
//
//
*/
#include "../../g_local.h"		// SVGame.
#include "../../effects.h"		// Effects.
#include "../../entities.h"		// Entities.
#include "../../utils.h"		// Util funcs.
#include "SVGBaseEntity.h"

#include "SVGBaseTrigger.h"
#include "../trigger/TriggerDelayedUse.h"

// Constructor/Deconstructor.
SVGBaseEntity::SVGBaseEntity(ServerEntity* svServerEntity) : serverEntity(svServerEntity) {
	//
	// All callback functions best be nullptr.
	//
	thinkFunction = nullptr;
	useFunction = nullptr;
	touchFunction = nullptr;
	blockedFunction = nullptr;
	takeDamageFunction = nullptr;
	dieFunction = nullptr;

	//
	// Set all ServerEntity pointer references to nullptr.
	//
	enemyServerEntity = nullptr;
	groundServerEntity = nullptr;
	oldEnemyServerEntity = nullptr;
	teamChainServerEntity = nullptr;
	teamMasterServerEntity = nullptr;

	//
	// Default values for members.
	//
	moveType = MoveType::None;

	// Velocity.
	delayTime = 0;
	waitTime = 0;

	flags = 0;
	spawnFlags = 0;
	velocity = vec3_zero();
	angularVelocity = vec3_zero();
	mass = 0;
	gravity = 1.f;
	yawSpeed = 0.f;
	idealYawAngle = 0.f;
	groundServerEntityLinkCount = 0;
	health = 0;
	maxHealth = 0;
	deadFlag = DEAD_NO;

	// Set the server entity to be in use.
	serverEntity = svServerEntity;
}
SVGBaseEntity::~SVGBaseEntity() {
	serverEntity->inUse = false;
}

// Interface functions. 
//
//===============
// SVGBaseEntity::Precache
//
// This function is used to load all ServerEntity data with.
//===============
//
void SVGBaseEntity::Precache() {
	//gi.DPrintf("SVGBaseEntity::Precache();");
}

//
//===============
// SVGBaseEntity::Spawn
//
// This function can be overrided, to allow for ServerEntity spawning.
// Setup the basic ServerEntity properties here.
//===============
//
void SVGBaseEntity::Spawn() {
	//gi.DPrintf("SVGBaseEntity::Spawn();");

	// Set default movetype to none.
	//SetMoveType(MoveType::None);
}

//
//===============
// SVGBaseEntity::Respawn
//
// This function can be overrided, to allow for ServerEntity respawning.
// Setup the basic ServerEntity properties here.
//===============
//
void SVGBaseEntity::Respawn() {
	//gi.DPrintf("SVGBaseEntity::Respawn();");
}

//
//===============
// SVGBaseEntity::PostSpawn
//
// This function can be overrided, to allow for ServerEntity post spawning.
// An example of that could be finding targetnames for certain target
// trigger settings, etc.
//===============
//
void SVGBaseEntity::PostSpawn() {
	//gi.DPrintf("SVGBaseEntity::PostSpawn();");
}

//
//===============
// SVGBaseEntity::Think
//
// This function can be overrided, to allow for custom ServerEntity thinking.
// By default it only executes the 'Think' callback in case we have any set.
//===============
//
void SVGBaseEntity::Think() {
	// Safety check.
	if (thinkFunction == nullptr)
		return;

	// Execute 'Think' callback function.
	(this->*thinkFunction)();
}

//
//===============
// SVGBaseEntity::ParseFloatKeyValue
//
// PROTECTED function to help parsing float key:value string pairs with.
//===============
//
qboolean SVGBaseEntity::ParseFloatKeyValue(const std::string& key, const std::string& value, float &floatNumber) {
	floatNumber = std::stof(value);

	return true;
}

//
//===============
// SVGBaseEntity::ParseIntegerKeyValue
//
// PROTECTED function to help parsing int32_t key:value string pairs with.
//===============
//
qboolean SVGBaseEntity::ParseIntegerKeyValue(const std::string& key, const std::string& value, int32_t &integerNumber) {
	integerNumber = std::stoi(value);

	return true;
}

//
//===============
// SVGBaseEntity::ParseUnsignedIntegerKeyValue
//
// PROTECTED function to help parsing uint32_t key:value string pairs with.
//===============
//
qboolean SVGBaseEntity::ParseUnsignedIntegerKeyValue(const std::string& key, const std::string& value, uint32_t& unsignedIntegerNumber) {
	unsignedIntegerNumber = std::stoul(value);

	return true;
}

//
//===============
// SVGBaseEntity::ParseStringKeyValue
//
// PROTECTED function to help parsing string key:value string pairs with.
//===============
//
qboolean SVGBaseEntity::ParseStringKeyValue(const std::string& key, const std::string& value, std::string& stringValue) {
	stringValue = value;

	return true;
}

//
//===============
// SVGBaseEntity::ParseVector3KeyValue
//
// PROTECTED function to help parsing vector key:value string pairs with.
//===============
//
qboolean SVGBaseEntity::ParseVector3KeyValue(const std::string& key, const std::string &value, vec3_t &vectorValue) {
	// Stores vector fields fetched from string. (Might be corrupted, so we're parsing this nicely.)
	std::vector<std::string> vectorFields;

	// We split it based on the space delimiter. Empties are okay, how can they be empty then? Good question...
	STR_Split(vectorFields, value, " ");

	// Zero out our vector.
	vectorValue = vec3_zero();
	int32_t i = 0;
	for (auto& str : vectorFields) {
		vectorValue[i] = std::stof(str);
		i++;

		if (i > 2)
			break;
	}

	return true;
}

//
//===============
// SVGBaseEntity::SpawnKey
//
// This function can be overrided, to allow for custom ServerEntity key:value parsing.
//===============
//
void SVGBaseEntity::SpawnKey(const std::string& key, const std::string& value) {
	//{"lip", STOFS(lip), F_INT},
	//{ "distance", STOFS(distance), F_INT },
	//{ "height", STOFS(height), F_INT },
	//{ "noise", STOFS(noise), F_LSTRING },
	//{ "pausetime", STOFS(pausetime), F_FLOAT },
	//{ "item", STOFS(item), F_LSTRING },

	//{ "gravity", STOFS(gravity), F_LSTRING },
	//{ "sky", STOFS(sky), F_LSTRING },
	//{ "skyrotate", STOFS(skyrotate), F_FLOAT },
	//{ "skyaxis", STOFS(skyaxis), F_VECTOR },
	//{ "minyaw", STOFS(minyaw), F_FLOAT },
	//{ "maxyaw", STOFS(maxyaw), F_FLOAT },
	//{ "minpitch", STOFS(minpitch), F_FLOAT },
	//{ "maxpitch", STOFS(maxpitch), F_FLOAT },
	//{ "nextmap", STOFS(nextMap), F_LSTRING },
	
	// STOOOOOOOP WITH THE GOD DAMN WARNINGS IN THE CONSOLE ABOUT CLASSNAME
	// RAAAAAAAAHHHHH
	if ( key == "classname" ) {
		SetClassName( value.c_str() );
	}
	// Angle.
	else if (key == "angle") {
		// Parse angle.
		vec3_t hackedAngles = vec3_zero();
		ParseFloatKeyValue(key, value, hackedAngles.y);

		// Set angle.
		SetAngles( hackedAngles );
	}
	// Angles.
	else if (key == "angles") {
		// Parse angles.
		vec3_t parsedAngles = vec3_zero();
		ParseVector3KeyValue(key, value, parsedAngles);

		// Set origin.
		SetAngles(parsedAngles);
	}
	// Damage(dmg)
	else if (key == "dmg") {
		// Parse damage.
		int32_t parsedDamage = 0;
		ParseIntegerKeyValue(key, value, parsedDamage);

		// Set Damage.
		SetDamage(parsedDamage);
	}
	// Delay.
	else if (key == "delay") {
		// Parsed float.
		float parsedFloat = 0.f;

		// Parse.
		ParseFloatKeyValue(key, value, parsedFloat);

		// Assign.
		SetDelayTime(parsedFloat);
	}
	// KillTarget.
	else if (key == "killtarget") {
		// Parsed string.
		std::string parsedString = "";

		// Parse.
		ParseStringKeyValue(key, value, parsedString);

		// Assign.
		SetKillTarget(parsedString);
	}
	// Message.
	else if (key == "message") {
		// Parsed string.
		std::string parsedString = "";

		// Parse.
		ParseStringKeyValue(key, value, parsedString);

		// Assign.
		SetMessage(parsedString);
	} 
	// Model.
	else if (key == "model") {
		// Parse model.
		std::string parsedModel = "";
		ParseStringKeyValue(key, value, parsedModel);

		// Set model.
		SetModel(parsedModel);
	}
	// Origin.
	else if (key == "origin") {
		// Parse origin.
		vec3_t parsedOrigin = vec3_zero();
		ParseVector3KeyValue(key, value, parsedOrigin);

		// Set origin.
		SetOrigin(parsedOrigin);
	// Target.
	} else if (key == "target") {
		// Parsed string.
		std::string parsedString = "";

		// Parse.
		ParseStringKeyValue(key, value, parsedString);

		// Assign.
		SetTarget(parsedString);
	// TargetName.
	} else 	if (key == "targetname") {
		// Parsed string.
		std::string parsedString = "";

		// Parse.
		ParseStringKeyValue(key, value, parsedString);

		// Assign.
		SetTargetName(parsedString);
	}
	// Spawnflags.
	else if (key == "spawnflags") {
		// Parse damage.
		int32_t parsedSpawnFlags = 0;
		ParseIntegerKeyValue(key, value, parsedSpawnFlags);

		// Set SpawnFlags.
		SetSpawnFlags(parsedSpawnFlags);
	} else {
		gi.DPrintf("ServerEntity ID: %i - classname: %s has unknown Key/Value['%s','%s']\n", GetServerServerEntity()->state.number, GetServerServerEntity()->className, key.c_str(), value.c_str());
	}
}

//
//===============
// SVGBaseEntity::Use
//
// Execute the 'Use' callback in case we ran into any.
//===============
//
void SVGBaseEntity::Use(SVGBaseEntity* other, SVGBaseEntity* activator) {
	// Safety check.
	if (useFunction == nullptr)
		return;

	// Execute 'Die' callback function.
	(this->*useFunction)(other, activator);
}

//
//===============
// SVGBaseEntity::Blocked
//
// Execute the 'Blocked' callback in case we ran into any.
//===============
//
void SVGBaseEntity::Blocked(SVGBaseEntity* other) {
	// Safety check.
	if (blockedFunction == nullptr)
		return;

	// Execute 'Die' callback function.
	(this->*blockedFunction)(other);
}

//
//===============
// SVGBaseEntity::TakeDamage
//
// Execute the 'TakeDamage' callback in case we ran into any.
//===============
//
void SVGBaseEntity::TakeDamage(SVGBaseEntity* other, float kick, int32_t damage) {
	// Safety check.
	if (takeDamageFunction == nullptr)
		return;

	// Execute 'Die' callback function.
	(this->*takeDamageFunction)(other, kick, damage);
}

//
//===============
// SVGBaseEntity::Die
//
// Execute the 'Die' callback in case we ran into any.
//===============
//
void SVGBaseEntity::Die(SVGBaseEntity* inflictor, SVGBaseEntity* attacker, int damage, const vec3_t& point) {
	// Safety check.
	if (dieFunction == nullptr)
		return;

	// Execute 'Die' callback function.
	(this->*dieFunction)(inflictor, attacker, damage, point);
}

//
//===============
// SVGBaseEntity::Touch
//
// Execute the 'Touch' callback in case we ran into any.
//===============
//
void SVGBaseEntity::Touch(SVGBaseEntity* self, SVGBaseEntity* other, cplane_t* plane, csurface_t* surf) {
	// Safety check.
	if (touchFunction == nullptr)
		return;

	// Execute 'Touch' callback function.
	(this->*touchFunction)(self, other, plane, surf);
}

//===============
// SVGBaseEntity::UseTargets
// 
// Calls Use on this ServerEntity's targets, as well as killtargets
//===============
void SVGBaseEntity::UseTargets( SVGBaseEntity* activatorOverride )
{
	if ( nullptr == activatorOverride )
	{
		activatorOverride = activator;
	}

	if ( nullptr == activator )
	{
		activatorOverride = this;
	}

	// Create a temporary DelayedUse ServerEntity in case this ServerEntity has a trigger delay
	if ( GetDelayTime() )
	{
		// This is all very lengthy. I'd rather have a static method in TriggerDelayedUse that
		// allocates one such ServerEntity and accepts activator, message, target etc. as parameters
		// Something like 'TriggerDelayedUse::Schedule( GetTarget(), GetKillTarget(), activatorOverride, GetMessage(), GetDelayTime() );'
		SVGBaseTrigger* triggerDelay = SVG_CreateClassServerEntity<TriggerDelayedUse>();
		triggerDelay->SetActivator( activatorOverride );
		triggerDelay->SetMessage( GetMessage() );
		triggerDelay->SetTarget( GetTarget() );
		triggerDelay->SetKillTarget( GetKillTarget() );
		triggerDelay->SetNextThinkTime( level.time + GetDelayTime() );
		triggerDelay->SetThinkCallback( &TriggerDelayedUse::TriggerDelayedUseThink );
		// No need to continue. The rest happens by delay.
		return;
	}

	// Print the "message"
	if ( GetMessage().length() && !(activator->GetServerFlags() & ServerEntityServerFlags::Monster) ) 
	{
		// Get the message sound
		int32_t messageSound = GetNoiseIndex();
		
		// Print the message.
		SVG_CenterPrint( activator, GetMessage() );

		// Play the message sound
		if ( messageSound ) 
		{
			SVG_Sound( activatorOverride, CHAN_AUTO, messageSound, 1, ATTN_NORM, 0 );
		}
		else 
		{
			SVG_Sound( activatorOverride, CHAN_AUTO, gi.SoundIndex( "misc/talk1.wav" ), 1, ATTN_NORM, 0 );
		}
	}

	// Remove all entities that qualify as our killtargets
	if ( GetKillTarget().length() )
	{
		SVGBaseEntity* victim = nullptr;
		while ( victim = SVG_FindServerEntityByKeyValue( "targetname", GetKillTarget(), victim ) )
		{	// It is going to die, free it.
			SVG_FreeServerEntity( victim->GetServerServerEntity() );
		}

		if ( !IsInUse() ) 
		{
			gi.DPrintf( "ServerEntity was removed while using killtargets\n" );
			return;
		}
	}

	// Actually fire the targets
	if ( GetTarget().length() ) 
	{
		SVGBaseEntity* targetServerEntity = nullptr;
		while ( (targetServerEntity = SVG_FindServerEntityByKeyValue( "targetname", GetTarget(), targetServerEntity )) )
		{
			// Doors fire area portals in a special way, so skip those
			if ( targetServerEntity->GetClassName() == "func_areaportal"
				 && (GetClassName() == "func_door" || GetClassName() == "func_door_rotating") ) 
			{
				continue;
			}

			if ( targetServerEntity == this ) 
			{
				gi.DPrintf( "WARNING: ServerEntity #%i used itself.\n", GetServerServerEntity()->state.number );
			}
			else 
			{
				targetServerEntity->Use( this, activatorOverride );
			}

			// Make sure it is in use
			if ( !targetServerEntity->IsInUse() ) 
			{
				gi.DPrintf( "WARNING: ServerEntity #%i was removed while using targets\n", GetServerServerEntity()->state.number );
				return;
			}
		}
	}
}

//
//===============
// SVGBaseEntity::LinkServerEntity
//
// Link ServerEntity to world for collision testing using gi.LinkServerEntity.
//===============
//
void SVGBaseEntity::LinkServerEntity() {
	gi.LinkServerEntity(serverEntity);
}

//===============
// SVGBaseEntity::UnlinkServerEntity
//
// 
//===============
void SVGBaseEntity::UnlinkServerEntity() {
	gi.UnlinkServerEntity(serverEntity);
}

//===============
// SVGBaseEntity::Remove
//===============
void SVGBaseEntity::Remove()
{
	serverEntity->serverFlags |= ServerEntityServerFlags::Remove;
}

//===============
// SVGBaseEntity::SVGBaseServerEntityThinkRemove
// 
// Can be utilized to have it be removed at the next moment of thinking.
//===============
void SVGBaseEntity::SVGBaseServerEntityThinkRemove(void) {
	Remove();
}