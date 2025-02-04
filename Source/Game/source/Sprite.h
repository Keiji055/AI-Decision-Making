#pragma once
#include "tge/sprite/sprite.h"
#include <tge/graphics/GraphicsEngine.h>
#include <tge/drawers/SpriteDrawer.h>
#include <tge/Math/Transform.h>
#include "tge\math\Vector.h"

class Sprite
{
public:
	void Init(const std::string aSpritePath, Tga::Vector2f aPosition = { -1,-1 }, const float& aSize = -1);

	void Render(Tga::SpriteDrawer& aDrawer);
	Tga::SpriteSharedData mySharedData = {};

	void SetPosition(Tga::Vector2f aPosition);
	void Move(const Tga::Vector2f& aPosition);
	void ChangeColor(const Tga::Vector3f color);

	void DebugPosition();

	float GetSize();
	void ChangeRotation(float aRotation);
	void ChangeSprite(const std::string& aSpritePath);

	float GetRotation() const { return mySprite2D.myRotation; }

	void SetPivot(const Tga::Vector2f& aPivot);

private:
	Tga::Sprite2DInstanceData mySprite2D;
	Tga::Vector2f myPivot;
	Tga::Vector2f myOffsetPosition;
	float myTimer;
};