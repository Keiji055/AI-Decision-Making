#include "GameObject.h"
#include <tge/Engine.h>
#include <tge/graphics/GraphicsEngine.h>
#include <tge/drawers/SpriteDrawer.h>

void GameObject::Init(const CommonUtilities::Vector2f& aStartPosition, std::string aPath)
{
	myPosition = aStartPosition;
	mySprite.Init(aPath, { myPosition.x, myPosition.y }, 1);
	mySpriteAdded = true;
	myHealth = myMaxHealth;
}

void GameObject::Render(Tga::SpriteDrawer& aSpriteDrawer)
{
	mySprite.Render(aSpriteDrawer);
	assert(mySpriteAdded == true && L"You should init the GameObject first");
}

void GameObject::UpdateTransform(const CommonUtilities::Vector2f& aPosition,const float aRotation)
{
	myPosition = aPosition;
	mySprite.SetPosition({myPosition.x, myPosition.y});
	mySprite.ChangeRotation(aRotation);
	assert(mySpriteAdded == true && L"You should init the GameObject first");
}

CommonUtilities::Vector2f GameObject::GetPosition() const
{
	assert(mySpriteAdded == true && L"You should init the GameObject first");
	return myPosition;
}

void GameObject::ResetPosition()
{
	//std::cout << "robot is dead -> Resetting position" << std::endl;
	UpdateTransform(myOriginalPosition, 0.0f);
	myHealth = myMaxHealth;
}

void GameObject::TakeDamage(int amountOfDamage)
{
	myHealth -= amountOfDamage;
	//std::cout << "Robot took damage: " << amountOfDamage << std::endl;
	if (myHealth <= 0)
	{
		myHealth = 0;
		ResetPosition();
	}
}
