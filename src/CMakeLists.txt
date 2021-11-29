cmake_minimum_required (VERSION 3.8)
###############################################################################
##
##			SOURCE AND HEADER FILE LISTS
##
###############################################################################
###################### CLIENT GAME
SET(SRC_CLGAME
	CLGame/ClientGameExports.cpp
	CLGame/ClientGameImports.cpp

	CLGame/Exports/Core.cpp
	CLGame/Exports/Entities.cpp
	CLGame/Exports/Media.cpp
	CLGame/Exports/Movement.cpp
	CLGame/Exports/Prediction.cpp
	CLGame/Exports/Screen.cpp
	CLGame/Exports/ServerMessage.cpp
	CLGame/Exports/View.cpp

	CLGame/Effects.cpp
	CLGame/Entities.cpp
	CLGame/Input.cpp
	CLGame/Main.cpp
	CLGame/Media.cpp
	CLGame/NewFX.cpp
	CLGame/Parse.cpp
	CLGame/Predict.cpp
	CLGame/Screen.cpp
	CLGame/TemporaryEntities.cpp
	CLGame/View.cpp

	CLGame/ClientGame.def
)

SET(HEADERS_CLGAME
	CLGame/ClientGameExports.h
	CLGame/ClientGameImports.h

	CLGame/Exports/Core.h
	CLGame/Exports/Entities.h
	CLGame/Exports/Media.h
	CLGame/Exports/Movement.h
	CLGame/Exports/Prediction.h
	CLGame/Exports/Screen.h
	CLGame/Exports/ServerMessage.h
	CLGame/Exports/View.h

	CLGame/Effects.h
	CLGame/Entities.h
	CLGame/Input.h
	CLGame/ClientGameLocal.h
	CLGame/Main.h
	CLGame/Media.h
	CLGame/NewFX.h
	CLGame/Parse.h
	CLGame/Predict.h
	CLGame/Screen.h
	CLGame/TemporaryEntities.h
	CLGame/View.h
)

