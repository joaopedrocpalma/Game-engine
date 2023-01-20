#pragma once
#include <iostream>
#include <iomanip>
#include <chrono>
#include <irrlicht.h>

#include "GameObject.h"
#include "Subsystem.h"
#include "Event.h"
#include "EventHandler.h"
#include "IrrCompileConfig.h"
#include "irrTypes.h"
#include "GUISubsystem.h"



using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

/// <summary>
/// The graphics subsystem is responsible for drawing all of the graphical elements on screen.
/// This subsystem is also resposible for calling GUI subsystems which (using irrlicht gui conponenets)
/// </summary>

class GraphicsSubsystem : public Subsystem
{
public:
	GraphicsSubsystem() {};
	// Initialise graphics varaibles like device, window, etc and populate them with a given lua file
	int InitGraphics(lua_State* lua_file);
	// Initialise models properties like position, rotation, scale, textures, etc. with a given lua file
	int InitModels(lua_State* lua_file, std::vector<GameObject*> objectList);
	// Temp function to pass delta time to physics subsystem. This was supposed to be done through the event queue but the value obtained is incorrect
	float GetDeltaTime() { return m_delta_time; }

	~GraphicsSubsystem();
	// Delete all currently loaded models and other varaibles associated with them. This should be called when loading a new level
	void UnloadModels();
	// Update the graphics subsystem
	void UpdateSubsystem();

	irr::scene::IAnimatedMeshSceneNode* GetModel(int index);

	virtual void UpdateCameraPos(GameObject** player);

private:
	void HandleEvent();

	IrrlichtDevice* device{};
	IVideoDriver* driver{};
	ISceneManager* scn_mngr{};
	IGUIEnvironment* gui_env{};

	f32 m_delta_time{ 16.7f };

	// Camera variables
	ICameraSceneNode* camera{};
	// Camera orientation
	vector3df camera_pos{};
	vector3df target{};
	vector3df look_dir{};
	vector3df up = vector3df(0, 1, 0);
	vector3df right{};

	// Left and right joy stick positions affects camera rotation
	vector3df camera_rot{};
	// Camera rotation varaibles
	vector3df camera_rot_x = vector3df(0, 1, 0);
	vector3df camera_rot_y = vector3df(1, 0, 0);

	std::wstring m_title{}; // Engine title
	std::wstring c_fps{}; // engine fps converted to a wstring

	std::vector<std::string> element_list; // Element list used to iterator over Lua objects

	// Array of game objects
	std::vector<IAnimatedMeshSceneNode*> Models; // Holds all of the model meshes
	std::vector<std::string> textures; // Holds model textres
	//std::vector<GameObject*> GameObjects; // unused

	bool toggle_wireframe = false;
	std::string debug; // Stores graphics specific debug information
	std::string model_dir;

	// Timer variablers
	typedef std::chrono::high_resolution_clock Clock;
	Clock::time_point current_time; // Current time
	Clock::time_point old_time; // Time of previous frame
	Clock::duration delta_time; // Change in time between frames
	float dt_f;

	// Irrlicht animations
	ISceneNodeAnimator* rotate_circle; // rotation animation
	ISceneNodeAnimator* spiny_anim; // spining animation
};