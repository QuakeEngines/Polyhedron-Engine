
#pragma once

class TriggerRelay : public BaseTrigger {
public:
	TriggerRelay( ServerEntity* entity );
	virtual ~TriggerRelay() = default;

	DefineMapClass( "trigger_relay", TriggerRelay, BaseTrigger );

	void Spawn() override;
	void RelayUse( SynchedEntityBase * other, SynchedEntityBase * activator );
};
