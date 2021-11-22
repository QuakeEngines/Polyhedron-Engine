#pragma once

class SVGBaseTrigger;

//===============
// Automatic trigger for func_door
//===============
class TriggerAutoDoor : public SVGBaseTrigger {
public:
	TriggerAutoDoor( ServerEntity* entity );
	virtual ~TriggerAutoDoor() = default;

	DefineClass( TriggerAutoDoor, SVGBaseTrigger );

	void					Spawn() override;
	// Responds to players touching this trigger
	void					AutoDoorTouch( ServerGameEntity* self, ServerGameEntity* other, cplane_t* plane, csurface_t* surf );
	// Creates an automatic door trigger and sets everything up for it
	static TriggerAutoDoor* Create( ServerGameEntity* ownerEntity, vec3_t ownerMaxs, vec3_t ownerMins );

protected:
	float					debounceTouchTime;
};
