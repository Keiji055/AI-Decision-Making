#include "Weapon.h"
#include "PollingStation.h"
#include "RobotMovement.h"

void Weapon::Init(TargetType aTarget)
{
	GameObject::Init({0,0}, "");

	for (size_t i = 0; i < myBullets.size(); i++)
	{
		myBullets[i].Init();
		myBullets[i].GetSprite().Init("Sprites/R.png", { 500,500 }, 0.1f);
	}

 	switch (aTarget)
	{
	case TargetType::StateStackRobot:
		myTarget = PollingStation::Get().GetStateStackRobot();
		break;
	case TargetType::DecisionTreeRobot:
		myTarget = PollingStation::Get().GetDecisionTreeRobot();
		break;
	default:
		break;
	}

}

void Weapon::Update(float aDeltaTime)
{
	//update bullets transform to move towards the direction
	

	for (auto& bullet : myBullets)
	{
		if (bullet.myIsActive)
		{
			bullet.UpdateTransform(bullet.GetPosition() + bullet.myDirection * bullet.mySpeed * aDeltaTime, bullet.myAngle);
			if (bullet.GetPosition().Distance(myTarget->GetPosition()) < 50.0f)
			{
				myTarget->TakeDamage();
				bullet.myIsActive = false;
			}
			if (IsOutOfBounds(bullet.GetPosition()))
			{
				bullet.myIsActive = false;
			}
		}
	}
}

void Weapon::Render(Tga::SpriteDrawer& aSpriteDrawer)
{
	for (auto& bullet : myBullets)
	{
		if (bullet.myIsActive)
		{
			bullet.Render(aSpriteDrawer);
		}
	}
}

void Weapon::Shoot(const CommonUtilities::Vector2f& aDirection)
{
	for (auto& bullet : myBullets)
	{
		if (!bullet.myIsActive)
		{
			bullet.myIsActive = true;
			bullet.myAngle = atan2f(aDirection.y, aDirection.x);
			bullet.UpdateTransform(GetPosition(), bullet.myAngle);
			bullet.myDirection = aDirection.GetNormalized();
			return;
		}
	}
}

bool Weapon::IsOutOfBounds(const CommonUtilities::Vector2f& aPosition)
{
	if (aPosition.x < -500.0f || aPosition.x > 1500 || aPosition.y < -500.0f || aPosition.y > 1500)
	{
		return true;
	}
	return false;
}
