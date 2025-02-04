#pragma once
#include "GameObject.h"
#include "CommonUtilities/Vector.hpp"

//TODO: 
// the car should have 3 rays in front and left and right ... 
// if the front ray hits a wall the car should turn left or right depending on which ray is farthest from the wall

class RobotMovement : public GameObject
{
protected:
	RobotMovement() = default;
	virtual ~RobotMovement() {};

	void Init(const CommonUtilities::Vector2f& aPosition, const std::string& aTexturePath);
	void GoToDestination(const CommonUtilities::Vector2f& aDestination, float aDeltaTime);
	void WanderAround(float aDeltaTime);
	void SetMaxSpeed(float aSpeed) { maxSpeed = aSpeed; }
private:
	void KeyBoardMovement(float aDeltaTime);
	void UpdateBoxCollider();
	CommonUtilities::Vector2f Seek(const CommonUtilities::Vector2f& aTarget, float aDeltaTime);
	CommonUtilities::Vector2f Wander(float aDeltaTime);
	CommonUtilities::Vector2f BounderyAvoidance(float aDeltaTime);
	CommonUtilities::Vector2f ObstacleAvoidance(float aDeltaTime);
	float Random(float aMin, float aMax);
	void ApplyForce(const CommonUtilities::Vector2f& aForce);
	bool myIsCollidingWithWall = false;
	//float speed = 150.0f;
	float aabbWidth = 50.0f;
	float aabbHeight = 50.0f;



	CommonUtilities::Vector2f velocity;
	CommonUtilities::Vector2f acceleration;

	//this is used so that the desired velocity is not very high ... to limit the desired velocity to have the max speed as the length of the vector
	float maxSpeed = 200.0f;

	//this is used to limit the force of the steering velocity
	float maxForce =200.0f;
	//mass
	float mass = 1.0f;




};


//in steering behavior you can do you own behavior .. only by adding a new force to the car .. like wander + a force that make the car avoid the walls

