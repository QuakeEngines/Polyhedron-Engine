#pragma once

class SynchedEntityBase;

//=============================================
// FuncAreaportal
// 
// This is a non-visible object that divides the world into
// areas that are seperated when this portal is not activated.
// Usually enclosed in the middle of a door.
//=============================================
class FuncAreaportal : public SynchedEntityBase {
public:
	FuncAreaportal( ServerEntity* entity );
	virtual ~FuncAreaportal() = default;

	DefineMapClass( "func_areaportal", FuncAreaportal, SynchedEntityBase);

	void Spawn() override;
	void SpawnKey( const std::string& key, const std::string& value ) override;

	// For triggering by mappers
	void PortalUse( SynchedEntityBase * other, SynchedEntityBase * activator );
	// For doors and other autonomous entities
	void ActivatePortal( bool open );

protected:
	bool turnedOn{ false };
};
