#include "Entity.h"

namespace Hydra
{
	Entity::Entity(int nLife)
	{
		life = nLife;
	}

	void Entity::sVX(float nVX)
	{
		vel.setX(nVX);
	}

	void Entity::sVY(float nVY)
	{
		vel.setY(nVY);
	}

	void Entity::sPX(float nPX)
	{
		posX = nPX;
	}

	void Entity::sPY(float nPY)
	{
		posY = nPY;
	}

	void Entity::sR(float nR_rad)
	{
		rot = nR_rad;
	}

	Vector2D Entity::gV()
	{
		return vel;
	}

	float Entity::gPX()
	{
		return posX;
	}

	float Entity::gPY()
	{
		return posY;
	}

	float Entity::gR()
	{
		return rot;
	}
}
