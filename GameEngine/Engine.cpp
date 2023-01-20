#include "Engine.h"
#include "EventHandler.h"
#include "DataSubsystem.h"

Input input;
GraphicsSubsystem graphics; 
GameObject* gameObject;
static GameObject* player;
std::vector<GameObject*> objectList;
PhysicsSubsystem physics;
//AudioSubsystem audio;
//AudioSubsystem* getAudio;
//ProfilingSubsystem profiling;
ScoreSubsystem score;

bool Engine::running;

Engine::Engine()
{
    graphics.InitGraphics(DataSubsystem::GetLuaFile("data/config/window.lua"));

    LoadLevel(DataSubsystem::GetLuaFile("data/config/level01.lua"));
      
    // Initialise input subsystem to respond to mouse, keyboard, and xbox controller input
    input.InitInput(DataSubsystem::GetLuaFile("data/config/controls.lua"));

    // Start counting the time in seconds which will be used for the highscore
    score.InitScore("data/Highscore.html");

    // Initialise the audio subsystem to play sounds on event
    //audio.InitAudio(DataSubsystem::GetLuaFile("data/config/audio.lua"));
    //audio.InitAudio();

    Update();
}

Engine::~Engine()
{
    for (GameObject* object : objectList) {
        delete object;
    }
}

void Engine::Update()
{    
    while (running) {
        input.UpdateSubsystem();
        physics.UpdateSubsystem(objectList, graphics.GetDeltaTime());        
        graphics.UpdateSubsystem();
        //profiling.UpdateSubsystem();
        score.UpdateSubsystem();
        //audio.UpdateSubsystem();
        graphics.UpdateCameraPos(&player);
        ChangeLevel();  // Check if the player has finished level 1
        HandleEvents(); // Engine can handle its own events
        EventHandler::ClearEvents();
    }
    score.SaveScore("data/Highscore.html", graphics.GetDeltaTime()); // Save current score when everything else is done
    EventHandler::ClearEvents();    
}

// Before loading another level, the update loop should not be running!
void Engine::LoadLevel(lua_State* lua_level_file) // make load level take in a lua file for physics graphics level data
{
    // Reuse the same gameobjects.lua to initialise physics object properties such as positions, scale/radius, mass, etc.
    objectList = physics.InitPhysics(lua_level_file, &player);

    // Initialise model properties like position, scale, rotation, texture, etc.
    graphics.InitModels(lua_level_file, objectList);

    running = true; //  Tell the engine update loop that we want to update the subsystems
}

void Engine::HandleEvents() // Could handle events take an event pointer and handle only that specific event instead of going from the entire event queue?
{
    for (Event* event : EventHandler::GetEvents()) {
        switch (event->GetEventType())
        {
        case EventType::Quit:
            running = false;
            delete event;

            break;
        case EventType::LoadLevel:
            std::cout << "[Engine] Event load level received\n";
            physics.UnloadPhysics();
            graphics.UnloadModels();
            running = false;
            LoadLevel(DataSubsystem::GetLuaFile("data/config/level02.lua"));
            delete event;

            break;
        default:
            break;
        }
    }
}

GameObject* Engine::GetPlayer()
{
    return player;
}

// Attempted inluding audio, it's complaining about linking problems
//AudioSubsystem* Engine::GetAudio()
//{
//    return getAudio;
//}

void Engine::ChangeLevel()
{
    if (player->changeLevel)   // If the player reached the end platform loads level 2
    {
        player->changeLevel = false;
        Event* level_event = new Event(EventType::LoadLevel);
        EventHandler::AddEvent(level_event);        
    }

    if (player->endGame)   // If the player reached the end platform of level 2, finishes the game
    {
        Event* level_event = new Event(EventType::Quit);
        EventHandler::AddEvent(level_event);
    }
}