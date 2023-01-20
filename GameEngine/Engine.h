#pragma once
#include <iostream>
#include <vector>
#include "InputSubsystem.h"
#include "GraphicsSubsystem.h"
#include "PhysicsSubsystem.h"
#include "AudioSubsystem.h"
#include "ScoreSubsystem.h"
#include "GameObject.h"

extern "C" {
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
}

//#include <LuaBridge\LuaBridge.h>

/// <summary>
/// The engine class is responsible for calling each subsystems update methods.
/// It can also load levels and handle its own events.
/// </summary>

class Engine
{
public:
	Engine();
	~Engine(); // Virtual allows for the base class destructor to be called when an inherited class's destructor is called. Making sure all memory is freed

	// Call the global update loop
	void Update();
	// Load a given level
	void LoadLevel(lua_State* lua_level_file);
	// Handle engine events
	void HandleEvents();

	static GameObject* GetPlayer();

	//static AudioSubsystem* GetAudio();	// I don't understand what the issue is, 

	virtual void ChangeLevel();

	static bool running;
private:
	lua_State* lua_file; // The Lua file to be based to init a given subsystem
};