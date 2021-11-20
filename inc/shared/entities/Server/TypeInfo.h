#pragma once

#include <string>

class ServerGameEntity;

//===============
// A static counter, used by TypeInfo to get compile-time IDs
//===============
class StaticCounter {
public:

	// You can also use this to check the total number of classes
	inline static size_t GlobalID = 0U;

	StaticCounter() {
		localID = GlobalID;
		GlobalID++;
	}

	size_t GetID() const {
		return localID;
	}

private:
	size_t localID;
};

using ServerGameEntityAllocatorFn = ServerGameEntity* ( ServerEntity* );

//===============
// TypeInfo, a system for getting runtime information about classes
//===============
class TypeInfo {
public:
	enum
	{
		TypeFlag_None = 0,
		// Cannot be allocated
		TypeFlag_Abstract = 1 << 0,
		// Can be spawned in the map
		TypeFlag_MapSpawn = 1 << 1
	};

public:
	TypeInfo( const char* mapClassName, const char* entClassName, const char* superClassName, uint8_t flags, ServerGameEntityAllocatorFn entityAllocator )
		: mapClass( mapClassName ), className( entClassName ), superName( superClassName ), typeFlags( flags ) {
		AllocateInstance = entityAllocator;
		prev = head;
		head = this;

		// Doesn't actually quite work here, so I wrote SetupSuperClasses
		super = GetInfoByName( superClassName );
	}

	// This will be used to allocate instances of each ServerGameEntity class
	// In theory, multiple map classnames can allocate one C++ class
	ServerGameEntityAllocatorFn* AllocateInstance;

	// Is this ServerGameEntity of this specific class?
	bool IsClass( const TypeInfo& eci ) const {
		return classInfoID.GetID() == eci.classInfoID.GetID();
	}

	// Is this ServerGameEntity a subclass of this class?
	bool IsSubclassOf( const TypeInfo& eci ) const {
		if ( nullptr == super )
			return false;

		if ( classInfoID.GetID() == eci.classInfoID.GetID() )
			return true;

		return super->IsSubclassOf( eci );
	}

	bool IsMapSpawnable() const {
		return !IsAbstract() && typeFlags & TypeFlag_MapSpawn;
	}

	bool IsAbstract() const {
		return typeFlags & TypeFlag_Abstract;
	}

	// Get type info by map classname
	static TypeInfo* GetInfoByMapName( const char* name ) { 
		if ( nullptr == name ) {
			return nullptr;
		}

		TypeInfo* current = nullptr;
		current = head;

		while ( current ) {
			if ( !strcmp( current->mapClass, name ) ) {
				return current;
            }
			current = current->prev;
		}

		return nullptr;
	}

	// Get type info by name
	static TypeInfo* GetInfoByName( const char* name ) {
		if ( nullptr == name ) {
			return nullptr;
		}

		TypeInfo* current = nullptr;
		current = head;

		while ( current ) {
			if ( !strcmp( current->className, name ) ) {
				return current;
            }
			current = current->prev;
		}

		return nullptr;
	}

	// This is called during game initialisation to properly set all superclasses
	static void SetupSuperClasses() {
		TypeInfo* current = nullptr;
		current = head;

		while ( current ) {
			current->super = GetInfoByName( current->superName );
			current = current->prev;
		}
	}

	TypeInfo*       prev;
	inline static TypeInfo* head = nullptr;

	StaticCounter   classInfoID; // automatically increments itself; TODO: maybe generate a CRC32 for each classname instead?
	TypeInfo*       super;

	const char*     mapClass;
	const char*     className;
	const char*     superName;
	uint8_t			typeFlags;
};

// ========================================================================
// Welcome to macro abuse purgatory, a.k.a. M.A.P.
// TODO: rewrite these macros using templates? It'd be quite nicer that way
// ========================================================================

// Declares and initialises the type information for a class 
// @param mapClassName - the map classname of this Entity, used during Entity spawning 
// @param className - the internal C++ class name 
#define __DeclareTypeInfo( mapClassName, className, superClass, typeFlags, allocatorFunction )	\
virtual inline TypeInfo* GetTypeInfo() const {					\
	return &ClassInfo;											\
}																\
inline static TypeInfo ClassInfo = TypeInfo( (mapClassName), (className), (superClass), (typeFlags), (allocatorFunction) );

// Top abstract class, the start of the class tree 
// Instances of this cannot be allocated, as it is abstract 
#define DefineTopAbstractClass( className )						\
__DeclareTypeInfo( #className, #className, nullptr, TypeInfo::TypeFlag_Abstract, nullptr );

// Abstract class that inherits from another 
// Instances of this cannot be allocated 
// NOTE: multiple inheritance not supported
#define DefineAbstractClass( className, superClass )			\
using Base = superClass;										\
__DeclareTypeInfo( #className, #className, #superClass, TypeInfo::TypeFlag_Abstract, nullptr );

// Declares and initialises the type information for this class, so it can be spawned in a map. 
// NOTE: multiple inheritance not supported
// @param mapClassName (string) - the map classname of this ServerEntity, used during ServerEntity spawning
// @param className (symbol) - the internal C++ class name
// @param superClass (symbol) - the class this ServerEntity class inherits from
#define DefineMapClass( mapClassName, className, superClass )	\
using Base = superClass;										\
static ServerGameEntity* AllocateInstance( ServerEntity* serverEntity ) {		\
	return new className( serverEntity );								\
}																\
__DeclareTypeInfo( mapClassName, #className, #superClass, TypeInfo::TypeFlag_MapSpawn, &className::AllocateInstance );

// Declares type information the same as DefineMapClass, however, it doesn't allocate anything. 
// Used by InfoNull. Cannot be instantiated. 
// Its type flag is TypeFlag_MapSpawn, but it has a nullptr AllocateInstance. This is to avoid
// a certain developer warning when spawning info_null
#define DefineDummyMapClass( mapClassName, className, superClass )\
using Base = superClass;											\
__DeclareTypeInfo( mapClassName, #className, #superClass, TypeInfo::TypeFlag_MapSpawn, nullptr );

// Declares and initialises the type information for this class 
// NOTE: multiple inheritance not supported
// @param className (symbol) - the internal C++ class name
// @param superClass (symbol) - the class this ServerEntity class inherits from
#define DefineClass( className, superClass )					\
using Base = superClass;										\
static ServerGameEntity* AllocateInstance( ServerEntity* ServerEntity ) {		\
	return new className( ServerEntity );								\
}																\
__DeclareTypeInfo( #className, #className, #superClass, TypeInfo::TypeFlag_None, &className::AllocateInstance );
