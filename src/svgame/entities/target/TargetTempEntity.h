
#pragma once

class TargetTempEntity : public ServerGameEntity {
public:
	TargetTempEntity( ServerEntity* entity );
	virtual ~TargetTempEntity() = default;

	DefineMapClass( "target_temp_entity", TargetTempEntity, ServerGameEntity );

	void Spawn() override;

	void TempEntityUse( ServerGameEntity* other, ServerGameEntity* activator );
};