# Server game DLL
# Throw all sources in here, but group them elsewhere
SET( SRC_SVGAME 
	## Sources - Server Game
	SVGame/ChaseCamera.cpp
	SVGame/Commands.cpp
	SVGame/Combat.cpp
	SVGame/Effects.cpp
	SVGame/Entities.cpp
	SVGame/Items.cpp
	SVGame/ImportsWrapper.cpp
	SVGame/Main.cpp
	SVGame/Save.cpp
	SVGame/Spawn.cpp
	SVGame/ServerCommands.cpp
	SVGame/Trigger.cpp
	SVGame/Utilities.cpp
	SVGame/Weapons.cpp 

	SVGame/AI/MonsterAI.cpp

	## Source: SVGame - Entities - Base
	#SVGame/Entities/Base/ServerGameEntity.cpp
	SVGame/Entities/Base/SVGBaseTrigger.cpp
	SVGame/Entities/Base/SVGBaseMover.cpp
	SVGame/Entities/Base/PlayerEntity.cpp

	## Source: SVGame - Entities - Info
	#SVGame/Entities/Info/InfoNotNull.cpp
	SVGame/Entities/Info/InfoNull.cpp
	SVGame/Entities/Info/InfoPlayerCoop.cpp
	SVGame/Entities/Info/InfoPlayerDeathmatch.cpp
	SVGame/Entities/Info/InfoPlayerIntermission.cpp
	SVGame/Entities/Info/InfoPlayerStart.cpp

	## Source: SVGame - Entities - Func
	SVGame/Entities/Func/FuncAreaportal.cpp
	SVGame/Entities/Func/FuncButton.cpp
	#SVGame/Entities/Func/FuncConveyor.cpp
	SVGame/Entities/Func/FuncDoor.cpp 
	SVGame/Entities/Func/FuncDoorRotating.cpp
	SVGame/Entities/Func/FuncExplosive.cpp 
	#SVGame/Entities/Func/FuncKillbox.cpp
	#SVGame/Entities/Func/FuncObject.cpp
	#SVGame/Entities/Func/FuncPlat.cpp
	SVGame/Entities/Func/FuncRotating.cpp
	SVGame/Entities/Func/FuncTimer.cpp
	SVGame/Entities/Func/FuncTrain.cpp 
	SVGame/Entities/Func/FuncWall.cpp
	#SVGame/Entities/Func/FuncWater.cpp

	## Source: SVGame - Entities - Misc
	#SVGame/Entities/Misc/MiscExplobox.cpp
	#SVGame/Entities/Misc/MiscGibArm.cpp 
	#SVGame/Entities/Misc/MiscGibLeg.cpp 
	#SVGame/Entities/Misc/MiscGibHead.cpp 
	SVGame/Entities/Misc/MiscExplosionBox.cpp
	SVGame/Entities/Misc/MiscServerModel.cpp
	#SVGame/Entities/Misc/MiscTeleporter.cpp
	#SVGame/Entities/Misc/MiscTeleporterDest.cpp

	## Source: SVGame - Entities - Path
	SVGame/entities/path/PathCorner.cpp

	## Source: SVGame - Entities - Target
	#SVGame/Entities/Target/TargetBlaster.cpp
	#SVGame/Entities/Target/TargetChangelevel.cpp
	#SVGame/Entities/Target/TargetCrosslevel_target.cpp
	#SVGame/Entities/Target/TargetCrosslevel_trigger.cpp
	SVGame/Entities/Target/TargetEarthquake.cpp
	SVGame/Entities/Target/TargetExplosion.cpp
	#SVGame/Entities/Target/TargetLightramp.cpp
	#SVGame/Entities/Target/TargetSpawner.cpp
	SVGame/Entities/Target/TargetSpeaker.cpp
	#SVGame/Entities/Target/TargetSplash.cpp
	SVGame/Entities/Target/TargetTempEntity.cpp

	## Source: SVGame - Entities - Trigger
	SVGame/Entities/Trigger/TriggerCounter.cpp
	#SVGame/Entities/Trigger/TriggerElevator.cpp
	SVGame/Entities/Trigger/TriggerGravity.cpp
	#SVGame/Entities/Trigger/TriggerKey.cpp
	#SVGame/Entities/Trigger/TriggerMonsterjump.cpp
	SVGame/Entities/Trigger/TriggerPush.cpp
	SVGame/Entities/Trigger/TriggerAlways.cpp
	SVGame/Entities/Trigger/TriggerAutoDoor.cpp
	SVGame/Entities/Trigger/TriggerDelayedUse.cpp
	SVGame/Entities/Trigger/TriggerHurt.cpp
	SVGame/Entities/Trigger/TriggerMultiple.cpp
	SVGame/Entities/Trigger/TriggerOnce.cpp
	SVGame/Entities/Trigger/TriggerRelay.cpp

	## Source: SVGame - Entities - Weaponry
	SVGame/Entities/Weaponry/BlasterBolt.cpp

	## Source: SVGame - Entities - World
	SVGame/Entities/World/BodyCorpse.cpp
	SVGame/Entities/World/DebrisEntity.cpp
	SVGame/Entities/World/GibEntity.cpp
	SVGame/Entities/World/Light.cpp
	SVGame/Entities/World/WorldSpawn.cpp

	## Source: SVGame - GameModes
	SVGame/Gamemodes/DefaultGameMode.cpp
	SVGame/Gamemodes/CoopGameMode.cpp
	SVGame/Gamemodes/DeathMatchGameMode.cpp

	## Source: SVGame - Physics
	SVGame/Physics/Physics.cpp
	SVGame/Physics/Stepmove.cpp

	## Source: SVGame - Player
	SVGame/Player/Client.cpp
	SVGame/Player/Hud.cpp
	SVGame/Player/Trail.cpp
	SVGame/Player/Player.cpp
	SVGame/Player/View.cpp
	SVGame/Player/Weapons.cpp

	## Source: SVGame - Weapons
	SVGame/Weapons/Blaster.cpp
	SVGame/Weapons/Machinegun.cpp
	SVGame/Weapons/Shotgun.cpp
	SVGame/Weapons/SuperShotgun.cpp
    SVGame/svgame.def
    )
    
    SET ( HEADERS_SVGAME
		## Headers - Server Game
		SVGame/g_local.h
		SVGame/ChaseCamera.h
		SVGame/Effects.h
		SVGame/Entities.h
		SVGame/Trigger.h
		SVGame/Utilities.h
		SVGame/AI/MonsterAI.h

		## Source: SVGame - Entities - Base
		#SVGame/Entities/Base/ServerGameEntity.h
		SVGame/Entities/Base/PrivateEntityBase.cpp
		SVGame/Entities/Base/SynchedEntityBase.cpp
		SVGame/Entities/Base/SVGBaseTrigger.h
		SVGame/Entities/Base/SVGBaseMover.h
		SVGame/Entities/Base/PlayerEntity.h

		## Source: SVGame - Entities - Func
		SVGame/Entities/Func/FuncAreaportal.h
		SVGame/Entities/Func/FuncButton.h
		SVGame/Entities/Func/FuncDoor.h
		SVGame/Entities/Func/FuncDoorRotating.h
		SVGame/Entities/Func/FuncExplosive.h
		SVGame/Entities/Func/FuncRotating.h
		SVGame/Entities/Func/FuncTimer.h
		SVGame/Entities/Func/FuncTrain.h
		SVGame/Entities/Func/FuncWall.h

		## Source: SVGame - Entities - Info
		SVGame/Entities/Info/InfoPlayerStart.h
		
		## Source: SVGame - Entities - Misc
		SVGame/Entities/Misc/MiscExplosionBox.h
		SVGame/Entities/Misc/MiscServerModel.h

		## Source: SVGame - Entities - Path
		SVGame/Entities/Path/PathCorner.h

		## Source: SVGame - Entities - Target
		SVGame/Entities/Target/TargetEarthquake.h
		SVGame/Entities/Target/TargetExplosion.h
		SVGame/Entities/Target/TargetSpeaker.h
		SVGame/Entities/Target/TargetTempEntity.h

		## Source: SVGame - Entities - Trigger
		SVGame/Entities/Trigger/TriggerAlways.h
		SVGame/Entities/Trigger/TriggerAutoDoor.h
		SVGame/Entities/Trigger/TriggerCounter.h
		SVGame/Entities/Trigger/TriggerDelayedUse.h
		SVGame/Entities/Trigger/TriggerHurt.h
		SVGame/Entities/Trigger/TriggerGravity.h
		SVGame/Entities/Trigger/TriggerMultiple.h
		SVGame/Entities/Trigger/TriggerOnce.h
		SVGame/Entities/Trigger/TriggerPush.h
		SVGame/Entities/Trigger/TriggerRelay.h

		## Source: SVGame - Entities - Weaponry
		SVGame/Entities/Weaponry/BlasterBolt.h

		## Source: SVGame - Entities - World
		SVGame/Entities/World/Light.h
		SVGame/Entities/World/WorldSpawn.h

		## Source: SVGame - Gamemodes
		SVGame/Gamemodes/DefaultGameMode.h
		SVGame/Gamemodes/CoopGameMode.h
		SVGame/Gamemodes/DeathMatchGameMode.h
		SVGame/Gamemodes/IGameMode.h

		## Source:  SVGame - Player
		SVGame/Player/Animations.h
		SVGame/Player/Client.h
		SVGame/Player/Player.h
		SVGame/Player/View.h
		SVGame/Player/Weapons.h

		## Source:  SVGame - Weapons
		SVGame/Weapons/Blaster.h
		SVGame/Weapons/Machinegun.h
		SVGame/Weapons/Shotgun.h
		SVGame/Weapons/SuperShotgun.h

		## Source: SVGame - .
		SVGame/svgame.def
    )
    
    ###################### Client.
