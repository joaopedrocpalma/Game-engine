#include "GraphicsSubsystem.h"
#include "DataSubsystem.h"
#include "aabbox3d.h"


typedef luabridge::LuaRef lua_r;

GUISubsystem irrGUI;

int GraphicsSubsystem::InitGraphics(lua_State* lua_file)
{
#pragma region Lua

	lua_r g = luabridge::getGlobal(lua_file, "graphics");
	lua_r title = g["title"];
	lua_r width = g["width"];
	lua_r height = g["height"];
	lua_r fullscreen = g["fullscreen"];
	lua_r stencil_buffer = g["stencil_buffer"];
	lua_r vsync = g["vsync"];

	// Convert C++ string to wstring
	std::string temp_string = title.cast<std::string>();

	m_title = std::wstring(temp_string.begin(), temp_string.end());
	//const wchar_t* widecstr = widestr.c_str();

#pragma endregion

	device = createDevice(EDT_OPENGL, dimension2d<u32>(width, height), 16, fullscreen, stencil_buffer, vsync, 0); // shadow buffer disabled
	
	if (!device) {
		return 1;
		std::cout << "Error: failed to initialize device\n";
	}

	driver = device->getVideoDriver();
	scn_mngr = device->getSceneManager();
	irrGUI.InitGUI(device);
	
	// A camera with first person shooter-ish behaviour 
	camera = scn_mngr->addCameraSceneNodeFPS(0, 100.f, 0);

	return 0;
}

int GraphicsSubsystem::InitModels(lua_State* lua_file, std::vector<GameObject*> objectList)
{
	//rotate_circle = scn_mngr->createFlyCircleAnimator(vector3df(0, 0, 0), 1.0f);	// Creates a flying circle animation
	//spiny_anim = scn_mngr->createRotationAnimator(vector3df(0, 0.2, 0));	// Makes the map rotate

	element_list = DataSubsystem::GetElements("gameObjectList", lua_file);
	lua_r object_ref = luabridge::getGlobal(lua_file, "gameObjectList");

	// Iterate through the list of elements
	for (int i = 0; i < element_list.size(); ++i) {
		lua_r entityCheck = object_ref[element_list.at(i)];

		//if ((std::string)element_list.at(i) == "player")
			//std::cout << (std::string)element_list.at(i) << '\n';

		std::string model_dir = "data/assets/models/" + (entityCheck["model"].cast<std::string>()) + ".obj";
		//std::cout << model_dir << '\n';

		textures.push_back("data/assets/textures/" + entityCheck["texture"].cast<std::string>());
		//std::cout << textures[i] << '\n';

		IAnimatedMeshSceneNode* model = scn_mngr->addAnimatedMeshSceneNode(scn_mngr->getMesh(model_dir.c_str()));
		Models.push_back(model);

		//GameObject* game_object = new GameObject(pos, scl, rot, ObjType::Dynamic);
		//GameObjects.push_back(game_object);

		//if ((std::string)element_list.at(i) == "object5") {
		//	Models[i]->addAnimator(spiny_anim);
			//Models[i]->setFrameLoop(0, 60);
			//Models[i]->setAnimationSpeed(10);
		//}

		Models[i]->setMaterialFlag(EMF_LIGHTING, false); // Set false to affect materials by lights (must have a light in scene to see effect)
		Models[i]->setMaterialTexture(0, driver->getTexture(textures[i].c_str()));

		objectList[i]->InitMesh(&Models[i]);	// Attributing mesh/model to game object
	}	

	std::cout << "Loaded [" << Models.size() << "] models.\n";
	//std::cout << "Created [" << GameObjects.size() <<"] game objects.\n";

	return 0;
}

GraphicsSubsystem::~GraphicsSubsystem()
{
	//delete window;
	//device->drop();
	//scn_mngr->clear();
	Models.clear();
	textures.clear();
	element_list.clear();	
}

