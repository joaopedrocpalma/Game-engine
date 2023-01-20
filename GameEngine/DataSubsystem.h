#pragma once
#include <algorithm>
#include "Subsystem.h"

extern "C" {
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
}
#include <LuaBridge\LuaBridge.h>
#include <fstream>


typedef luabridge::LuaRef lua_r;

/// <summary>
/// The data subsyst is used to intialise each subsystems default varaibles, E.g., the window size, mass of physics object, etc.
/// The get elements function accesses a given lua file, reads its data, and stores it in an array which we can then access in
/// to retrieve the necessary data in each subsystem.
/// </summary>

class DataSubsystem : public Subsystem
{
public:
	static std::vector<std::string> GetElements(const std::string& tab, lua_State* lua_file);
	static lua_State* GetLuaFile(const char* file_path);
	//static std::string GetHTMLFile(std::string file_path); // unused, not sure if its better to call read in html file from this class or the score class
};