SET(SRC_CLIENT
	Client/ASCII.cpp
	Client/Console.cpp
	Client/Cinematic.cpp
	Client/ClientGame.cpp
	Client/CRC.cpp
	Client/Demo.cpp
	Client/Download.cpp
	#Client/effects.cpp
	Client/Entities.cpp
	#Client/gtv.cpp
	Client/Input.cpp
	Client/Keys.cpp
	Client/Main.cpp
	Client/Parse.cpp
	Client/Precache.cpp
	Client/Predict.cpp
	Client/Refresh.cpp
	Client/Screen.cpp
	Client/View.cpp
	Client/UserInterface/Demos.cpp
	Client/UserInterface/Menu.cpp
	Client/UserInterface/Playerconfig.cpp
	Client/UserInterface/Playermodels.cpp
	Client/UserInterface/Script.cpp
	Client/UserInterface/Servers.cpp
	Client/UserInterface/Management.cpp
	#Client/SoundDrivers/DirectMemoryAccess.cpp
	Client/SoundDrivers/OpenAL.cpp
	Client/SoundDrivers/Sound.cpp
	Client/SoundDrivers/Memory.cpp
	Client/SoundDrivers/Mixer.cpp
	Client/SoundDrivers/OGG.cpp
#	Client/SoundDrivers/PolyHedronOpenAL/fixed.c
	Client/SoundDrivers/PolyHedronOpenAL/Dynamic.cpp
)
# Required as a placeholder for certain Vulkan only related features.
if (NOT CONFIG_VKPT_RENDERER AND CONFIG_GL_RENDERER)
	set(SRC_CLIENT 
		${SRC_CLIENT}
		Client/null_gl.cpp
	)
endif()

if (CONFIG_ENABLE_RMLUI)
	SET(SRC_CLIENT_RMLUI
		Client/RMLUserInterface/Interfaces/FileInterface.cpp
		Client/RMLUserInterface/Interfaces/FileInterface.h
		Client/RMLUserInterface/Interfaces/RenderInterface.cpp
		Client/RMLUserInterface/Interfaces/RenderInterface.h
		Client/RMLUserInterface/Interfaces/SystemInterface.cpp
		Client/RMLUserInterface/Interfaces/SystemInterface.h
		Client/RMLUserInterface/RmlUserInterface.cpp
		Client/RMLUserInterface/RmlUserInterface.h
	)
else()
	SET(SRC_CLIENT_RMLUI
		Client/RMLUserInterface/RmlNullUserInterface.cpp
		Client/RMLUserInterface/RmlUserInterface.h
	)
endif()

SET(SRC_CLIENT_HTTP
	Client/Http.cpp
)
SET(HEADERS_CLIENT
	Client/Client.h
	#Client/UserInterface.h
	Client/SoundDrivers/Sound.h
	Client/SoundDrivers/PolyHedronOpenAL/Dynamic.h
	Client/SoundDrivers/PolyHedronOpenAL/Fixed.h
)

###################### Server.
SET(SRC_SERVER
	Server/Commands.cpp
	Server/Entities.cpp
	Server/ServerGame.cpp
	Server/Init.cpp
	Server/Main.cpp

	Server/Send.cpp
	Server/User.cpp
	Server/World.cpp

	Server/Save.cpp
)
SET(HEADERS_SERVER
	Server/server.h
)

###################### Common.
SET(SRC_COMMON
	Common/bsp.cpp
	Common/cmd.cpp
	Common/cmodel.cpp
	Common/Common.cpp
	Common/cvar.cpp
	Common/error.cpp
	Common/field.cpp
	Common/fifo.cpp
	Common/files.cpp
	Common/mdfour.cpp
	Common/msg.cpp
	Common/prompt.cpp
	Common/sizebuf.cpp
	Common/utils.cpp
	Common/zone.cpp

	Common/Hashes/crc32.cpp

	Common/Net/netchan.cpp
	Common/Net/net.cpp

	# These might have to go some day.
	#Common/netq3/netchan.cpp
	#Common/netq3/net.cpp
)
SET(HEADERS_COMMON
	Common/Net/inet_ntop.h
	Common/Net/inet_pton.h
	Common/Net/win.h
	
	Common/Hashes/crc32.h
)

###################### Format.
SET(HEADERS_COMMON
	../inc/Format/bsp.h
	../inc/Format/iqm.h
	../inc/Format/md2.h
	../inc/Format/md3.h
	../inc/Format/pak.h
	../inc/Format/pcx.h
	../inc/Format/sp2.h
	../inc/Format/wal.h
)

###################### Refresh.
SET(SRC_REFRESH
	Refresh/images.cpp
	Refresh/models.cpp
	Refresh/model_iqm.cpp
	Refresh/stb/stb.cpp
)

###################### GL.
SET(SRC_GL
	Refresh/gl/draw.cpp
	Refresh/gl/hq2x.cpp
	Refresh/gl/images.cpp
	Refresh/gl/main.cpp
	Refresh/gl/mesh.cpp
	Refresh/gl/models.cpp
	Refresh/gl/sky.cpp
	Refresh/gl/state.cpp
	Refresh/gl/surf.cpp
	Refresh/gl/tess.cpp
	Refresh/gl/world.cpp
	Refresh/gl/qgl/dynamic.cpp
#	Refresh/gl/qgl/fixed.c
)
SET(HEADERS_GL
	Refresh/gl/arbfp.h
	Refresh/gl/gl.h
)

