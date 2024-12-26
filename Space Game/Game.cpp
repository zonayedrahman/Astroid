#include "Game.h"

void Game::initWindow()
{
	this->window = new sf::RenderWindow(sf::VideoMode(800, 600), "Space Game 3", sf::Style::Close | sf::Style::Titlebar);
	this->window->setFramerateLimit(144);
	this->window->setVerticalSyncEnabled(false);
}

void Game::initTextures()
{
	this->textures["BULLET"] = new sf::Texture();
	if (!this->textures["BULLET"]->loadFromFile("Textures/Bullet.png")) {
		std::cout << "ERROR::GAME.CPP::INITTEXTURES()::FAILED TO LOAD TEXTURE\n";
	}
}


void Game::initGUI()
{
	if (!this->font.loadFromFile("Fonts/SHPinscher-Regular.otf")) {
		std::cout << "ERROR::GAME::InitGui()::Failed to load font\n";
	}
	this->pointText.setFont(this->font);
	this->pointText.setCharacterSize(24);
	this->pointText.setFillColor(sf::Color::White);
	this->pointText.setString("Test");
	this->pointText.setPosition(4.f, 40.f);


	// gameover text
	this->gameOverText.setFont(this->font);
	this->gameOverText.setCharacterSize(60);
	this->gameOverText.setFillColor(sf::Color::Red);
	this->gameOverText.setString("Game Over!");
	this->gameOverText.setPosition(
		this->window->getSize().x / 2.f - this->gameOverText.getGlobalBounds().width / 2.f,
		this->window->getSize().y / 2.f - this->gameOverText.getGlobalBounds().height / 2.f);

	// init player gui
	this->playerHpBar.setSize(sf::Vector2f(300.f, 25.f));
	this->playerHpBar.setFillColor(sf::Color::Red);
	this->playerHpBar.setPosition(sf::Vector2f(10.f, 10.f));

	this->playerHpBarBack = this->playerHpBar;
	this->playerHpBarBack.setFillColor(sf::Color(25, 25, 25, 200));
}

void Game::initWorld()
{
	//if (!this->worldBackgroundTexture.loadFromFile("Textures/background.jpg")) {
	//	std::cout << "ERROR::GAME::initWorld()::Failed to load background texture\n";
	//}
	//this->worldBackground.setTexture(this->worldBackgroundTexture);
}

void Game::initSystems()
{
	this->points = 0;
}

void Game::initEnemies()
{
	this->spawnTimerMax = 50.f;
	this->spawnTimer = this->spawnTimerMax;
}

void Game::initPlayer()
{
	this->player = new Player(this->window);
	//this->enemy = new Enemy(20.f, 20.f);
}

Game::Game()
{

	this->initWindow();
	this->initTextures();
	this->initGUI();
	this->initWorld();
	this->initEnemies();
	this->initPlayer();
	this->initSystems();
}

Game::~Game()
{
	delete this->window;
	delete this->player;

	// textures
	for (auto &i : this->textures) {
		delete i.second;
	}


	// bullets
	for (auto* i : this->bullets) {
		delete i;
	}

	// enemies
	for (auto* i : this->enemies) {
		delete i;
	}
}


// Functions
void Game::run()
{
	while (this->window->isOpen())
	{
		this->updatePollEvents();
		if (this->player->getHp() > 0)
		{
			this->update();
			this->render();
		}
	}
}



void Game::updatePollEvents()
{
	sf::Event e;
	while (this->window->pollEvent(e)) {


		// close on x 
		if (e.type == sf::Event::Closed) {
			this->window->close();
		}

		// close on escape key
		if (e.KeyPressed && e.key.code == sf::Keyboard::Escape) {
			this->window->close();
		}

	}
}

void Game::updateInput()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		this->player->move(-1.f, 0.f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		this->player->move(1.f, 0.f);
	}


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		this->player->move(0.f, -1.f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		this->player->move(0.f, 1.f);
	}

	

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->player->canAttack()) {
		this->bullets.push_back(new Bullet(this->textures["BULLET"], 
			// centering
			this->player->getPos().x + 16.f,
			this->player->getPos().y + 16.f,
			0.f, -1.f, 5.f));
	}
}

