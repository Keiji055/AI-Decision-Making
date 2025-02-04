#include "StateStackRobot.h"
#include "PollingStation.h"


void StateStackRobot::Init(const CommonUtilities::Vector2f& aStartPosition, std::string aPath)
{
	RobotMovement::Init(aStartPosition, aPath);
	myWeapon.Init(TargetType::DecisionTreeRobot);
	SetMaxSpeed(100.0f);
}

void StateStackRobot::Update(float aDeltaTime)
{
	switch (myState)
	{
	case RobotState::MovingToEnemy:
		MovingToEnemyState(aDeltaTime);
		break;
	case RobotState::Arrived:
		ArrivedState(aDeltaTime);
		break;
	case RobotState::Shooting:
		ShootingState(aDeltaTime);
		break;
	case RobotState::MovingToHealth:
		MovingToHealthState(aDeltaTime);
		break;
	default:
		break;
	}

	myWeapon.Update(aDeltaTime);

	//debug the detection range
	PollingStation::Get().DebugCircle(GetPosition(), detectionRange, { 0.0f, 1.0f, 0.0f, 1.0f });
}

void StateStackRobot::Render(Tga::SpriteDrawer& aSpriteDrawer)
{
	RobotMovement::Render(aSpriteDrawer);
	myWeapon.Render(aSpriteDrawer);
}

void StateStackRobot::MovingToEnemyState(float aDeltaTime)
{
	const auto& otherRobot = PollingStation::Get().GetDecisionTreeRobot();

	RobotMovement::GoToDestination(otherRobot->GetPosition(), aDeltaTime);
	if (GetPosition().Distance(otherRobot->GetPosition()) < detectionRange)
	{
		SetState(RobotState::Arrived);
	}

	if (GetHealth() < GetMaxHealth() - 3)
	{
		SetState(RobotState::MovingToHealth);
	}
}

void StateStackRobot::MovingToHealthState(float aDeltaTime)
{
	RobotMovement::GoToDestination(PollingStation::Get().GetHealthPack2Position(), aDeltaTime);
	if (GetPosition().Distance(PollingStation::Get().GetHealthPack2Position()) < detectionRange)
	{
		static float timer = 0.0f;
		timer += aDeltaTime;
		if (timer > 0.1f)
		{
			SetHealth(GetHealth() + 1);
			std::cout << "State New health + 1: " << GetHealth() << std::endl;
			timer = 0.0f;
		}
	}

	if (GetHealth() == GetMaxHealth())
	{
		SetState(RobotState::MovingToEnemy);
	}
}

void StateStackRobot::ArrivedState(float aDeltaTime)
{
	SetState(RobotState::Shooting);


	if (GetHealth() < GetMaxHealth() - 3)
	{
		SetState(RobotState::MovingToHealth);
	}
}

void StateStackRobot::ShootingState(float aDeltaTime)
{
	const auto& targetPosition = PollingStation::Get().GetDecisionTreeRobot()->GetPosition();
	const auto& healthPackPosition = PollingStation::Get().GetHealthPackPosition();
	static float time = 0.0f;
	time += aDeltaTime;
	const auto& direction = targetPosition - GetPosition();
	UpdateTransform(GetPosition(), std::atan2(direction.y, direction.x));
	if (time > 0.5f)
	{
		time = 0.0f;
		myWeapon.UpdateTransform(GetPosition(), 0.0f);
		myWeapon.Shoot(direction);
	}

	if (GetPosition().Distance(targetPosition) > detectionRange)
	{
		SetState(RobotState::MovingToEnemy);
	}


	if (GetHealth() < GetMaxHealth() - 3)
	{
		SetState(RobotState::MovingToHealth);
	}
}

void StateStackRobot::SetState(RobotState aState)
{
	myState = aState;
	//switch (aState)
	//{
	//case RobotState::MovingToEnemy:
	//	//std::cout << "State changed to: MOVING TO ENEMY" << std::endl;;
	//	break;
	//case RobotState::Arrived:
	//	//std::cout << "State changed to: ARRIVED" << std::endl;
	//	break;
	//case RobotState::Shooting:
	//	//std::cout << "State changed to: SHOOTING" << std::endl;
	//	break;
	//case RobotState::MovingToHealth:
	//	//std::cout << "State changed to: MOVING TO HEALTH" << std::endl;
	//	break;
	//default:
	//	break;
	//}
}
