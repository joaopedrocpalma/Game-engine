#include "Keyboard.h"

void Keyboard::GetInput()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) 
    {
        if (!keys[sf::Keyboard::Key::Escape]) 
        {
            Event* quit_event = new Event(m_key, EventType::Quit);
            EventHandler::AddEvent(quit_event);
        }
        keys[sf::Keyboard::Key::Escape] = true;
    }
    else keys[sf::Keyboard::Key::Escape] = false;

 
    // W A S D[directions], Space[jump], T[audio] input keys
    if (sf::Keyboard::isKeyPressed(Input::sfml_keys[0]))
        HandleButton(Input::sfml_keys[0]);
    
    if (sf::Keyboard::isKeyPressed(Input::sfml_keys[1]))
        HandleButton(Input::sfml_keys[1]);
    
    if (sf::Keyboard::isKeyPressed(Input::sfml_keys[2]))
        HandleButton(Input::sfml_keys[2]);
    
    if (sf::Keyboard::isKeyPressed(Input::sfml_keys[3]))
        HandleButton(Input::sfml_keys[3]);

    if (sf::Keyboard::isKeyPressed(Input::sfml_keys[4]))
        HandleButton(Input::sfml_keys[4]);

    //if (sf::Keyboard::isKeyPressed(Input::sfml_keys[5]))
    //    HandleButton(Input::sfml_keys[5]);
    

    // Toggle debug key
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::F1))
    {
        if (!keys[sf::Keyboard::F1]) 
        {
            HandleButton(sf::Keyboard::F1);
        }
        keys[sf::Keyboard::F1] = true;
    }
    else keys[sf::Keyboard::F1] = false;

    // Toggle wireframe key
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::F2))
    {
        if (!keys[sf::Keyboard::F2])
        {
            HandleButton(sf::Keyboard::F2);
        }
        keys[sf::Keyboard::F2] = true;
    }
    else keys[sf::Keyboard::F2] = false;

    // Load level key
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::F3))
    {
        if (!keys[sf::Keyboard::F3])
        {
            HandleButton(sf::Keyboard::F3);
        }
        keys[sf::Keyboard::F3] = true;
    }
    else keys[sf::Keyboard::F3] = false;
}


void Keyboard::HandleButton(int key)
{
    m_key = key;
    //keys[m_key] = true;
    //std::cout << "Key pressed: " << m_key << " : " << keys[m_key] << std::endl;


    switch (m_key)
    {   // Escape[36]
    case 36:
    {
       
        break;
    }
    // W[22], S[18], A[0], D[3], SPACE[57], T[19] - audio
    case 22:
    {
        Event* keyboard_event = new Event(m_key, EventType::KeyPressed);
        EventHandler::AddEvent(keyboard_event);
        break;
    }
    case 18:
    {
        Event* keyboard_event = new Event(m_key, EventType::KeyPressed);
        EventHandler::AddEvent(keyboard_event);
        break;
    }
    case 0:
    {
        Event* keyboard_event = new Event(m_key, EventType::KeyPressed);
        EventHandler::AddEvent(keyboard_event);
        break;
    }
    case 3:
    {
        Event* keyboard_event = new Event(m_key, EventType::KeyPressed);
        EventHandler::AddEvent(keyboard_event);
        break;
    }
    case 57:
    {
        Event* keyboard_event = new Event(m_key, EventType::KeyPressed);
        EventHandler::AddEvent(keyboard_event);
        break;
    }
    //case 19:
    //{
    //    Event* keyboard_event = new Event(m_key, EventType::KeyPressed);
    //    EventHandler::AddEvent(keyboard_event);
    //    break;
    //}
    case 85: // F1[85] scene performance debug info
    {
        Event* play_debug_sound = new Event(1, EventType::PlaySound);
        EventHandler::AddEvent(play_debug_sound);

        Event* debug_info_event = new Event(EventType::ToggleDebugInfo);
        EventHandler::AddEvent(debug_info_event);
        break;
    }
    case 86: // F2[86] subsystem execution time debug info
    {
        Event* toggle_wireframe_event = new Event(EventType::Wireframe);
        EventHandler::AddEvent(toggle_wireframe_event);
        break;
    }
    case 87: // F3[87] load level
    {
        Event* load_level = new Event(EventType::LoadLevel);
        EventHandler::AddEvent(load_level);
        break;
    }
    default:
        std::cout << "Error: unregistered keyboard input " << m_key << '\n';
        break;
    }
}