void Game::updateGUI()
{
	std::stringstream ss;


	// TEST
	//this->player->setHp(5);
	// ==========================================
	ss << " Points: " << this->points << "\n";
	this->pointText.setString(ss.str());


	// update player GUI
	float hpPercent = static_cast<float>(this->player->getHp()) / this->player->getHpMax();
	this->playerHpBar.setSize(sf::Vector2f(
		300.f * hpPercent,
		this->playerHpBar.getSize().y));




}

void Game::updateWorld()
{
}

void Game::updateCollision()
{
	// horizontal window collision
	if (this->player->getBounds().left < 0.f) {
		this->player->setPosition(0.f, this->player->getBounds().top);
	}

	if (this->player->getBounds().left + this->player->getBounds().width > this->window->getSize().x) {
		this->player->setPosition(this->window->getSize().x - this->player->getBounds().width, this->player->getBounds().top);
	}


	// vertical window collision
	if (this->player->getBounds().top < 0.f) {
		this->player->setPosition(this->player->getPos().x, 0.f);
	}

	if (this->player->getBounds().top + this->player->getBounds().height > this->window->getSize().y) {
		this->player->setPosition(this->player->getPos().x, this->window->getSize().y - this->player->getBounds().height);
	}

}

void Game::updateBullets()
{

	unsigned counter = 0;
	for (auto* bullet : this->bullets) {
		bullet->update();


		// bullet culling at top of screen
		if (bullet->getBounds().top + bullet->getBounds().height < 0.f) {

			// delete bullet
			delete this->bullets.at(counter);
			this->bullets.erase(this->bullets.begin() + counter);

		}
		++counter;
	}
}

void Game::updateEnemies()
{
	this->spawnTimer += 0.5f;

	if (this->spawnTimer >= this->spawnTimerMax) {

		
		this->enemies.push_back(new Enemy(static_cast<float>(rand() % this->window->getSize().x - 20.f), static_cast<float>(-100.f)));
		this->spawnTimer = 0.f;
		
	}

	unsigned counter = 0;
	for (auto* enemy : this->enemies) {
		enemy->update();


		// enemy culling at bottom of screen
		if (enemy->getBounds().top > this->window->getSize().y) {

			// delete enemy
			delete this->enemies.at(counter);
			this->enemies.erase(this->enemies.begin() + counter);

		} 


		// collision with player
		else if (enemy->getBounds().intersects(this->player->getBounds())) {

			this->player->loseHp(this->enemies.at(counter)->getDamage());


			delete this->enemies.at(counter);
			this->enemies.erase(this->enemies.begin() + counter);



		}


		++counter;
	}

	
}

void Game::updateCombat()
{
	for (unsigned int i = 0; i < this->enemies.size(); i++) {

		bool enemy_deleted = false;
		
		for (unsigned int j = 0; j < this->bullets.size() && !enemy_deleted; j++) {

			if (this->enemies[i]->getBounds().intersects(this->bullets[j]->getBounds())) {

				// remove enemy

				this->points += this->enemies[i]->getPoints();
				delete this->enemies[i];
				this->enemies.erase(this->enemies.begin() + i);

				// remove bullet
				delete this->bullets[j];
				this->bullets.erase(this->bullets.begin() + j);

				

				enemy_deleted = true;
			}
		}
	}
}

void Game::update()
{
	
	//this->updatePollEvents();     // happens in run()
	this->updateInput();
	

	this->player->update();
	this->updateCollision();
	this->updateBullets();
	this->updateEnemies();
	this->updateCombat();

	this->updateGUI();
	this->updateWorld();

}

void Game::renderGUI()
{
	this->window->draw(this->pointText);

	
	this->window->draw(this->playerHpBarBack);
	this->window->draw(this->playerHpBar);
}

void Game::renderWorld()
{
	this->window->draw(this->worldBackground);
}

void Game::render()
{

	this->window->clear();

	// draw world
	this->renderWorld();

	// draw
	this->player->render(*this->window);

	for (auto* bullet : this->bullets) {
		bullet->render(this->window);
	}

	//this->enemy->render(this->window);
	for (auto* enemy : enemies) {
		enemy->render(this->window);
	}

	this->renderGUI();

	// game over screen

	if (this->player->getHp() <= 0) {
		this->window->draw(this->gameOverText);
	}


	this->window->display();
}
