#pragma once
#include "RobotMovement.h"
#include "Weapon.h"
class DesitionTreeRobot : public RobotMovement
{
public:
	DesitionTreeRobot() = default;
	~DesitionTreeRobot() {};

	void Init(const CommonUtilities::Vector2f& aStartPosition = CommonUtilities::Vector2f(100.0f, 100.0f), std::string aPath = "");

	void Update(float aDeltaTime) override;
	void Render(Tga::SpriteDrawer& aSpriteDrawer) override;
private:
	void GoToHealth(float aDeltaTime);
	void ShootAtEnemy(float aDeltaTime);
	void FollowEnemy(float aDeltaTime);
	bool IsEnemyInRange();
	float detectionRange = 200.0f;

	Weapon myWeapon;
	bool didInitWeapon = false;
	bool isHealing = false;
};

