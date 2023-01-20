#pragma once
#include "Event.h"
#include <iostream>
#include <vector>
#include <string>

/// <summary>
/// Event Handler - allows each subsystem to Get, Add, and Clear Events from the Event Queue vector.
/// Each subsystem handles their events individually.
/// </summary>

class EventHandler
{
public:
	static void AddEvent(Event* event);
	static std::vector<Event*> GetEvents(); // Event queue getter
	static void ClearEvents();

private:
	static std::vector<Event*> EventQueue;
};