###################### Shared Game Folder.
SET(HEADERS_SHAREDGAME
	../inc/SharedGame/PlayerMove.h 
	../inc/SharedGame/Protocol.h 
	../inc/SharedGame/SharedGame.h 
)
SET(SRC_SHAREDGAME
	../src/SharedGame/PlayerMove.cpp
)

###################### Shared Folder.
SET(HEADERS_SHARED
	# Container lib.
	#

	# Entities.
	../inc/Shared/Entities/Base/ServerEntity.h
	../inc/Shared/Entities/Base/EntityBase.h

	# Interfaces
	../inc/Shared/Interfaces/IClientGameExports.h
	../inc/Shared/Interfaces/IClientGameImports.h

	# Math lib.
	../inc/Shared/math/Color.h
	../inc/Shared/math/Matrix3.h
	../inc/Shared/math/Matrix4.h
	../inc/Shared/math/Plane.h
	../inc/Shared/math/Rectangle.h
	../inc/Shared/math/Utilities.h
	../inc/Shared/math/Vector2.h
	../inc/Shared/math/Vector3.h
	../inc/Shared/math/Vector4.h
	../inc/Shared/math/Vector5.h
	
	# Other Shared lib functionalities.
	../inc/Shared/ClientGame.h
	../inc/Shared/ClientGameTypes.h
	../inc/Shared/Collision.h
	../inc/Shared/Common.h
	../inc/Shared/Config.h
	../inc/Shared/Endian.h 
	../inc/Shared/ServerGame.h 
	../inc/Shared/KeyboardKeys.h 
	../inc/Shared/List.h 
	../inc/Shared/Math.h 
	../inc/Shared/Messaging.h 
	../inc/Shared/Platform.h
	../inc/Shared/Refresh.h 
	../inc/Shared/QString.h 
	../inc/Shared/Strings.h
	../inc/Shared/Shared.h 
	../inc/Shared/TickRate.h 
	../inc/Shared/UserInterface.h 
)
SET(SRC_SHARED
	# Maths.
	Shared/math/Plane.cpp
	Shared/math/Vector3.cpp
	Shared/math.cpp

	# Entities.
	Shared/Entities/Base/EntityBase.cpp
	
	# Random
	Shared/Shared.cpp
)

###################### UNIX Client Specific.
SET(SRC_UNIX
	OS/unix/hunk.cpp
	OS/unix/system.cpp
	OS/unix/tty.cpp
)
SET(SRC_UNIX_CLIENT
	OS/sdl2/sound.cpp
	OS/sdl2/video.cpp
	OS/sdl2/time.cpp
)

###################### Windows Client Specific.
SET(SRC_WINDOWS
	OS/Windows/debug.cpp
	OS/Windows/hunk.cpp
	OS/Windows/system.cpp
)
SET(SRC_WINDOWS_CLIENT
	OS/Windows/wave.cpp
	OS/sdl2/video.cpp
	OS/sdl2/time.cpp
)
SET(HEADERS_WINDOWS
	OS/Windows/wgl.h
	OS/Windows/glimp.h
	OS/Windows/client.h
	OS/Windows/threads/threads.h
)

###################### VKPT.
SET(SRC_VKPT
	Refresh/VkPt/asvgf.cpp
	Refresh/VkPt/bloom.cpp
	Refresh/VkPt/bsp_mesh.cpp
	Refresh/VkPt/conversion.cpp
	Refresh/VkPt/draw.cpp
	Refresh/VkPt/freecam.cpp
	Refresh/VkPt/fog.cpp
	Refresh/VkPt/fsr.cpp
	Refresh/VkPt/main.cpp
	Refresh/VkPt/material.cpp
	Refresh/VkPt/matrix.cpp
	Refresh/VkPt/mgpu.cpp
	Refresh/VkPt/models.cpp
	Refresh/VkPt/path_tracer.cpp
	Refresh/VkPt/physical_sky.cpp
	Refresh/VkPt/precomputed_sky.cpp
	Refresh/VkPt/profiler.cpp
	Refresh/VkPt/shadow_map.cpp
	Refresh/VkPt/textures.cpp
	Refresh/VkPt/tone_mapping.cpp
	Refresh/VkPt/transparency.cpp
	Refresh/VkPt/uniform_buffer.cpp
	Refresh/VkPt/vertex_buffer.cpp
	Refresh/VkPt/vk_util.cpp
	Refresh/VkPt/buddy_allocator.cpp
	Refresh/VkPt/device_memory_allocator.cpp
	Refresh/VkPt/god_rays.cpp
)
SET(HEADERS_VKPT
	Refresh/VkPt/fsr/ffx_a.h
	Refresh/VkPt/fsr/ffx_fsr1.h

    Refresh/VkPt/Shader/constants.h
    Refresh/VkPt/Shader/global_textures.h
    Refresh/VkPt/Shader/global_ubo.h
    Refresh/VkPt/Shader/god_rays_Shared.h
    Refresh/VkPt/Shader/light_lists.h
    Refresh/VkPt/Shader/path_tracer_hit_shaders.h
    Refresh/VkPt/Shader/path_tracer_rgen.h
    Refresh/VkPt/Shader/path_tracer.h
    Refresh/VkPt/Shader/sky.h
    Refresh/VkPt/Shader/vertex_buffer.h

	Refresh/VkPt/VkPt.h
	Refresh/VkPt/vk_util.h
	Refresh/VkPt/buddy_allocator.h
	Refresh/VkPt/conversion.h
	Refresh/VkPt/device_memory_allocator.h
	Refresh/VkPt/fog.h
	Refresh/VkPt/material.h
	Refresh/VkPt/physical_sky.h
	Refresh/VkPt/precomputed_sky.h
)

