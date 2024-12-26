#include "Enemy.h"



void Enemy::initVariables()
{
	this->pointCount = static_cast<unsigned>(rand() % 8 + 3); // min = 3  &  max = 7
	this->type = 0;
	this->speed = static_cast<float>(rand() % 3 + 1);
	this->hpMax = static_cast<int>(this->pointCount);
	this->hp = this->hpMax;
	this->damage = static_cast<int>(this->pointCount);
	this->points = static_cast<int>(this->pointCount);
}

void Enemy::initShape()
{
	this->shape.setRadius(static_cast<float>(this->pointCount) * 5.f);
	this->shape.setPointCount(static_cast<size_t>(this->pointCount));
	this->shape.setFillColor(sf::Color(static_cast<sf::Uint8>(rand() % 255 + 1), static_cast<sf::Uint8>(rand() % 255 + 1), static_cast<sf::Uint8>(rand() % 255 + 1), 255));

}

Enemy::Enemy(float pos_x, float pos_y)
{
	this->initVariables();
	this->initShape();

	this->shape.setPosition(pos_x, pos_y);
}

Enemy::~Enemy()
{
}

const sf::FloatRect Enemy::getBounds() const
{
	return this->shape.getGlobalBounds();
}

const int& Enemy::getPoints() const
{
	// TODO: insert return statement here
	return this->points;
}

const int& Enemy::getDamage() const
{
	// TODO: insert return statement here
	return this->damage;
}

void Enemy::update()
{
	this->shape.move(0.f, this->speed);
}

void Enemy::render(sf::RenderTarget* target)
{
	target->draw(this->shape);
}
