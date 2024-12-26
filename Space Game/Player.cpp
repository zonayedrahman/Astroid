#include "Player.h"


void Player::initVariables()
{
	this->movementSpeed = 5.f;
	this->attackCooldownMax = 50.f;
	this->attackCooldown = this->attackCooldownMax;

	this->hpMax = 100;
	this->hp = this->hpMax;
}

void Player::initTexture()
{

	// load texture from file
	if (!this->texture.loadFromFile("Textures/Spaceship_SpriteSheet.png")) {
		std::cout << "ERROR::PLAYER.CPP::INITTEXTURE:: FAILED TO LOAD TEXTURE FROM FILE\n";
	}
}

void Player::initSprite(sf::RenderWindow* window)
{

	// set the texture to sprite
	this->sprite.setTexture(this->texture);

	this->spritePositionInSheet = sf::IntRect(0, 128, 64, 64);
	this->sprite.setTextureRect(this->spritePositionInSheet);


	// resize sprite
	this->sprite.scale(1.f, 1.f);


	// set initial position
	this->sprite.setPosition((window->getSize().x / 2.f) - 32.f, window->getSize().y - 64.f);


}

Player::Player(sf::RenderWindow* window)
{

	this->initVariables();
	this->initTexture();
	this->initSprite(window);
}

Player::~Player()
{
}

const sf::Vector2f Player::getPos() const
{
	return this->sprite.getPosition();
}

const sf::FloatRect Player::getBounds() const
{
	return this->sprite.getGlobalBounds();
}

const int& Player::getHp() const
{
	// TODO: insert return statement here
	return this->hp;
}

const int& Player::getHpMax() const
{
	// TODO: insert return statement here
	return this->hpMax;
}

void Player::setPosition(const sf::Vector2f pos)
{
	this->sprite.setPosition(pos);
}

void Player::setPosition(const float x, const float y)
{
	this->sprite.setPosition(x, y);
}

void Player::setHp(const int new_value)
{
	this->hp = new_value;
	if (this->hp < 0) {
		this->hp = 0;
	}
}

void Player::loseHp(const int value)
{
	this->hp -= value;
	if (this->hp < 0) {
		this->hp = 0;
	}
	std::cout << this->hp << "\n";
}

void Player::move(const float dirX, const float dirY)
{
	this->sprite.move(this->movementSpeed * dirX, this->movementSpeed * dirY);
}

const bool Player::canAttack()
{
	if (this->attackCooldown >= this->attackCooldownMax) {
		this->attackCooldown = 0.f;
		return true;
	}
	return false;
}

void Player::updateAttack()
{
	if (this->attackCooldown < this->attackCooldownMax)
	{
		this->attackCooldown += 1.f;
	}

}

void Player::update()
{
	this->updateAttack();
}

void Player::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);

}
