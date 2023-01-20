#pragma once
#include <vector>
#include <aabbox3D.h>
#include <string>
#include <irrlicht.h>
#include <iostream>

using namespace irr;
using namespace core;

class GameObject
{
public:
	// --------ALL VARIABLES----------
	// Physics variables
	int colliderID = 0;
	float mass = 2.0f;
	float maxVelocity = 2.0f;

	bool isColliderStatic;
	bool gravityEnabled;
	bool isGrounded;
	bool jumpTrigger;

	// Conditional variables
	bool changeLevel;
	bool endGame;

	vector3df position;
	vector3df rotation;
	vector3df scale;
	vector3df acceleration;
	vector3df velocity;
	vector3df friction = vector3df(2.0f, 1.0f, 2.0f);	

	std::string tag = "";
	std::string collShape;

	irr::scene::IAnimatedMeshSceneNode* Mesh;

	aabbox3df* bBox;
	aabbox3df* groundCollider;

	// Constructors / Destructors
	GameObject(); // Default constructor	(Default position (0, 0, 0) and ID = 0)
	GameObject(int colID, std::string tag);
	GameObject(vector3df position, vector3df rotation, vector3df scale, float mass, int colID, std::string collShape, std::string tag, aabbox3df** bBox, bool colliderStatic,bool gravityEnabled);
	~GameObject();	// Default Destructor


	// Functions
	virtual void Move(vector3df force);
	virtual void Jump(vector3df force);
	virtual void InitMesh(irr::scene::IAnimatedMeshSceneNode** mesh);
	virtual void Update(float deltaTime);
	virtual void CalculatePos(float deltaTime);
	virtual void CalculateRot();	
	virtual void CheckLevelTrigger();
	void SetGrounded(bool grounded);
};
