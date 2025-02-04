#pragma once
#include "GameObject.h"
#include <CommonUtilities/CommonUtilities.h>

class Wall : public GameObject
{
public:
	Wall() = default;
	~Wall() {};

	void Init(CommonUtilities::Vector2f& aStartPosition, std::string aPath, float aWidth = 50.0f, float aHeight = 500.0f);
	void Update(float aDeltaTime) override;

	CommonUtilities::AABB2D<float>& GetAABB() { return myAABB; }
private:

	CommonUtilities::AABB2D<float> myAABB;
	float myWidth;
	float myHeight;
};
