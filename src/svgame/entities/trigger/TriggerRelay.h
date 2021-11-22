
#pragma once

class TriggerRelay : public SVGBaseTrigger {
public:
	TriggerRelay( ServerEntity* entity );
	virtual ~TriggerRelay() = default;

	DefineMapClass( "trigger_relay", TriggerRelay, SVGBaseTrigger );

	void Spawn() override;
	void RelayUse( ServerGameEntity* other, ServerGameEntity* activator );
};
