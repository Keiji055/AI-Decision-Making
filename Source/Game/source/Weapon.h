#pragma once
#include "GameObject.h"

enum class TargetType
{
	StateStackRobot,
	DecisionTreeRobot,
};

class RobotMovement;

struct Bullet : public GameObject
{
	CommonUtilities::Vector2f myDirection;
	float myAngle = 0.0f;
	float mySpeed = 500.0f;
	bool myIsActive = false;
};

class Weapon : public GameObject
{
public:
	Weapon() = default;
	~Weapon() {};

	void Init(TargetType aTarget);
	void Update(float aDeltaTime) override;
	void Render(Tga::SpriteDrawer& aSpriteDrawer) override;
	void Shoot(const CommonUtilities::Vector2f& aDirection);
	bool IsOutOfBounds(const CommonUtilities::Vector2f& aPosition);
private:
	std::array<Bullet,10> myBullets;
	std::shared_ptr<RobotMovement> myTarget;
};
