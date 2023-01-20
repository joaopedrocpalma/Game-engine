#pragma once
#include "Subsystem.h"
#include "Event.h";
#include "EventHandler.h";
#include <chrono>
#include <SFML/Window/Keyboard.hpp>
//#include <SFML/Window.hpp> // for sf::event

#include "GameObject.h"
#include "Engine.h"

/// <summary>
/// The input subsystem is splt into 4 classes with Input acting as the core, calling the update methods of keyboard, mouse, joystick derived classes.
/// Each derived input class handles its own input device speicifc inputs and creates events based on a given input.
/// </summary>

class Input : public Subsystem
{
public:
	Input() {};
	~Input() {};

	// initialise input key binds. 
	void InitInput(lua_State* lua_file);
	// Update the input subsystem
	virtual void UpdateSubsystem();
protected:
	// For Debug purposes only! input subsystem does not handle events on its own, but it can check if the child classes (keyboard, mouse, joystick) successfully create their events. 
	void HandleEvent();

	lua_State* lua_control_file{}; // Lua file used to initialise child subsystems

	// Input Variables
	std::map<int, bool> keys; // Check if a given key is pressed, if it is set bool value to true, otherwise false
	static std::vector<sf::Keyboard::Key> sfml_keys; // used to check if an SFML key has been pressed
	int m_key{}; // Stores a pressed button. Shared by keyboard and mouse classes
	sf::Vector2i m_mouse_pos{}; // Mouse position is relative to the window position
	sf::Vector2i left_stick_pos{}; // Left controller joy stick axis
	sf::Vector2i right_stick_pos{};// Right controller joy stick axis
	static float deadzone; // The controller deadzone. Bumper stick input below this value will be ignored

	// Timer varaibles
	typedef std::chrono::high_resolution_clock Clock;
	Clock::time_point current_time; // Current time
	Clock::time_point old_time; // Time of previous frame
	Clock::duration delta_time; // Change in time between frames
	float dt_f;
};