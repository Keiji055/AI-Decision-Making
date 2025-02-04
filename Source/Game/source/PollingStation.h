#pragma once
#include "tge\math\Vector.h"
#include "tge/math/color.h"
#include <vector>
#include <random>
#include "CommonUtilities/CommonUtilities.h"

class Wall;
class RobotMovement;
//using CommonUtilities::AABB3D<float> as AABB3D;
using namespace CommonUtilities;

struct CollisionData
{
	bool myIsColliding = false;
	Tga::Vector2f myCollisionNormal;
};

class PollingStation
{
public:
	static PollingStation & Get()
	{
		static PollingStation instance;
		return instance;
	}
	void Init(std::vector<std::shared_ptr<Wall>> WallsColiders);
	void AddFirstRobot(std::shared_ptr<RobotMovement> aRobot);
	void AddSecondRobot(std::shared_ptr<RobotMovement> aRobot);
	void AddHealthPackPosition(const CommonUtilities::Vector2f& aPosition);
	void AddHealthPack2Position(const CommonUtilities::Vector2f& aPosition);

	std::shared_ptr<RobotMovement> GetStateStackRobot()
	{
		return myFirstRobot;
	}

	std::shared_ptr<RobotMovement> GetDecisionTreeRobot()
	{
		return mySecondRobot;
	}

	CommonUtilities::Vector2f GetHealthPackPosition()
	{
		return myHealthPackPosition;
	}

	CommonUtilities::Vector2f GetHealthPack2Position()
	{
		return myHealthPack2Position;
	}

	CollisionData CheckRayWallCollision(const CommonUtilities::Ray2D<float>& aRay, float aRayLength);

	void DebugAABB(const AABB2D<float>& anAABB, const Tga::Color& aColor = Tga::Color(1,0,0));
	void DebugCircle(const CommonUtilities::Vector2f& aPosition, float aRadius, const Tga::Color& aColor = Tga::Color(1, 0, 0));

	
	std::vector<std::shared_ptr<Wall>> GetObstacles()
	{
		return myObstacles;
	}

private:

	std::vector<std::shared_ptr<Wall>> myObstacles;

	std::shared_ptr<RobotMovement> myFirstRobot;
	std::shared_ptr<RobotMovement> mySecondRobot;
	CommonUtilities::Vector2f myHealthPackPosition;
	CommonUtilities::Vector2f myHealthPack2Position;

};