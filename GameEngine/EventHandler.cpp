#include "EventHandler.h"

std::vector<Event*> EventHandler::EventQueue;

void EventHandler::AddEvent(Event* event)
{
	EventQueue.push_back(event);
}

std::vector<Event*> EventHandler::GetEvents()
{
	return EventQueue;
}

void EventHandler::ClearEvents()
{
	EventQueue.clear();
}