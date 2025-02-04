#include "PollingStation.h"
#include "Wall.h"

#ifdef _DEBUG
#include <tge/engine.h>
#include "tge/drawers/DebugDrawer.h"
#endif

#include "RobotMovement.h"


void PollingStation::Init(std::vector<std::shared_ptr<Wall>> WallsColiders)
{
	myObstacles = WallsColiders;
}

void PollingStation::AddFirstRobot(std::shared_ptr<RobotMovement> aRobot)
{
	myFirstRobot = aRobot;
}

void PollingStation::AddSecondRobot(std::shared_ptr<RobotMovement> aRobot)
{
	mySecondRobot = aRobot;
}

void PollingStation::AddHealthPackPosition(const CommonUtilities::Vector2f& aPosition)
{
	myHealthPackPosition = aPosition;
}

void PollingStation::AddHealthPack2Position(const CommonUtilities::Vector2f& aPosition)
{
	myHealthPack2Position = aPosition;

}

//CollisionData PollingStation::CheckAABBWallCollision(const AABB3D<float>& anAABB)
//{
//	CollisionData collisionData;
//	collisionData.myIsColliding = false;
//
//	for (const auto& wall : myWallsAabb)
//	{
//		if (CommonUtilities::IntersectionAABBAABB<float>(wall->GetAABB(), anAABB))
//		{
//			collisionData.myIsColliding = true;
//
//			const auto& wallMax = wall->GetAABB().GetMax();
//			const auto& wallMin = wall->GetAABB().GetMin();
//			CommonUtilities::Vector2f wallCenter = { (wallMax.x + wallMin.x) * 0.5f, (wallMax.y + wallMin.y) * 0.5f};
//
//			const auto& aabbMax = anAABB.GetMax();
//			const auto& aabbMin = anAABB.GetMin();
//			CommonUtilities::Vector2f aabbCenter = { (aabbMax.x + aabbMin.x) * 0.5f, (aabbMax.y + aabbMin.y) * 0.5f };
//
//			Tga::Vector2f direction = aabbCenter - wallCenter;
//			direction.Normalize();
//			collisionData.myCollisionNormal = direction;
//			return collisionData;
//		}
//	}
//	return collisionData;
//}

CollisionData PollingStation::CheckRayWallCollision(const CommonUtilities::Ray2D<float>& aRay, float aRayLength)
{
	CollisionData collisionData;
	collisionData.myIsColliding = false;

	for (const auto& wall : myObstacles)
	{
		if (CommonUtilities::IntersectionRayAABB2D<float>(aRay, wall->GetAABB(), aRayLength))
		{
			collisionData.myIsColliding = true;
			//collisionData.myCollisionNormal = wall->GetAABB().GetNormal();
			return collisionData;
		}
	}
	return collisionData;
}

void PollingStation::DebugAABB(const AABB2D<float>& anAABB, const Tga::Color& aColor)
{
	auto& debugDrawer = Tga::Engine::GetInstance()->GetDebugDrawer();
	debugDrawer.DrawLine(CommonUtilities::Vector2f(anAABB.GetMin().x, anAABB.GetMin().y), CommonUtilities::Vector2f(anAABB.GetMax().x, anAABB.GetMin().y), aColor);
	debugDrawer.DrawLine(CommonUtilities::Vector2f(anAABB.GetMax().x, anAABB.GetMin().y), CommonUtilities::Vector2f(anAABB.GetMax().x, anAABB.GetMax().y), aColor);
	debugDrawer.DrawLine(CommonUtilities::Vector2f(anAABB.GetMax().x, anAABB.GetMax().y), CommonUtilities::Vector2f(anAABB.GetMin().x, anAABB.GetMax().y), aColor);
	debugDrawer.DrawLine(CommonUtilities::Vector2f(anAABB.GetMin().x, anAABB.GetMax().y), CommonUtilities::Vector2f(anAABB.GetMin().x, anAABB.GetMin().y), aColor);
}

void PollingStation::DebugCircle(const CommonUtilities::Vector2f& aPosition, float aRadius, const Tga::Color& aColor)
{
	auto& debugDrawer = Tga::Engine::GetInstance()->GetDebugDrawer();
	debugDrawer.DrawCircle(aPosition, aRadius, aColor);
}
