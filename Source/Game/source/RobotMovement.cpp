#include "RobotMovement.h"
#include "CommonUtilities/CommonUtilities.h"
#ifdef _DEBUG
#include <tge/engine.h>
#include "tge/drawers/DebugDrawer.h"
#endif

#include "PollingStation.h"
#include <random> 
#include "Wall.h"


void RobotMovement::Init(const CommonUtilities::Vector2f& aPosition, const std::string& aTexturePath)
{
	GameObject::Init(aPosition, aTexturePath);
}
float RobotMovement::Random(float aMin, float aMax)
{
	static std::mt19937 myRandomGenerator;
	myRandomGenerator = std::mt19937(std::random_device()());
	std::uniform_real_distribution<float> randomDistribution(aMin, aMax);
	return randomDistribution(myRandomGenerator);
}

void RobotMovement::ApplyForce(const CommonUtilities::Vector2f& aForce)
{
	acceleration += aForce / mass;
}

void RobotMovement::GoToDestination(const CommonUtilities::Vector2f& aDestination, float aDeltaTime)
{
	UpdateBoxCollider();
	KeyBoardMovement(aDeltaTime);
	const auto& seekForce = Seek(aDestination, aDeltaTime);
	//const auto& bounderyAvoidanceForce = BounderyAvoidance(aDeltaTime);
	const auto& obstacleAvoidanceForce = ObstacleAvoidance(aDeltaTime);

	const auto& totalForce = seekForce  + obstacleAvoidanceForce;

	ApplyForce(totalForce);

	velocity += acceleration * aDeltaTime;
	velocity.Limit(maxSpeed);
	UpdateTransform(GetPosition() + velocity * aDeltaTime, std::atan2(velocity.y, velocity.x));
	acceleration = { 0,0 };
}

void RobotMovement::WanderAround(float aDeltaTime)
{
	UpdateBoxCollider();
	KeyBoardMovement(aDeltaTime);
	const auto& wanderForce = Wander(aDeltaTime);
	const auto& bounderyAvoidanceForce = BounderyAvoidance(aDeltaTime);
	const auto& obstacleAvoidanceForce = ObstacleAvoidance(aDeltaTime);

	const auto& totalForce = wanderForce + obstacleAvoidanceForce + bounderyAvoidanceForce * 2.f;

	ApplyForce(totalForce);

	velocity += acceleration * aDeltaTime;
	velocity.Limit(maxSpeed);
	UpdateTransform(GetPosition() + velocity * aDeltaTime, std::atan2(velocity.y, velocity.x));
	acceleration = { 0,0 };
}

void RobotMovement::KeyBoardMovement(float aDeltaTime)
{
	CommonUtilities::Vector2f position = GameObject::GetPosition();
	auto forward = GetForwardVector();

	//change the position of the car based on the input from the keyboard .. but if w is pressed the car should move forward direction
	float rotationSpeed = 5.0f;
	if (CommonUtilities::InputHandler::IsKeyPressed(Keys::W))
	{
		position += forward * maxSpeed * aDeltaTime;
	}
	if (CommonUtilities::InputHandler::IsKeyPressed(Keys::S))
	{
		position -= forward * maxSpeed * aDeltaTime;
	}

	GameObject::UpdateTransform(position, GetSprite().GetRotation());

}

void RobotMovement::UpdateBoxCollider()
{

	CommonUtilities::Vector2f position = GameObject::GetPosition();

	auto& debugDrawer = Tga::Engine::GetInstance()->GetDebugDrawer();

	CommonUtilities::AABB2Df boxCollider;

	float boxMinX = position.x - aabbWidth;
	float boxMinY = position.y - aabbHeight;
	float boxMaxX = position.x + aabbWidth;
	float boxMaxY = position.y + aabbHeight;

	boxCollider.InitWithMinAndMax({ boxMinX, boxMinY}, { boxMaxX,boxMaxY });


	float rayLength = 100.0f;
	CommonUtilities::Ray2D<float> ray;
	ray.InitWithOriginAndDirection({ position.x, position.y }, {GetForwardVector().x,GetForwardVector().y});
	auto collisionData = PollingStation::Get().CheckRayWallCollision(ray, rayLength);
	myIsCollidingWithWall = collisionData.myIsColliding;

	Tga::Color color = !myIsCollidingWithWall ? Tga::Color(1, 0, 0) : Tga::Color(0, 1, 0);
	PollingStation::Get().DebugAABB(boxCollider, color);

	//debugDrawer.DrawArrow(ray.GetOrigin(), ray.GetOrigin() + ray.GetDirection() * rayLength, Tga::Color(1, 1, 1));

}

