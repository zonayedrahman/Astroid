#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>


class Player
{
private:

	sf::IntRect spritePositionInSheet;
	sf::Sprite sprite;
	sf::Texture texture;

	float movementSpeed;


	float attackCooldown;
	float attackCooldownMax;


	int hp;
	int hpMax;




	// functions
	void initVariables();
	void initTexture();
	void initSprite(sf::RenderWindow* window);

	



public:

	Player(sf::RenderWindow* window);
	virtual ~Player();


	// accessors
	const sf::Vector2f getPos() const;
	const sf::FloatRect getBounds() const;
	const int& getHp() const;
	const int& getHpMax() const;


	// modifiers
	void setPosition(const sf::Vector2f pos);
	void setPosition(const float x, const float y);
	void setHp(int new_value);
	void loseHp(const int value);

	// functions
	void move(const float dirX, const float dirY);
	const bool canAttack();

	void updateAttack();
	void update();
	void render(sf::RenderTarget& target);

};

