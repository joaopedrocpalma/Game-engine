#pragma once
#include <string>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window.hpp> 
#include <irrlicht.h>

#include <iostream>
enum class EventType
{
	None,
	// Keyboard
	KeyPressed, KeyReleased,
	// Mouse
	MouseButtonPressed, MouseButtonReleased, MouseMoved,
	// Joystick
	JotstickButtonPressed, JotstickButtonReleased, LeftStickMoved, RightStickMoved,
	// Sounds
	PlaySound, PlaySoundLoop, PlayMusic,
	// Physics to graphics interactions
	UpdateTransform, UpdateScale, // If scale can be affected by physics
	// Graphics to physics interactions
	UpdateCameraLookDir, UpdateCameraRight, UpdateDeltaTime,
	// Interactions and player
	SpotEnemy, Interaction, ReceiveDamage, ReceiveHealth, // Currently all unused
	// Enemy
	SpotPlayer, LoosePlayer, GiveDamage, // Currently all unused
	// Application
	LoadLevel, Quit, ToggleDebugInfo, Wireframe
};

class Event
{
public:
	Event(EventType type);
	Event(int key, EventType type);
	Event(float dt, EventType type);
	Event(sf::Vector2i joy_stick_pos, int joy_stick, EventType type);
	Event(irr::core::vector3df cam_trans, EventType type);
	~Event() {}

	// Event getters - these are accessed in each subsystems HandlEvent() functions
	inline EventType GetEventType() { return m_eType; }
	inline int GetKeyPressed() { return m_key; }
	inline sf::Vector2i GetLeftJoystickPos() { return m_left_stick_pos; }
	inline sf::Vector2i GetRightJoystickPos() { return m_right_stick_pos; }
	inline irr::core::vector3df GetCamTransform() { return camera_transform; }
	inline float GetDeltaTime() { return delta_time; }
private:
	// Event type
	EventType m_eType{ EventType::None };
	// Input variables
	int m_key{};
	sf::Vector2i m_left_stick_pos{};
	sf::Vector2i m_right_stick_pos{};
	// Camera variables
	irr::core::vector3df camera_transform; // Used to pass camera look direction and camera right to the physics subsystem

	float delta_time; // delta time passed from graphics to physics
};