###################### Vulkan Shaders.
set(SRC_SHADERS
	Refresh/VkPt/Shader/animate_materials.comp
	Refresh/VkPt/Shader/god_rays_filter.comp
	Refresh/VkPt/Shader/god_rays.comp
	Refresh/VkPt/Shader/bloom_composite.comp
	Refresh/VkPt/Shader/bloom_blur.comp
	Refresh/VkPt/Shader/bloom_downscale.comp
	Refresh/VkPt/Shader/compositing.comp
	Refresh/VkPt/Shader/checkerboard_interleave.comp
	Refresh/VkPt/Shader/asvgf_atrous.comp
	Refresh/VkPt/Shader/asvgf_gradient_atrous.comp
	Refresh/VkPt/Shader/asvgf_gradient_img.comp
	Refresh/VkPt/Shader/asvgf_gradient_reproject.comp
	Refresh/VkPt/Shader/asvgf_lf.comp
	Refresh/VkPt/Shader/asvgf_taau.comp
	Refresh/VkPt/Shader/asvgf_temporal.comp
	Refresh/VkPt/Shader/instance_geometry.comp
	Refresh/VkPt/Shader/tone_mapping_histogram.comp
	Refresh/VkPt/Shader/tone_mapping_curve.comp
    Refresh/VkPt/Shader/tone_mapping_apply.comp
	Refresh/VkPt/Shader/physical_sky.comp
	Refresh/VkPt/Shader/physical_sky_space.comp
	Refresh/VkPt/Shader/shadow_map.vert
	Refresh/VkPt/Shader/sky_buffer_resolve.comp
	Refresh/VkPt/Shader/stretch_pic.frag
	Refresh/VkPt/Shader/stretch_pic.vert
	Refresh/VkPt/Shader/final_blit_lanczos.frag
	Refresh/VkPt/Shader/final_blit.vert
	Refresh/VkPt/Shader/fsr_easu_fp16.comp
	Refresh/VkPt/Shader/fsr_easu_fp32.comp
	Refresh/VkPt/Shader/fsr_rcas_fp16.comp
	Refresh/VkPt/Shader/fsr_rcas_fp32.comp
)

set(SRC_RT_SHADERS
	Refresh/VkPt/Shader/primary_rays.rgen
	Refresh/VkPt/Shader/direct_lighting.rgen
	Refresh/VkPt/Shader/indirect_lighting.rgen
	Refresh/VkPt/Shader/path_tracer.rchit
	Refresh/VkPt/Shader/path_tracer.rmiss
	Refresh/VkPt/Shader/path_tracer_masked.rahit
	Refresh/VkPt/Shader/path_tracer_particle.rahit
	Refresh/VkPt/Shader/path_tracer_sprite.rahit
	Refresh/VkPt/Shader/path_tracer_beam.rahit
	Refresh/VkPt/Shader/path_tracer_beam.rint
	Refresh/VkPt/Shader/path_tracer_explosion.rahit
	Refresh/VkPt/Shader/reflect_refract.rgen
)

# Check for a Shader compiler.
if (CONFIG_VKPT_RENDERER)
	IF(IS_64_BIT)
		include(../cmake/compileShaders.cmake)

		foreach(s ${SRC_RT_SHADERS})
			get_filename_component(shader_name ${s} NAME)
			get_filename_component(shader_ext ${s} EXT)
			compile_shader(SOURCE_FILE ${s} OUTPUT_FILE_LIST shader_bytecode OUTPUT_FILE_NAME "${shader_name}.pipeline")
			if (shader_ext STREQUAL ".rgen")
				compile_shader(SOURCE_FILE ${s} OUTPUT_FILE_LIST shader_bytecode OUTPUT_FILE_NAME "${shader_name}.query" DEFINES "-DKHR_RAY_QUERY" STAGE "comp")
			endif()
		endforeach()

		foreach(s ${SRC_SHADERS})
			compile_shader(SOURCE_FILE ${s} INCLUDES "-I${CMAKE_CURRENT_SOURCE_DIR}/Refresh/VkPt/fsr" OUTPUT_FILE_LIST shader_bytecode)
		endforeach()

		add_custom_target(shaders DEPENDS ${shader_bytecode})

		if(TARGET glslangValidator)
			add_dependencies(shaders glslangValidator)
		endif()
	ENDIF()
endif()
# Embed version number
ADD_DEFINITIONS(-DVERSION_MAJOR=${POLYHEDRON_VERSION_MAJOR})
ADD_DEFINITIONS(-DVERSION_MINOR=${POLYHEDRON_VERSION_MINOR})
ADD_DEFINITIONS(-DVERSION_POINT=${POLYHEDRON_VERSION_POINT})
ADD_DEFINITIONS(-DVERSION_SHA=${POLYHEDRON_VERSION_SHA})
ADD_DEFINITIONS(-DVERSION_BRANCH=${POLYHEDRON_VERSION_BRANCH})

ADD_DEFINITIONS(-DHAVE_CONFIG_H=1 -DCURL_STATICLIB)

IF(WIN32)
	ADD_DEFINITIONS(-D_CRT_SECURE_NO_WARNINGS)
ENDIF()

