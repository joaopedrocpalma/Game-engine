#include "Event.h"

Event::Event(EventType type)
{
	m_eType = type;
}

Event::Event(int key, EventType type)
{
	m_key = key;
	m_eType = type;
}

Event::Event(float dt, EventType type)
{
	delta_time = dt;
	m_eType = type;
}

Event::Event(sf::Vector2i joy_stick_pos, int joy_stick, EventType type)
{
	if (joy_stick == 0)
		m_left_stick_pos = joy_stick_pos;
	if (joy_stick == 1)
		m_right_stick_pos = joy_stick_pos;

	m_eType = type;
}


Event::Event(irr::core::vector3df cam_trans, EventType type)
{
	camera_transform = cam_trans;
	m_eType = type;
}