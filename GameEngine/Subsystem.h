#pragma once

/// <summary>
/// Base subsystem class. Graphics, physics, audio, and input inherit from this class.
/// </summary>

extern "C" {
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
}

#include <LuaBridge\LuaBridge.h>

class Subsystem
{
	virtual void UpdateSubsystem() = 0;
};

