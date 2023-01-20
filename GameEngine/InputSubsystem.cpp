#include "InputSubsystem.h"
#include "Keyboard.h"
#include "Mouse.h"


Keyboard keyboard;
Mouse mouse;

typedef luabridge::LuaRef lua_r;
std::vector<sf::Keyboard::Key> Input::sfml_keys;
float Input::deadzone;

void Input::InitInput(lua_State* lua_file)
{
    lua_control_file = lua_file;

    // Set graphics_lua to be the "graphics" block of the file
    lua_r keyBinds = luabridge::getGlobal(lua_control_file, "keyBinds");
    lua_r k = keyBinds["keyboard"];
    lua_r forward = k["forward"];
    lua_r left = k["left"];
    lua_r backward = k["backward"];
    lua_r right = k["right"];
    lua_r jump = k["jump"];
    lua_r sound = k["sound"];
    lua_r c = keyBinds["controller"];
    lua_r dz = c["deadzone"];



    if (forward.cast<char>() == 'w') 
        sfml_keys.push_back(sf::Keyboard::Key::W); // Assing the first member on our map to given key
    if (backward.cast<char>() == 's')
        sfml_keys.push_back(sf::Keyboard::Key::S);
    if (left.cast<char>() == 'a')
        sfml_keys.push_back(sf::Keyboard::Key::A);
    if (right.cast<char>() == 'd')
        sfml_keys.push_back(sf::Keyboard::Key::D);
    if (jump.cast<char>() == 'j')
        sfml_keys.push_back(sf::Keyboard::Key::Space);
    if (jump.cast<char>() == 't')
        sfml_keys.push_back(sf::Keyboard::Key::T);

    deadzone = dz.cast<float>();
}

void Input::UpdateSubsystem()
{
    old_time = current_time;
    current_time = Clock::now();

    keyboard.GetInput();
    mouse.GetInput();

    HandleEvent();

    delta_time = current_time - old_time;
    dt_f = delta_time.count() * 0.000001f;
}

void Input::HandleEvent()
{
    for (Event* event : EventHandler::GetEvents()) {
        switch (event->GetEventType())
        {
        case EventType::KeyPressed:
        {
            switch (event->GetKeyPressed())
            {
                case 22:    // W
                {
                    vector3df force = vector3df(0.0f, 0.0f, 1.0f);
                    Engine::GetPlayer()->Move(force);
                    break;
                }
                case 18:    // S
                {
                    vector3df force = vector3df(0.0f, 0.0f, -1.0f);
                    Engine::GetPlayer()->Move(force);
                    break;
                }
                case 0: // A
                {
                    vector3df force = vector3df(-1.0f, 0.0f, 0.0f);
                    Engine::GetPlayer()->Move(force);
                    break;
                }
                case 3: // D
                {
                    vector3df force = vector3df(1.0f, 0.0f, 0.0f);
                    Engine::GetPlayer()->Move(force);
                    break;
                }
                case 57: // Space
                {
                    vector3df force = vector3df(0.0f, 50.0f, 0.0f);
                    Engine::GetPlayer()->Jump(force);
                    break;
                }
                //case 19: // T - play audio
                //{
                //    //Engine::GetAudio()->PlayAudio();
                //    std::cout << "Audio playing\n";
                //    break;
                //}
                default:
                    break;
            }
        }
        default:
            break;
        }
    }    
}