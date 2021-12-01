#pragma once

class SynchedEntityBase.h;

//=============================================
// FuncTimer
// 
// A utility entity for mappers, that triggers its targets
// every "wait" seconds + "random" if specified.
// 
// NOTE: pausetime is currently always 0
//=============================================
class FuncTimer : public SynchedEntityBase{
public:
	FuncTimer( ServerEntity* entity );
	virtual ~FuncTimer() = default;

	DefineMapClass( "func_timer", FuncTimer, SynchedEntityBase);

	// Spawn flags
	static constexpr int32_t SF_StartOn = 1 << 0;

	void Spawn() override;
	void SpawnKey( const std::string& key, const std::string& value ) override;

	void TimerThink();
	void TimerUse( SynchedEntityBase * other, SynchedEntityBase * activator );

protected:
	float randomTime{ 0.0f };
};
