#pragma once
#include "RobotMovement.h"
#include "Weapon.h"


enum class RobotState
{
	MovingToEnemy,
	MovingToHealth,
	Arrived,
	Shooting
};


class StateStackRobot : public RobotMovement
{
public:
	StateStackRobot()= default;
	~StateStackRobot() {};

	void Init(const CommonUtilities::Vector2f& aStartPosition = CommonUtilities::Vector2f(100.0f, 100.0f), std::string aPath = "");

	void Update(float aDeltaTime) override;

	void Render(Tga::SpriteDrawer& aSpriteDrawer) override;

private:
	void MovingToEnemyState(float aDeltaTime);
	void MovingToHealthState(float aDeltaTime);
	void ArrivedState(float aDeltaTime);
	void ShootingState(float aDeltaTime);

	void SetState(RobotState aState);


	float detectionRange = 200.0f;

	RobotState myState = RobotState::MovingToEnemy;

	Weapon myWeapon;
};

