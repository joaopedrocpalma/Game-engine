#pragma once
#include "InputSubsystem.h"

class Mouse : public Input
{
public:
	~Mouse() {};
	void GetInput();
	int GetKey() { return m_key; }
private:
	void HandleInput(int key);
	void HandleMovement(sf::Vector2i mouse_pos);
};