# Optional build target.
if (CONFIG_BUILD_SV_GAME)
	# Used for SharedGame code(such as PlayerMove), so we can ifdef certain parts specific to client or server.	
	ADD_DEFINITIONS(-DSHAREDGAME_SERVER=1)
	# Add library.
	ADD_LIBRARY(svgame Shared 
		${SRC_SVGAME} 
		${HEADERS_SVGAME} 
		${SRC_SHARED} 
		${HEADERS_SHARED} 
		${SRC_SHAREDGAME} 
		${HEADERS_SHAREDGAME})
endif()

# Optional build target.
if (CONFIG_BUILD_CL_GAME)
	# Used for SharedGame code(such as PlayerMove), so we can ifdef certain parts specific to client or server.	
	ADD_DEFINITIONS(-DSHAREDGAME_CLIENT=1)
	# Add library.
	ADD_LIBRARY(clgame Shared ${SRC_CLGAME} ${HEADERS_CLGAME} ${SRC_SHARED} ${HEADERS_SHARED} ${SRC_SHAREDGAME} ${HEADERS_SHAREDGAME})
endif()

IF(WIN32)
ADD_EXECUTABLE(client WIN32 
	${SRC_CLIENT} ${HEADERS_CLIENT} 
	${SRC_COMMON} ${HEADERS_COMMON} 
	${SRC_REFRESH} ${SRC_SHADERS} 
	${SRC_SHARED} ${HEADERS_SHARED}
	${SRC_WINDOWS} ${SRC_WINDOWS_CLIENT} ${HEADERS_WINDOWS}
	${SRC_SERVER} ${HEADERS_SERVER}
	OS/res/polyhedron.rc
)
ADD_EXECUTABLE(server 
	${SRC_COMMON} ${HEADERS_COMMON} 
	${SRC_SHARED} ${HEADERS_SHARED}
	${SRC_WINDOWS} ${HEADERS_WINDOWS}
	${SRC_SERVER} ${HEADERS_SERVER}
	Client/null.cpp
	#OS/sdl2/time.cpp
	OS/res/polyhedron_dedicated.rc
)
ELSE()
ADD_EXECUTABLE(client
	${SRC_CLIENT} ${HEADERS_CLIENT} 
	${SRC_COMMON} ${HEADERS_COMMON} 
	${SRC_REFRESH} ${SRC_SHADERS} 
	${SRC_SHARED} ${HEADERS_SHARED}
	${SRC_UNIX} ${SRC_UNIX_CLIENT}
	${SRC_SERVER} ${HEADERS_SERVER}
)
ADD_EXECUTABLE(server
	${SRC_COMMON} ${HEADERS_COMMON} 
	${SRC_SHARED} ${HEADERS_SHARED}
	${SRC_UNIX}
	${SRC_SERVER} ${HEADERS_SERVER}
	Client/null.c
)
ENDIF()

TARGET_COMPILE_DEFINITIONS(client PRIVATE USE_SERVER=1 USE_CLIENT=1)
TARGET_COMPILE_DEFINITIONS(server PRIVATE USE_SERVER=1 USE_CLIENT=0)

IF(CONFIG_USE_CURL)
	ADD_DEFINITIONS(-DHAVE_CONFIG_H=1 -DCURL_STATICLIB)

	TARGET_SOURCES(client PRIVATE ${SRC_CLIENT_HTTP})
	TARGET_COMPILE_DEFINITIONS(client PRIVATE USE_CURL=1)
	TARGET_LINK_LIBRARIES(client libcurl)
ENDIF()

IF(CONFIG_ENABLE_RMLUI)
 	TARGET_SOURCES(client PRIVATE ${SRC_CLIENT_RMLUI})
	TARGET_INCLUDE_DIRECTORIES(client PRIVATE ${CMAKE_SOURCE_DIR}/extern/Nac-RmlUi/Include/)
	TARGET_COMPILE_DEFINITIONS(client PRIVATE USE_RMLUI=1 RMLUI_STATIC_LIB)
	TARGET_LINK_LIBRARIES(client RmlCore RmlDebugger RmlLua)
ELSE()
	# These are set to supply the rmlui_null.cpp file.
	TARGET_SOURCES(client PRIVATE ${SRC_CLIENT_RMLUI})
ENDIF()

if (GLSLANG_COMPILER AND CONFIG_VKPT_RENDERER)
	add_dependencies(client shaders)
endif()

IF (CONFIG_GL_RENDERER)
	TARGET_SOURCES(client PRIVATE ${SRC_GL} ${HEADERS_GL})
	TARGET_COMPILE_DEFINITIONS(client PRIVATE REF_GL=1 USE_REF=1)
ENDIF()

IF (CONFIG_VKPT_RENDERER)
	TARGET_SOURCES(client PRIVATE ${SRC_VKPT} ${HEADERS_VKPT})
	TARGET_INCLUDE_DIRECTORIES(client PRIVATE ${CMAKE_SOURCE_DIR}/extern/Vulkan-Headers/include)
	LINK_DIRECTORIES(client PRIVATE ${CMAKE_SOURCE_DIR})
	TARGET_COMPILE_DEFINITIONS(client PRIVATE REF_VKPT=1 USE_REF=1)
	IF (CONFIG_VKPT_ENABLE_DEVICE_GROUPS)
		TARGET_COMPILE_DEFINITIONS(client PRIVATE VKPT_DEVICE_GROUPS)
	ENDIF()
	if (CONFIG_VKPT_ENABLE_IMAGE_DUMPS)
		TARGET_COMPILE_DEFINITIONS(client PRIVATE VKPT_IMAGE_DUMPS)
	ENDIF()
	IF (WIN32)
	TARGET_LINK_LIBRARIES(client vulkan-1)
	ELSE ()
	TARGET_LINK_LIBRARIES(client vulkan)
	ENDIF()
ENDIF()

TARGET_LINK_LIBRARIES(client stb)
TARGET_LINK_LIBRARIES(client tinyobjloader)
#TARGET_LINK_LIBRARIES(server enet)

