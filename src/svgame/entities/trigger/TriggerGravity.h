
#pragma once

class TriggerGravity : public SVGBaseTrigger {
public:
	TriggerGravity( ServerEntity* ServerEntity );
	virtual ~TriggerGravity() = default;

	DefineMapClass( "trigger_gravity", TriggerGravity, SVGBaseTrigger );

	void Spawn() override;

	void SpawnKey( const std::string& key, const std::string& value ) override;

	void GravityTouch( SVGBaseEntity* self, SVGBaseEntity* other, cplane_t* plane, csurface_t* surf );
};
