#include "DesitionTreeRobot.h"
#include "PollingStation.h"
void DesitionTreeRobot::Init(const CommonUtilities::Vector2f& aStartPosition, std::string aPath)
{
	RobotMovement::Init(aStartPosition, aPath);
}

void DesitionTreeRobot::Update(float aDeltaTime)
{
	if (!didInitWeapon)
	{
		myWeapon.Init(TargetType::StateStackRobot);
		didInitWeapon = true;
	}
	myWeapon.Update(aDeltaTime);

	if (GetHealth() < GetMaxHealth() - 3 || isHealing)
	{
		GoToHealth(aDeltaTime);
	}
	else if (IsEnemyInRange())
	{
		ShootAtEnemy(aDeltaTime);
	}
	else
	{
		FollowEnemy(aDeltaTime);
	}

}

void DesitionTreeRobot::Render(Tga::SpriteDrawer& aSpriteDrawer)
{
	RobotMovement::Render(aSpriteDrawer);
	myWeapon.Render(aSpriteDrawer);
}

void DesitionTreeRobot::GoToHealth(float aDeltaTime)
{
	const auto& healthPackPosition = PollingStation::Get().GetHealthPackPosition();
	RobotMovement::GoToDestination(healthPackPosition, aDeltaTime);
	if (GetPosition().Distance(healthPackPosition) < 50.0f)
	{
		isHealing = true;
		
		static float timer = 0.0f;
		timer += aDeltaTime;
		if (timer > 0.1f)
		{
			SetHealth(GetHealth() + 1);
		//	std::cout << "Tree New health + 1: " << GetHealth() << std::endl;
			timer = 0.0f;
		}

		if (GetHealth() == GetMaxHealth())
		{
			isHealing = false;
		}
	}
}

void DesitionTreeRobot::ShootAtEnemy(float aDeltaTime)
{
	auto& pollingstation = PollingStation::Get();
	const auto& enemyPosition = pollingstation.GetStateStackRobot()->GetPosition();
	const auto& myPosition = GetPosition();
	
	static float time = 0.0f;
	time += aDeltaTime;
	const auto& direction = enemyPosition - GetPosition();
	UpdateTransform(GetPosition(), std::atan2(direction.y, direction.x));
	if (time > 1.f)
	{
		time = 0.0f;
		myWeapon.UpdateTransform(GetPosition(), 0.0f);
		myWeapon.Shoot(direction);
	}

}

void DesitionTreeRobot::FollowEnemy(float aDeltaTime)
{
	const auto& otherRobot = PollingStation::Get().GetStateStackRobot();
	RobotMovement::GoToDestination(otherRobot->GetPosition(), aDeltaTime);
}

bool DesitionTreeRobot::IsEnemyInRange()
{
	auto& pollingstation = PollingStation::Get();
	auto enemy = pollingstation.GetStateStackRobot();
	pollingstation.DebugCircle(GetPosition(), detectionRange, { 1.0f, 0.0f, 0.0f, 1.0f });
	if (GetPosition().Distance(enemy->GetPosition()) < detectionRange)
	{
		return true;
	}

	return false;
}