SOURCE_GROUP( TREE ${CMAKE_SOURCE_DIR} FILES ${SRC_COMMON})
SOURCE_GROUP( TREE ${CMAKE_SOURCE_DIR} FILES ${HEADERS_COMMON})
SOURCE_GROUP( TREE ${CMAKE_SOURCE_DIR} FILES ${SRC_CLIENT})
SOURCE_GROUP( TREE ${CMAKE_SOURCE_DIR} FILES ${HEADERS_CLIENT})
SOURCE_GROUP( TREE ${CMAKE_SOURCE_DIR} FILES ${SRC_SERVER})
SOURCE_GROUP( TREE ${CMAKE_SOURCE_DIR} FILES ${HEADERS_SERVER})

# Old SVGame source grouping - it just bundled *everything* into SVGame/sources and SVGame/headers, eugh -Admer
#SOURCE_GROUP("svgame" FILES ${SRC_SVGAME})
#SOURCE_GROUP("svgame" FILES ${HEADERS_SVGAME})

# Source and header groups
SOURCE_GROUP( TREE ${CMAKE_SOURCE_DIR} FILES ${SRC_SVGAME} )
SOURCE_GROUP( TREE ${CMAKE_SOURCE_DIR} FILES ${HEADERS_SVGAME} )
SOURCE_GROUP( TREE ${CMAKE_SOURCE_DIR} FILES ${SRC_SHAREDGAME} )
SOURCE_GROUP( TREE ${CMAKE_SOURCE_DIR} FILES ${HEADERS_SHAREDGAME} )

SOURCE_GROUP( TREE ${CMAKE_SOURCE_DIR} FILES ${SRC_REFRESH} ${SRC_VKPT})
SOURCE_GROUP( TREE ${CMAKE_SOURCE_DIR} FILES ${HEADERS_VKPT})
SOURCE_GROUP( TREE ${CMAKE_SOURCE_DIR} FILES ${SRC_SHADERS})
SOURCE_GROUP( TREE ${CMAKE_SOURCE_DIR} FILES ${SRC_SHARED})
SOURCE_GROUP( TREE ${CMAKE_SOURCE_DIR} FILES ${HEADERS_SHARED})
SOURCE_GROUP( TREE ${CMAKE_SOURCE_DIR} FILES ${SRC_WINDOWS})
SOURCE_GROUP( TREE ${CMAKE_SOURCE_DIR} FILES ${HEADERS_WINDOWS})
SOURCE_GROUP( TREE ${CMAKE_SOURCE_DIR} FILES ${SRC_UNIX})
SOURCE_GROUP( TREE ${CMAKE_SOURCE_DIR} FILES ${HEADERS_UNIX})

SOURCE_GROUP( TREE ${CMAKE_SOURCE_DIR} FILES Client/null.cpp )

IF (WIN32)
	TARGET_INCLUDE_DIRECTORIES(client PRIVATE ../VC/inc)
	TARGET_INCLUDE_DIRECTORIES(server PRIVATE ../VC/inc)
	TARGET_INCLUDE_DIRECTORIES(svgame PRIVATE ../VC/inc)
	TARGET_SOURCES(svgame PRIVATE OS/res/basepoly_sv.rc)
	TARGET_SOURCES(clgame PRIVATE OS/res/basepoly_cl.rc)

	TARGET_LINK_LIBRARIES(client winmm ws2_32)
	TARGET_LINK_LIBRARIES(server winmm ws2_32)

	set_target_properties(client PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}")
	set_target_properties(server PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}")

	# Macro redefinitions, for deprecations.
	target_compile_options(client PRIVATE /wd4005 /wd4996)
	target_compile_options(server PRIVATE /wd4005 /wd4996)
	target_compile_options(svgame PRIVATE /wd4005 /wd4996)

    ## Group the resource files too, so they don't end up in the ugly "Source Files" folder in VS
    SOURCE_GROUP( TREE ${CMAKE_SOURCE_DIR} FILES 
        OS/res/polyhedron.rc 
        OS/res/polyhedron_dedicated.rc )
ENDIF()

TARGET_INCLUDE_DIRECTORIES(svgame PRIVATE ../inc)
TARGET_INCLUDE_DIRECTORIES(clgame PRIVATE ../inc)

TARGET_INCLUDE_DIRECTORIES(client PRIVATE ../inc)
TARGET_INCLUDE_DIRECTORIES(client PRIVATE "${ZLIB_INCLUDE_DIRS}")
TARGET_INCLUDE_DIRECTORIES(server PRIVATE ../inc)
TARGET_INCLUDE_DIRECTORIES(server PRIVATE "${ZLIB_INCLUDE_DIRS}")

TARGET_INCLUDE_DIRECTORIES(client PRIVATE "/extern/stb/")

# WATISDEZE: Do we still need this?
# Use dynamic zlib for steam runtime
# if (CONFIG_LINUX_STEAM_RUNTIME_SUPPORT)
#     TARGET_LINK_LIBRARIES(client SDL2main SDL2-static z)
#     TARGET_LINK_LIBRARIES(server SDL2main SDL2-static z)
# else()
# TARGET_LINK_LIBRARIES(client SDL2main SDL2-static zlibstatic)
# TARGET_LINK_LIBRARIES(server SDL2main SDL2-static zlibstatic)
# endif()
TARGET_LINK_LIBRARIES(client SDL2main SDL2-static zlibstatic)
TARGET_LINK_LIBRARIES(server SDL2main SDL2-static zlibstatic)

