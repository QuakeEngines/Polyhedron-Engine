#pragma once

class BaseTrigger;

//===============
// Automatic trigger for func_door
//===============
class TriggerAutoDoor : public BaseTrigger {
public:
	TriggerAutoDoor( ServerEntity* entity );
	virtual ~TriggerAutoDoor() = default;

	DefineClass( TriggerAutoDoor, BaseTrigger );

	void					Spawn() override;
	// Responds to players touching this trigger
	void					AutoDoorTouch( SynchedEntityBase * self, SynchedEntityBase * other, cplane_t* plane, csurface_t* surf );
	// Creates an automatic door trigger and sets everything up for it
	static TriggerAutoDoor* Create( SynchedEntityBase * ownerEntity, vec3_t ownerMaxs, vec3_t ownerMins );

protected:
	float					debounceTouchTime;
};
