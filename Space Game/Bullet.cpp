#include "Bullet.h"



//Bullet::Bullet()
//{
//}

Bullet::Bullet(sf::Texture* texture, float pos_x, float pos_y, float dir_x, float dir_y, float movement_speed)
{
	this->sprite.setTexture(*texture);
	sprite.setScale(0.2f, 0.2f);
	sprite.setRotation(-90);
	this->sprite.setPosition(pos_x, pos_y);
	this->direction.x = dir_x;
	this->direction.y = dir_y;
	this->movementSpeed = movement_speed;

}


Bullet::~Bullet()
{
}

const sf::FloatRect Bullet::getBounds() const
{
	return this->sprite.getGlobalBounds();
}

void Bullet::update()
{
	this->sprite.move(this->movementSpeed * this->direction);
}

void Bullet::render(sf::RenderTarget* target)
{
	target->draw(this->sprite);
}
