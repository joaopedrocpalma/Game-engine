#pragma once
#include <algorithm>
#include "GameObject.h"
#include "Subsystem.h"

class PhysicsSubsystem
{
public:
	// Public vectors
	std::vector<aabbox3df*> dynamicColliders;	// Check with statics and between each others
	std::vector<aabbox3df*> staticColliders;	// Don't check between each other

	// Constructor
	PhysicsSubsystem();

	// Functions
	std::vector<GameObject*> InitPhysics(lua_State* lua_level_file, GameObject** player);
	static vector3df AddForce(vector3df startPoint, vector3df direction, float mass);
	virtual void UpdateSubsystem(std::vector<GameObject*> objectList, float deltaTime);	
	virtual void CalculateCollision(GameObject* object);
	virtual void ResolveCollision(GameObject* object);
	virtual void CheckTrigger(GameObject* player);
	virtual void UnloadPhysics();	
};