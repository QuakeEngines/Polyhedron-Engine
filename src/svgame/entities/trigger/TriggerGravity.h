
#pragma once

class TriggerGravity : public SVGBaseTrigger {
public:
	TriggerGravity( ServerEntity* entity );
	virtual ~TriggerGravity() = default;

	DefineMapClass( "trigger_gravity", TriggerGravity, SVGBaseTrigger );

	void Spawn() override;

	void SpawnKey( const std::string& key, const std::string& value ) override;

	void GravityTouch( ServerGameEntity* self, ServerGameEntity* other, cplane_t* plane, csurface_t* surf );
};
