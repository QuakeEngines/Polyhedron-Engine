
#pragma once

class TargetTempServerEntity : public SVGBaseEntity {
public:
	TargetTempServerEntity( ServerEntity* ServerEntity );
	virtual ~TargetTempServerEntity() = default;

	DefineMapClass( "target_temp_ServerEntity", TargetTempServerEntity, SVGBaseEntity );

	void Spawn() override;

	void TempServerEntityUse( SVGBaseEntity* other, SVGBaseEntity* activator );
};
