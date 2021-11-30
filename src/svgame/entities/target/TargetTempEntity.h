
#pragma once

class TargetTempEntity : public SynchedEntityBase{
public:
	TargetTempEntity( ServerEntity* entity );
	virtual ~TargetTempEntity() = default;

	DefineMapClass( "target_temp_entity", TargetTempEntity, SynchedEntityBase);

	void Spawn() override;

	void TempEntityUse( SynchedEntityBase * other, SynchedEntityBase * activator );
};
