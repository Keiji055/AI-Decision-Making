#include "Sprite.h"
#include <tge/math/Matrix2x2.h>
#include <tge/drawers/DebugDrawer.h>
#include "tge/engine.h"
#include "tge/settings/settings.h"
#include "tge/texture/TextureManager.h"

#include "tge/primitives/LinePrimitive.h"
#include <tge/drawers/DebugDrawer.h>
#include <tge/drawers/LineDrawer.h>

void Sprite::Init(const std::string aSpritePath, Tga::Vector2f aPosition, const float& aSize)
{
	float defaultValue = -1.f;
	mySharedData.myTexture = Tga::Engine::GetInstance()->GetTextureManager().GetTexture(Tga::Settings::EngineAssetW(aSpritePath).c_str());
	mySprite2D.myPivot = { 0.5f, 0.5f };
	if (aSize == defaultValue)
	{
		mySprite2D.mySize = mySharedData.myTexture->CalculateTextureSize();
	}
	else
	{
		mySprite2D.mySize = mySharedData.myTexture->CalculateTextureSize();
		mySprite2D.mySizeMultiplier = aSize;
	}
	if (aPosition.y == defaultValue)
	{
		float Width = static_cast<float>(Tga::Engine::GetInstance()->GetRenderSize().x * 0.1f);
		float Hight = static_cast<float>(Tga::Engine::GetInstance()->GetRenderSize().y * 0.5f);
		mySprite2D.myPosition = { Width, Hight };
	}
	else
	{

		mySprite2D.myPosition = { aPosition.x, aPosition.y };
	}
}


void Sprite::Render(Tga::SpriteDrawer& aDrawer)
{

	aDrawer.Draw(mySharedData, mySprite2D);
}


void Sprite::SetPosition(Tga::Vector2f aPosition)
{
	mySprite2D.myPosition = { aPosition.x,aPosition.y};

}

void Sprite::Move(const Tga::Vector2f& aPosition)
{
	mySprite2D.myPosition += { aPosition.x, aPosition.y };
}

void Sprite::ChangeColor(const Tga::Vector3f color)
{
	mySprite2D.myColor = Tga::Color(color.x, color.y, color.z);
}

void Sprite::DebugPosition()
{
	std::cout << "( " << mySprite2D.myPosition.x << " , " << mySprite2D.myPosition.y << " )" << std::endl;
}

float Sprite::GetSize()
{
	return mySprite2D.mySize.x;
}

void Sprite::ChangeRotation(float aRotation)
{
	mySprite2D.myRotation = aRotation;
}

void Sprite::ChangeSprite(const std::string& aSpritePath)
{
	mySharedData.myTexture = Tga::Engine::GetInstance()->GetTextureManager().GetTexture(Tga::Settings::EngineAssetW(aSpritePath).c_str());
}

void Sprite::SetPivot(const Tga::Vector2f& aPivot)
{
	mySprite2D.myPivot = aPivot;
}