float map(float value, float start1, float stop1, float start2, float stop2) {
	return start2 + ((value - start1) * (stop2 - start2)) / (stop1 - start1);
}



CommonUtilities::Vector2f RobotMovement::Seek(const CommonUtilities::Vector2f& aTarget, float aDeltaTime)
{
	const auto& position = GameObject::GetPosition();

	CommonUtilities::Vector2f desiredVelocity = aTarget - position;

	desiredVelocity.SetLength(maxSpeed);
	
	CommonUtilities::Vector2f steeringForce = desiredVelocity - velocity;
	steeringForce.Limit(maxForce);

	//ApplyForce(steeringForce);

	
	//debug
	//auto& debugDrawer = Tga::Engine::GetInstance()->GetDebugDrawer();
	////desired velocity
	//debugDrawer.DrawArrow(position, position + desiredVelocity, Tga::Color(1, 0, 0));
	////current velocity
	//debugDrawer.DrawArrow(position, position + velocity, Tga::Color(0, 1, 0));
	////steering force
	//debugDrawer.DrawArrow(position, position + steeringForce, Tga::Color(1, 1, 0));


	return steeringForce;
}

CommonUtilities::Vector2f RobotMovement::Wander(float aDeltaTime)
{
	const float wanderRadius = 50.0f;
	const float wanderDistance = 100.0f;
	const float change = 0.05f;
	static float wanderTheta = 0;

	wanderTheta += Random(-change, change);

	CommonUtilities::Vector2f circlePosition = velocity;
	circlePosition.Normalize();
	circlePosition *= wanderDistance;
	circlePosition += GameObject::GetPosition();

	float h = std::atan2(velocity.y, velocity.x);

	CommonUtilities::Vector2f circleOffset = { wanderRadius * std::cos(wanderTheta + h), wanderRadius * std::sin(wanderTheta + h) };

	CommonUtilities::Vector2f target = circlePosition + circleOffset;

	//auto& debugDrawer = Tga::Engine::GetInstance()->GetDebugDrawer();
	//debugDrawer.DrawCircle(circlePosition, wanderRadius, Tga::Color(1, 0, 0));
	//debugDrawer.DrawCircle(target, 5, Tga::Color(0, 1, 0));
	////draw from the circle center to the target
	//debugDrawer.DrawLine(circlePosition, target, Tga::Color(1, 1, 0));

	return this->Seek(target, aDeltaTime);
}

CommonUtilities::Vector2f RobotMovement::BounderyAvoidance(float aDeltaTime)
{
	CommonUtilities::Vector2f desiredVelocity = { 0,0 };
	auto position = GameObject::GetPosition();
	static const CommonUtilities::Vector2f boundery = { 1000, 700};
	if (position.x < 100)
	{
		desiredVelocity = { maxSpeed, velocity.y };
	}
	else if (position.x > boundery.x)
	{
		desiredVelocity = { -maxSpeed, velocity.y };
	}
	else if (position.y < 100)
	{
		desiredVelocity = { velocity.x, maxSpeed };
	}
	else if (position.y > boundery.y)
	{
		desiredVelocity = { velocity.x, -maxSpeed };
	}
		auto& debugDrawer = Tga::Engine::GetInstance()->GetDebugDrawer();

	if (!(desiredVelocity.x == 0 && desiredVelocity.y == 0))
	{
		desiredVelocity.Normalize();
		desiredVelocity *= maxSpeed;
		CommonUtilities::Vector2f steeringForce = desiredVelocity - velocity;
		steeringForce.Limit(maxForce);

		//debugDrawer.DrawArrow(position, position + desiredVelocity, Tga::Color(1, 0.5f, 0));
		//debugDrawer.DrawArrow(position, position + velocity, Tga::Color(0, 1, 0.5f));
		//debugDrawer.DrawArrow(position, position + steeringForce, Tga::Color(1, 1, 0.5f));

		return steeringForce;
	}
	//debugDrawer.DrawArrow(position, position + desiredVelocity, Tga::Color(1, 0.5f, 0));

	return desiredVelocity;
}

