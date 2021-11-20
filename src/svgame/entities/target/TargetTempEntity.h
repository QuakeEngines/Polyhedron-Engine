
#pragma once

class TargetTempServerEntity : public ServerGameEntity {
public:
	TargetTempServerEntity( ServerEntity* ServerEntity );
	virtual ~TargetTempServerEntity() = default;

	DefineMapClass( "target_temp_ServerEntity", TargetTempServerEntity, ServerGameEntity );

	void Spawn() override;

	void TempServerEntityUse( ServerGameEntity* other, ServerGameEntity* activator );
};
