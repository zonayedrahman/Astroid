#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

class Bullet
{

private:

	sf::Sprite sprite;

	sf::Vector2f direction;
	float movementSpeed;


public:
	//Bullet();
	Bullet(sf::Texture* texture, float pos_x, float pos_y, float dir_x, float dir_y, float movement_speed);
	virtual ~Bullet();


	// accessors

	const sf::FloatRect getBounds() const;


	void update();
	void render(sf::RenderTarget* target);


};

