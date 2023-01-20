#pragma once
#include "InputSubsystem.h"

class Keyboard : public Input
{
public:
	~Keyboard() {};
	void GetInput();
	int GetKey() { return m_key; }

private:
	void HandleButton(int key);
	bool keypressed = false;
};