SET_TARGET_PROPERTIES(client
    PROPERTIES
    OUTPUT_NAME "Polyhedron"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin"
    RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}/bin"
    RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/bin"
    RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO "${CMAKE_SOURCE_DIR}/bin"
    RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL "${CMAKE_SOURCE_DIR}/bin"
    DEBUG_POSTFIX ""
)

SET_TARGET_PROPERTIES(server
    PROPERTIES
    OUTPUT_NAME "Polyhedron_Dedicated"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin"
    RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}/bin"
    RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/bin"
    RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO "${CMAKE_SOURCE_DIR}/bin"
    RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL "${CMAKE_SOURCE_DIR}/bin"
    DEBUG_POSTFIX ""
)

# Client Game
if (CONFIG_BUILD_CL_GAME)
	# Specify both LIBRARY and RUNTIME because one works only on Windows and another works only on Linux
	SET_TARGET_PROPERTIES(clgame
		PROPERTIES
		LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/basepoly"
		LIBRARY_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}/bin/basepoly"
		LIBRARY_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/bin/basepoly"
		LIBRARY_OUTPUT_DIRECTORY_RELWITHDEBINFO "${CMAKE_SOURCE_DIR}/bin/basepoly"
		LIBRARY_OUTPUT_DIRECTORY_MINSIZEREL "${CMAKE_SOURCE_DIR}/bin/basepoly"
		RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/basepoly"
		RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}/bin/basepoly"
		RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/bin/basepoly"
		RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO "${CMAKE_SOURCE_DIR}/bin/basepoly"
		RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL "${CMAKE_SOURCE_DIR}/bin/basepoly"
		PREFIX ""
		DEBUG_POSTFIX ""
	)
endif()

# Server Game
if (CONFIG_BUILD_SV_GAME)
	# Specify both LIBRARY and RUNTIME because one works only on Windows and another works only on Linux
	SET_TARGET_PROPERTIES(svgame
		PROPERTIES
		LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/basepoly"
		LIBRARY_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}/bin/basepoly"
		LIBRARY_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/bin/basepoly"
		LIBRARY_OUTPUT_DIRECTORY_RELWITHDEBINFO "${CMAKE_SOURCE_DIR}/bin/basepoly"
		LIBRARY_OUTPUT_DIRECTORY_MINSIZEREL "${CMAKE_SOURCE_DIR}/bin/basepoly"
		RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/basepoly"
		RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}/bin/basepoly"
		RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/bin/basepoly"
		RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO "${CMAKE_SOURCE_DIR}/bin/basepoly"
		RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL "${CMAKE_SOURCE_DIR}/bin/basepoly"
		PREFIX ""
		DEBUG_POSTFIX ""
	)
endif()

# WATISDEZE: Do we still need this?
# IF(CONFIG_LINUX_PACKAGING_SUPPORT)
#     # Put the real game binary in /usr/share so we can have a wrapper in /usr/bin
#     INSTALL(TARGETS client DESTINATION share/quake2rtx/bin COMPONENT shareware)
#     INSTALL(TARGETS server DESTINATION games COMPONENT shareware)

#     # Compress NVIDIA custom content
#     INSTALL(CODE "set(SOURCE \"${CMAKE_SOURCE_DIR}\")"
#         SCRIPT "${CMAKE_SOURCE_DIR}/setup/package_media.cmake"
#         SCRIPT "${CMAKE_SOURCE_DIR}/setup/package_shaders.cmake"
#         COMPONENT shareware)
#     INSTALL(TARGETS svgame DESTINATION share/quake2rtx/basenac COMPONENT shareware)

#     # Package data files, including the shareware pak0 for demo levels
#     set (SHAREWARE_DATA_FILES_LIST
#         "${CMAKE_SOURCE_DIR}/basenac/q2rtx_media.pkz"
#         "${CMAKE_SOURCE_DIR}/basenac/shaders.pkz"
#         "${CMAKE_SOURCE_DIR}/basenac/blue_noise.pkz"
#         "${CMAKE_SOURCE_DIR}/basenac/shareware/pak0.pak"
#     )
#     INSTALL(FILES
#         ${SHAREWARE_DATA_FILES_LIST}
#         DESTINATION share/quake2rtx/basenac
#         COMPONENT shareware)

#     # Package shareware player model
#     INSTALL(DIRECTORY
#         "${CMAKE_SOURCE_DIR}/basenac/shareware/players"
#         DESTINATION share/quake2rtx/basenac
#         COMPONENT shareware)

#     # Package the legal and info files
#     INSTALL(FILES
#         "${CMAKE_SOURCE_DIR}/license.txt"
#         "${CMAKE_SOURCE_DIR}/notice.txt"
#         "${CMAKE_SOURCE_DIR}/readme.md"
#         "${CMAKE_SOURCE_DIR}/changelog.md"
#         DESTINATION share/quake2rtx/
#         COMPONENT shareware)

#     # Package the icon/desktop file
#     INSTALL(FILES
#         "${CMAKE_SOURCE_DIR}/setup/q2rtx.desktop"
#         DESTINATION share/applications/
#         COMPONENT shareware)
#     INSTALL(FILES
#         "${CMAKE_SOURCE_DIR}/setup/q2rtx.png"
#         DESTINATION share/pixmaps/
#         COMPONENT shareware)

#     # Install Client Wrapper
#     INSTALL(FILES
#         "${CMAKE_SOURCE_DIR}/setup/q2rtx.sh"
#         DESTINATION games/
#         PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE
#         COMPONENT shareware
# 	RENAME q2rtx)

#     # Install PAK file finder
#     INSTALL(FILES
#         "${CMAKE_SOURCE_DIR}/setup/find-retail-paks.sh"
#         DESTINATION share/quake2rtx/bin
#         PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE
#         COMPONENT shareware)
# ENDIF()