void GraphicsSubsystem::UnloadModels()
{
	// Clear all the vectors, so we can refresh the scene when we load the new level
	for (int i = 0; i < Models.size(); i++) {
		scn_mngr->addToDeletionQueue(Models[i]);
		//delete Models[i];
		Models.erase(Models.begin() + i);
	}
	for (int i = 0; i < textures.size(); i++) {
		scn_mngr->addToDeletionQueue(Models[i]);
		//delete textures[i];
		textures.erase(textures.begin() + i);
	}
	for (int i = 0; i < element_list.size(); i++) {
		scn_mngr->addToDeletionQueue(Models[i]);
		//delete element_list[i];
		element_list.erase(element_list.begin() + i);
	}
	
	Models.clear();
	textures.clear();
	element_list.clear();
}

void GraphicsSubsystem::UpdateSubsystem()
{
	int last_fps = -1;
	// Get the time since last frame, which is used to to perform framerate independent movement
	u32 then = device->getTimer()->getTime();

	if (device->run()) {
		if (device->isWindowActive()) {
			const u32 now = device->getTimer()->getTime();
			m_delta_time = (f32)(now - then) / 1000.0f; // maybe pass to to physics as well, or have it located centrally in engine class
			then = now;

			device->setWindowCaption(m_title.c_str());

			// Anything can be draw in between beginScene and endScene calls
			driver->beginScene(true, true, SColor(255, 100, 101, 140)); // clear the color and depth buffer
			
			scn_mngr->drawAll();
			
			// Using IGUI to add a textbox onto the screen
			wchar_t myText[] = L"Score: ";

			irrGUI.AddStaticText(myText);
			irrGUI.UpdateSubsystem();

			// Tell the driver that a draw iteration has completed and prepare prepare for the next one
			driver->endScene();

			// Apply camera position, look target varaibles
			camera_pos = camera->getAbsolutePosition();
			target = camera->getTarget();
			look_dir = (target - camera_pos).normalize();
			camera_rot = camera->getRotation();

			// The right vector is perpendicular to camera direction and the up vector's
			right = look_dir.crossProduct(up).normalize();

			
			// The camera look direction is received by the physics subsystem to apply forces based based on the direction the camera is looking at
			Event* update_cam_look_dir = new Event(look_dir, EventType::UpdateCameraLookDir);
			EventHandler::AddEvent(update_cam_look_dir);

			Event* update_cam_right = new Event(right, EventType::UpdateCameraRight);
			EventHandler::AddEvent(update_cam_right);
		}
		else {
			// Prevents the loop from using up all the cpu cycles while the window is not active
			device->yield();
		}
	}
	
	delta_time = current_time - old_time;
	dt_f = delta_time.count() * 0.000001f; // delta_time.count returns nanoseconds, multiply by 0.000001f to get miliseconds

	Event* delta_time = new Event(dt_f, EventType::UpdateDeltaTime);
	EventHandler::AddEvent(delta_time);
	HandleEvent();
}

void GraphicsSubsystem::HandleEvent()
{
	for (Event* event : EventHandler::GetEvents()) {
		switch (event->GetEventType())
		{
		case EventType::Wireframe:
			std::cout << "[Graphics] Event: " << static_cast<int>(event->GetEventType()) << " (Toggle wireframe mode) handled\n";
			toggle_wireframe = !toggle_wireframe;

			for (int i = 0; i < Models.size(); ++i) {
				// Toggle wireframe mode for all objects in the scene
				if (toggle_wireframe)
					Models[i]->setMaterialFlag(EMF_WIREFRAME, true);
				else
					Models[i]->setMaterialFlag(EMF_WIREFRAME, false);
			}
			delete event;

			break;
			// Update each models transform properties by getting position, rotation, and scale values from the physics subsystem.
		case EventType::UpdateTransform:
			//std::cout << "[Graphics] Event Type: " << static_cast<int>(event->GetEventType()) << " (Update transform) handled\n";
			delete event;
			break;

		case EventType::UpdateScale:
			delete event;
			break;
		default:
			break;
		}
	}
}

irr::scene::IAnimatedMeshSceneNode* GraphicsSubsystem::GetModel(int index) 
{
	return Models[index];
}

void GraphicsSubsystem::UpdateCameraPos(GameObject** player) 
{
	// Update camera position to follow the player
	camera->setPosition((**player).position - vector3df(0.0f, -5.0f, 5.0f));
	camera->setTarget((**player).position);
	camera->updateAbsolutePosition();
}