#include "CircleCollider.h"
#include "BoxCollider.h"
#include <SFML/Graphics.hpp>



CircleCollider::CircleCollider(sf::CircleShape& sprite)
	:sprite(sprite)
{
}


CircleCollider::~CircleCollider()
{
}

bool CircleCollider::collidesWith(const BoxCollider& other) const
{
	sf::Vector2f min(getMinXAndY());
	sf::Vector2f max(getMaxXAndY());
	sf::Vector2f otherMin(other.getMinXAndY());
	sf::Vector2f otherMax(other.getMaxXAndY());
	sf::Vector2f mag(getMagXAndY());
	sf::Vector2f otherMag(other.getMagXAndY());
	if (otherMag.x < mag.x)
	{
		if ((otherMin.x > min.x && otherMin.x < max.x) || (otherMax.x > min.x && otherMax.x < max.x))
		{
			if (otherMag.y < mag.y)
			{
				if ((otherMin.y > min.y && otherMin.y < max.y) || (otherMax.y > min.y && otherMax.y < max.y))
				{
					return true;
				}
			}
			else
			{
				if ((min.y > otherMin.y && min.y < otherMax.y) || (max.y > otherMin.y && max.y < otherMax.y))
				{
					return true;
				}
			}

		}
		return false;
	}
	else
	{
		if ((min.x > otherMin.x && min.x < otherMax.x) || (max.x > otherMin.x && max.x < otherMax.x))
		{
			if (otherMag.y < mag.y)
			{
				if ((otherMin.y > min.y && otherMin.y < max.y) || (otherMax.y > min.y && otherMax.y < max.y))
				{
					return true;
				}
			}
			else
			{
				if ((min.y > otherMin.y && min.y < otherMax.y) || (max.y > otherMin.y && max.y < otherMax.y))
				{
					return true;
				}
			}

		}
		return false;
	}
}

bool CircleCollider::collidesWith(const CircleCollider& other) const
{
	sf::Vector2f min(getMinXAndY());
	sf::Vector2f max(getMaxXAndY());
	sf::Vector2f otherMin(other.getMinXAndY());
	sf::Vector2f otherMax(other.getMaxXAndY());
	sf::Vector2f mag(getMagXAndY());
	sf::Vector2f otherMag(other.getMagXAndY());
	if (otherMag.x < mag.x)
	{
		if ((otherMin.x > min.x && otherMin.x < max.x) || (otherMax.x > min.x && otherMax.x < max.x))
		{
			if (otherMag.y < mag.y)
			{
				if ((otherMin.y > min.y && otherMin.y < max.y) || (otherMax.y > min.y && otherMax.y < max.y))
				{
					return true;
				}
			}
			else
			{
				if ((min.y > otherMin.y && min.y < otherMax.y) || (max.y > otherMin.y && max.y < otherMax.y))
				{
					return true;
				}
			}

		}
		return false;
	}
	else
	{
		if ((min.x > otherMin.x && min.x < otherMax.x) || (max.x > otherMin.x && max.x < otherMax.x))
		{
			if (otherMag.y < mag.y)
			{
				if ((otherMin.y > min.y && otherMin.y < max.y) || (otherMax.y > min.y && otherMax.y < max.y))
				{
					return true;
				}
			}
			else
			{
				if ((min.y > otherMin.y && min.y < otherMax.y) || (max.y > otherMin.y && max.y < otherMax.y))
				{
					return true;
				}
			}

		}
		return false;
	}
}

sf::Vector2f& CircleCollider::getMinXAndY() const
{
	sf::Vector2f pos(sprite.getPosition());
	return sf::Vector2f(pos.x - sprite.getRadius(), pos.y - sprite.getRadius());
}

sf::Vector2f& CircleCollider::getMaxXAndY() const
{
	sf::Vector2f pos(sprite.getPosition());
	return sf::Vector2f(pos.x + sprite.getRadius(), pos.y + sprite.getRadius());
}

sf::Vector2f& CircleCollider::getMagXAndY() const
{
	sf::Vector2f min(getMinXAndY());
	sf::Vector2f max(getMaxXAndY());
	return max - min;
}

