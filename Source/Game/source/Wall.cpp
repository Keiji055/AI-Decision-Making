#include "Wall.h"



#include "PollingStation.h"

void Wall::Init(CommonUtilities::Vector2f& aStartPosition, std::string aPath, float aWidth, float aHeight)
{
	GameObject::Init(aStartPosition, aPath);
	myWidth = aWidth;
	myHeight = aHeight;
	CommonUtilities::Vector2f max = CommonUtilities::Vector2f(aStartPosition.x + myWidth, aStartPosition.y + myHeight);
	CommonUtilities::Vector2f min = aStartPosition;
	myAABB.InitWithMinAndMax(min, max);
}

void Wall::Update(float aDeltaTime)
{

	PollingStation::Get().DebugAABB(myAABB);

}
