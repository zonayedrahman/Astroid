#pragma once


#include <map>
#include <string>
#include <sstream>


#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"





class Game
{

private:
	// window
	sf::RenderWindow* window;


	// resources
	std::map<std::string, sf::Texture*> textures;
	std::vector<Bullet*> bullets;
	
	
	// gui

	sf::Font font;
	sf::Text pointText;

	sf::Text gameOverText;




	// systems
	unsigned points;


	// player
	Player* player;


	// player GUI
	sf::RectangleShape playerHpBar;
	sf::RectangleShape playerHpBarBack;


	// enemies

	float spawnTimer;
	float spawnTimerMax;
	std::vector<Enemy*> enemies;
	//Enemy* enemy;




	// world

	sf::Sprite worldBackground;
	sf::Texture worldBackgroundTexture;
	



	// private functions
	void initWindow();
	void initTextures();
	void initGUI();
	void initWorld();
	void initSystems();

	void initEnemies();
	void initPlayer();
public:

	Game();
	virtual ~Game();




	// Functions
	void run();


	void updatePollEvents();
	void updateInput();
	void updateGUI();

	void updateWorld();
	void updateCollision();
	void updateBullets();
	void updateEnemies();
	void updateCombat();

	void update();

	void renderGUI();
	void renderWorld();
	void render();

};

