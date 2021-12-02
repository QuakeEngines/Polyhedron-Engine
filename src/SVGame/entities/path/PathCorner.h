#pragma once

class SynchedEntityBase;

class PathCorner : public SynchedEntityBase{
public:
	PathCorner( ServerEntity* entity );
	virtual ~PathCorner() = default;

	DefineMapClass( "path_corner", PathCorner, SynchedEntityBase);

	const vec3_t	BboxSize = vec3_t( 8.0f, 8.0f, 8.0f );

	// Spawnflags
	static constexpr int32_t SF_Teleport = 1 << 0;

	void			Spawn() override;
	void			SpawnKey( const std::string& key, const std::string& value ) override;

	// For AI
	virtual void	OnReachedCorner( SynchedEntityBase * traveler );

	inline const char* GetPathTarget() override {
		return pathTarget.c_str();
	}

private:
	std::string		pathTarget;
};
