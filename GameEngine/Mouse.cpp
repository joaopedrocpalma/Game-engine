#include "Mouse.h"

void Mouse::GetInput()
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) 
		HandleInput(sf::Mouse::Left);
	
	if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) 
		HandleInput(sf::Mouse::Right);
	
}

void Mouse::HandleInput(int key)
{
	m_key = key;
	m_mouse_pos = sf::Mouse::getPosition();
	//std::cout << m_mouse_pos.x << ' ' << m_mouse_pos.y << ' ' << '\n';
	
	
	switch (m_key)
	{
	case 1:
	case 0:
	{
	    Event* mouse_button_press = new Event(m_key, EventType::MouseButtonPressed);
	    EventHandler::AddEvent(mouse_button_press);
	    break;
	}
	default:
	    std::cout << "Error: unregistered mouse input " << m_key << '\n';
	    break;
	}
}