CommonUtilities::Vector2f RobotMovement::ObstacleAvoidance(float aDeltaTime)
{
	auto obsticales = PollingStation::Get().GetObstacles();
	CommonUtilities::Vector2f desiredVelocity = { 0,0 };
	auto position = GameObject::GetPosition();

	for (const auto& obsticale : obsticales)
	{
		auto obsticalePosition = obsticale->GetPosition();
		auto distance = (obsticalePosition - position).Length();
		if (distance < 100)
		{
			desiredVelocity = position - obsticalePosition;
			desiredVelocity.Normalize();
			desiredVelocity *= maxSpeed;
			break;
		}
	}
	auto& debugDrawer = Tga::Engine::GetInstance()->GetDebugDrawer();

	if (!(desiredVelocity.x == 0 && desiredVelocity.y == 0))
	{
		CommonUtilities::Vector2f steeringForce = desiredVelocity - velocity;
		steeringForce.Limit(maxForce);

		debugDrawer.DrawArrow(position, position + desiredVelocity, Tga::Color(1, 0.5f, 0));
		debugDrawer.DrawArrow(position, position + velocity, Tga::Color(0, 1, 0.5f));
		debugDrawer.DrawArrow(position, position + steeringForce, Tga::Color(1, 1, 0.5f));

		return steeringForce;
	}
	debugDrawer.DrawArrow(position, position + desiredVelocity, Tga::Color(1, 0.5f, 0));

	return desiredVelocity;
}





/*
//float jitterThisFrame = wanderJitter * aDeltaTime;

	//Tga::Vector2f randomDisplacement = { Random(-1.0f, 1.0f), Random(-1.0f, 1.0f)};
	//randomDisplacement.Normalize();
	//randomDisplacement *= wanderJitter * aDeltaTime;
	//wanderTarget += randomDisplacement;

	//wanderTarget.Normalize();
	//wanderTarget *= wanderRadius;

	//Tga::Vector2f forward = velocity;
	//if (forward.Length() == 0)
	//{
	//	forward = GetForwardVector();
	//}

	//forward.Normalize();


	//Tga::Vector2f circleCenter = forward * wanderDistance;
	//Tga::Vector2f targetLocal = circleCenter + wanderTarget;

	//Tga::Vector2f position = GameObject::GetPosition();
	//Tga::Vector2f targetWorld = position + targetLocal;

	//Tga::Vector2f steeringForce = targetWorld - position;
	//steeringForce.Normalize();
	//steeringForce *= maxForce;


	//const float collisionAvoidanceStrength = 500.0f;
	//if (myIsCollidingWithWall)
	//{
	//	// Apply a force away from the wall
	//	Tga::Vector2f avoidanceForce = myCollisionNormal;
	//	avoidanceForce.Normalize();
	//	avoidanceForce *= collisionAvoidanceStrength; // Define this strength as needed

	//	// Add the avoidance force to the steering force
	//	steeringForce += avoidanceForce;
	//}


	//velocity += steeringForce * aDeltaTime;

	//if (velocity.Length() > maxSpeed)
	//{
	//	velocity.Normalize();
	//	velocity *= maxSpeed;
	//}

	//Tga::Vector2f newPosition = position + velocity * aDeltaTime;

	//float newRotation = std::atan2(velocity.y, velocity.x);
*/