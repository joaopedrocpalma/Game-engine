#include "GameObject.h"

// Constructors
GameObject::GameObject()
{
	this->position = { 0, 0, 0 };
	this->rotation = { 0, 0, 0 };
	this->scale = { 0, 0 , 0 };
	this->tag = "terrain";
}

GameObject::GameObject(int colID, std::string tag)
{
	this->position = { 0, 0, 0 };
	this->rotation = { 0, 0, 0 };
	this->scale = { 0, 0 , 0 };
	this->colliderID = colID;
	this->tag = tag;
}

GameObject::GameObject(vector3df position, vector3df rotation, vector3df scale, float mass, int colID, std::string collShape, std::string tag, aabbox3df** bBox, bool colliderStatic,bool gravityEnabled)
{
	this->position = vector3df(position.X, position.Y, position.Z);
	this->rotation = vector3df(rotation.X, rotation.Y, rotation.Z);
	this->scale = scale;
	this->mass = mass;
	this->colliderID = colID;
	this->collShape = collShape;
	this->tag = tag;
	this->bBox = *bBox;
	this->gravityEnabled = gravityEnabled;
	this->velocity = vector3df(0);
	this->acceleration = vector3df(0);
	this->jumpTrigger = true;
	isColliderStatic = colliderStatic;
	if (tag == "player")	// If the game object is the player then create a ground collider for jump checks
	{
		groundCollider = new aabbox3df(this->bBox->MinEdge.X + 0.5f, this->bBox->MinEdge.Y - 0.5f, this->bBox->MinEdge.Z + 0.5f,
									this->bBox->MaxEdge.X - 0.5f, this->bBox->MaxEdge.Y - (2 * scale.Y) - 0.001f, this->bBox->MaxEdge.Z - 0.5f);
	}	
}

// Destructor
GameObject::~GameObject() 
{
	delete Mesh;
	delete bBox;
	delete groundCollider;
}

void GameObject::Move(vector3df force)
{
	// Pass forward vector and multiply by acceleration to make player move towards camera position
	acceleration += vector3df(force.X / mass, 0, force.Z / mass);
	//std::cout << "X: " << position.X << "Z: " << position.Z << "\n";
}

void GameObject::Jump(vector3df force)
{
	if (isGrounded && jumpTrigger)
	{
		acceleration.Y += force.Y / mass;
		jumpTrigger = false;
	}
}

void GameObject::InitMesh(irr::scene::IAnimatedMeshSceneNode** mesh)
{
	// Set all the respective game objects position, rotation and scale for meshes in each game object
	this->Mesh = *mesh;
	this->Mesh->setPosition(position);
	this->Mesh->setRotation(rotation);
	this->Mesh->setScale(scale);
}

void GameObject::Update(float deltaTime)
{
	if (gravityEnabled && isGrounded == false)	// Only applies gravity if is not grounded
	{
		// acceleration = velocity / gravity
		acceleration.Y = -10.0f / 100;
	}

	// Update player things
	if (this->tag == "player")
	{
		// First calculate physics
		CalculatePos(deltaTime);
		CalculateRot();

		// Then apply visuals
		Mesh->setPosition(position);
		Mesh->setRotation(rotation);
		Mesh->setScale(scale);
		Mesh->updateAbsolutePosition();

		// Setting bounding box position
		bBox->setPosition(position, scale);		
		groundCollider->setGroundCollider(position, scale);

		CheckLevelTrigger();
	}	
}

void GameObject::CalculatePos(float deltaTime)	// Calculate velocity and apply position
{
	// Deaccelerate the object
	if (acceleration.X == 0 && acceleration.Z == 0)
	{
		velocity /= friction;	// Reduce movement over time
		if (velocity.X < 0.001 && velocity.X > -0.001)	// Stop deacceleration for all coordinates if their values are these
		{
			velocity.X = 0;
		}
		if (velocity.Z < 0.001 && velocity.Z > -0.001)
		{
			velocity.Z = 0;
		}
		velocity.Y += acceleration.Y * deltaTime;	// Makes you fall faster over time
	}
	else	// Accelerate object
	{
		// v = (a*t) + v0
		velocity = (acceleration * deltaTime) + velocity;
		if (velocity.X >= maxVelocity)	// So that the player does not exceed speed of light
		{
			velocity.X = maxVelocity;
		}
		else if (velocity.X <= -maxVelocity)	
		{
			velocity.X = -maxVelocity;
		}
		if (velocity.Z >= maxVelocity)
		{
			velocity.Z = maxVelocity;
		}
		else if (velocity.Z <= -maxVelocity) 
		{
			velocity.Z = -maxVelocity;
		}
	}

	// Reset acceleration to stop giving the object momemtum
	acceleration = vector3df(0.0f, acceleration.Y, 0.0f);

	// pos = pos0 + (v*t) + (1/2*a*t^2 OR
	// dist = v/t <=>
	// <=> pos - pos0 = v/t <=>
	// <=> pos = pos0 + v/t 
	position = position + velocity;	// Update position
}

void GameObject::CalculateRot()	// Apply rotations
{
	if (velocity.X > 0)	// Facing right
	{
		rotation = vector3df(0.0f, 90.0f, 0.0f);
		Mesh->setRotation(vector3df(0.0f, 90.0f, 0.0f));
	}
	else if (velocity.X < 0)	// Facing left
	{
		rotation = vector3df(0.0f, -90.0f, 0.0f);
		Mesh->setRotation(vector3df(0.0f, -90.0f, 0.0f));
	}
	else if (velocity.Z > 0)	// Facing forward
	{
		rotation = vector3df(0.0f, 0.0f, 0.0f);
		Mesh->setRotation(vector3df(0.0f, 0.0f, 0.0f));
	}
	else if (velocity.Z < 0)	// Facing backwards
	{
		rotation = vector3df(0.0f, 180.0f, 0.0f);
		Mesh->setRotation(vector3df(0.0f, 180.0f, 0.0f));
	}
}

void GameObject::SetGrounded(bool grounded)
{
	if (!isGrounded && grounded)	// When you are no longer out of the ground
	{
		jumpTrigger = true;
	}
	isGrounded = grounded;
	if (isGrounded && velocity.Y < 0)	// stop gravity if its grounded and not jumping
	{
		acceleration.Y = 0;
		velocity.Y = 0;
	}
}

// Check if the player has reached the end platform of the level
void GameObject::CheckLevelTrigger()
{
	if (this->tag == "player") {	// When player reaches these coordinates it changes to the next level
		if (position.X >= -8.0f && position.X <= 8.0f && position.Y >= -15.0f && position.Y <= -14.0f && position.Z >= 140.0f)
		{
			changeLevel = true;
		}

		// When player reaches these coordinates it ends the game and saves the score
		if (position.X >= 161 && position.X <= 245.0f && position.Y >= -54.0f && position.Y <= -53.0f && position.Z >= 160.0f)
		{
			endGame = true;
		}
	}
}
