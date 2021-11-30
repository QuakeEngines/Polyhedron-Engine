
#pragma once

class TriggerCounter : public BaseTrigger {
public:
	TriggerCounter( ServerEntity* entity );
	virtual ~TriggerCounter() = default;

	DefineMapClass( "trigger_counter", TriggerCounter, BaseTrigger );

	constexpr static int32_t SF_NoMessage = 1 << 0;

	void Spawn() override;
	void SpawnKey( const std::string& key, const std::string& value );

	void CounterUse( SynchedEntityBase * other, SynchedEntityBase * activator );

private:
	uint32_t count{ 2U };
};
