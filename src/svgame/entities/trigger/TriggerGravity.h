
#pragma once

class TriggerGravity : public BaseTrigger {
public:
	TriggerGravity( ServerEntity* entity );
	virtual ~TriggerGravity() = default;

	DefineMapClass( "trigger_gravity", TriggerGravity, BaseTrigger );

	void Spawn() override;

	void SpawnKey( const std::string& key, const std::string& value ) override;

	void GravityTouch( SynchedEntityBase * self, SynchedEntityBase * other, cplane_t* plane, csurface_t* surf );
};
