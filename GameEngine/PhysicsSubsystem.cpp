#include "PhysicsSubsystem.h"
#include "DataSubsystem.h"

PhysicsSubsystem::PhysicsSubsystem()
{

}

void PhysicsSubsystem::UpdateSubsystem(std::vector<GameObject*> objectList, float deltaTime)
{
	for (int i = 0; i < objectList.size(); i++) 
	{
		CalculateCollision(objectList[i]);	// Calculate all collisions

		if ((*objectList[i]).tag == "player")	// Checks if the player has hit the next level/end game triggers
		{
			CheckTrigger(objectList[i]);
		}		

		objectList[i]->Update(deltaTime);	// Updates physics for objects in scene	
	}
}

// Receives all the objects in the Lua file and unpacks them into different lists
std::vector<GameObject*> PhysicsSubsystem::InitPhysics(lua_State* lua_level_file, GameObject** player)
{
	std::vector<std::string> element_list;	// To save positions, rotations and other info about objects
	std::vector<GameObject*> objectsList;	// To save all objects as game objects

	vector3df position;
	vector3df rotation;
	vector3df scale;

	float mass;
	std::string collShape;

	element_list = DataSubsystem::GetElements("gameObjectList", lua_level_file);
	lua_r object_ref = luabridge::getGlobal(lua_level_file, "gameObjectList");

	// Iterate through the list of elements
	for (int i = 0; i < element_list.size(); ++i) {
		lua_r entityCheck = object_ref[element_list.at(i)];

		// Passing position, scale, rotation, mass and collider shape into variables
		position = vector3df(entityCheck["pos_x"].cast<float>(), entityCheck["pos_y"].cast<float>(), entityCheck["pos_z"].cast<float>());
		rotation = vector3df(entityCheck["rot_x"].cast<float>(), entityCheck["rot_y"].cast<float>(), entityCheck["rot_z"].cast<float>());
		scale = vector3df(entityCheck["scl_x"].cast<float>(), entityCheck["scl_y"].cast<float>(), entityCheck["scl_z"].cast<float>());
		mass = entityCheck["mass"].cast<float>();
		collShape = entityCheck["coll_shape"].cast<std::string>();		

		// Using aabb's I am using the constructor to define the size of each game object collision boxes, 
		// with their respective positions and their scale ir order to get their corners
		aabbox3df *boudingBox = new aabbox3df(position.X - scale.X, position.Y - scale.Y, position.Z - scale.Z, position.X + scale.X, position.Y + scale.Y, position.Z + scale.Z);

		if ((std::string)element_list.at(i) == "player")	// If the tag found in the Lua file is player, save it under player in the game objects list
		{
			GameObject* game_object = new GameObject(position, rotation, scale, mass, i, collShape, "player", &boudingBox, false, true);
			*player = game_object;
			dynamicColliders.push_back(boudingBox);
			objectsList.push_back(game_object);
			
		}
		else	// for everything else, just pass it normally
		{
			GameObject* game_object = new GameObject(position, rotation, scale, mass, i, collShape, "terrain", &boudingBox, true, false);
			staticColliders.push_back(boudingBox);
			objectsList.push_back(game_object);
		}		
	}
	return objectsList;
}

// Clear the memory
void PhysicsSubsystem::UnloadPhysics()
{
	// If I try to clear these vectors the game crashes
	for (int i = 0; i < dynamicColliders.size(); i++)
	{
		//delete &dynamicColliders[i];
		//dynamicColliders.erase(dynamicColliders.begin() + i);
	}

	for (int i = 0; i < staticColliders.size(); i++)
	{
		//delete &staticColliders[i];
		//staticColliders.erase(dynamicColliders.begin() + i);
	}
}

// Adds a force vector the and object (for the player)
vector3df PhysicsSubsystem::AddForce(vector3df startPoint, vector3df force, float mass)
{
	vector3df finalVector;

	finalVector = vector3df(force.X / mass, force.Y / mass, force.Z / mass);	// Calculating acceleration

	return finalVector;
}

// Checks if any objects are colliding
void PhysicsSubsystem::CalculateCollision(GameObject* object)
{
	if (!object->isColliderStatic) // Checks collisions for the player
	{
		for (int i = 0; i < staticColliders.size(); i++)	// Check collision against static objects
		{
			if (object->bBox->intersectsWithBox(*staticColliders[i]))	// checks object collision with any static objects in the map
			{
				ResolveCollision(object);
			}
		}
		for (int i = 0; i < dynamicColliders.size(); i++)
		{
			if (*dynamicColliders[i] == *object->bBox)	// If it is its own collider, continue
			{
				continue;
			}
			if (object->bBox->intersectsWithBox(*dynamicColliders[i]))	// If its any other dynamic collider
			{
				ResolveCollision(object);
			}
		}
	}
}

// Stops object from clipping
void PhysicsSubsystem::ResolveCollision(GameObject* object)
{
	// Stop object from going through other objects by removing its own velocity
	object->position.X -= object->velocity.X;
	object->position.Z -= object->velocity.Z;
	object->acceleration.X = 0;
	object->acceleration.Z = 0;
	object->velocity.X = 0;
	object->velocity.Z = 0;
	if (object->isGrounded == false)
	{
		object->position.Y -= object->velocity.Y;
	}
	
}

// Check if the player is colliding with any platform setting the jump variable to either grounded or not
void PhysicsSubsystem::CheckTrigger(GameObject* player)
{
	bool grounded = false;

	for (int i = 0; i < staticColliders.size(); i++)
	{
		if (player->groundCollider->intersectsWithBox(*staticColliders[i]))	// checks player collision with any static objects in the map
		{
			grounded = true;
			break;
		}
		if (player->position.Y <= -100) // In case player falls off  the platforms
		{
			player->position = vector3df(0.0f, 5.0f, 0.0f);	// reset position
		}
	}
	player->SetGrounded(grounded);
}