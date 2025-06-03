#include "Game.h"
#include <iostream>

Game::Game(const std::string& config)
{
	init(config);
}

void Game::init(const std::string& path)
{
	//TODO read in config file here 
	//use the premage PlayerConfig, ENemy COnfig , Bullet COnfig Varaibales

	//set up default window parameters 

	m_window.create(sf::VideoMode({ 1280, 730 }), "Assignmet 2");
	m_window.setFramerateLimit(60);


	ImGui::SFML::Init(m_window);
	

	//scale the imgui ui and text size by 2;
	ImGui::GetStyle().ScaleAllSizes(2.0f);
	ImGui::GetIO().FontGlobalScale = 2.0f;

	spawnPlayer();
}
std::shared_ptr<Entity> Game::player()
{
	auto& players = m_entities.getEntities("player");
	assert(players.size() == 1);
	return players.front();
}

void Game::run()
{
	//TODO:add pause functionality in here 
	//some system should funciton while pauserd
	//some systems should not (movement/input)
	while (m_running)
	{
		//update the entity manager 
		m_entities.update();
		//required to update call to imgui
		ImGui::SFML::Update(m_window, m_deltaClock.restart());
		sEnemySpawner();
		sMovement();
		sCollision();
		sUserInput();
		sGUI();
		sRender();

		//increment th current frame 
		//may need to moved when pause implemented 

		m_currentFrame++;

	}
}
void Game::setPaused(bool paused)
{
	//TODO

}

void Game::spawnPlayer()
{
	//todo :Finish adding all properties of the player with the correct values from the 

	//we create every entity by calling EnitityManager.addEntity(tag)
	//This returns a std::shared_ptr<Entity> so we use auto to save typing 
	auto entity = m_entities.addEntity("player");

	//Give this entity a Transfrom so it spawns at (200,200) with a velocity (1,1) and angle 
	entity->add<CTransform>(Vec2f(200.0f, 200.0f), Vec2f(1.0f, 1.0f), 0.0f);

	//the enittiy shape will have radius 32, 8 sides dark grey fill and gred outline of 
	entity->add<CShape>(32.0f, 8, sf::Color(10, 10, 10), sf::Color(255, 0, 0), 4.0f);

		//add a input component to the player so that we can use inputs
	entity->add<CInput>();

}
//spawn an enemy at a random position 

void Game::spawnEnemy()
{
	//TODO:make sure the enemy is spawned properly with the m_enemey Config variables 
	// the enemy mush be spawneed completely within bounds fo the window 
	//

	//record when the most recenet enemy was spawned
	m_lastEnemySpawnTime = m_currentFrame;

}
//spawns the small enemies when a big one (input entity e_ explodes
void Game::spawnSmallEnemies(std::shared_ptr<Entity> e)
{

	//Todo: spawn small enemies at the loacation of the input enemy e

	//when we create the smaller enemy we have tot read the values of the original enemy
	//-spawn a number of small enemies equal to the vertices of the original enemy 
	//- set each small enemy to the smae color as the original half the size 
	// small enemies are wroth double pointes of the oriignal enemy




}

//spawns a bullet from a given entity to a target location 
void Game::spawnBullet(std::shared_ptr<Entity>entity, const Vec2f& target)
{
	//TODO: implementation the spawining of the bullet which travels toward taret
	// -bullet speed is giving as a scalar speed 
	// -you must set the velocity  by using formula in notes
}

void Game :: spawnSpecialWeapon(std::shared_ptr<Entity> entity)
{
	//Todo:implement your own speical weapon


}

void Game::sMovement()
{
	//TOdo:implement all entity movement in this funciton 
	// you should read the m_player->cInput componenet to determine if player is 

	//Sample movenet speed update
	auto& transform = player()->get<CTransform>();
	transform.pos.x += transform.velocity.x;
	transform.pos.y += transform.velocity.y;

}
void Game::sLifespan()
{
	//Todo : implement all lifespan functionality
	//
	//for all entites
	//if entity has no lifespan component , skip it 
	// if entity has >0 remaining lifespan subract 1
	//if it has lifespan and is alive
	// scale its alpha channel properly
	// if it has lifespan and its time is up
	// destroy the entity

}
void Game::sCollision() {
	//TODO:implement all proper collisions between entities
	//be sure to use the collition radius not the shape radius 
}

void Game::sEnemySpawner()
{
	//TODO :code which implements enemey spawning should go here
}

void Game :: sGUI() {
	ImGui::Begin("Geometry Wars");
	ImGui::Text("Stuff GOes here");
	ImGui::End();
}

void Game::sRender() {
	//TODOL :change the code below to draw all the entites
	//sample drawing of the player Entity that we have creater 

	m_window.clear();

	//set the position of the shape based on the entity tranform->pos
	player()->get<CShape>().circle.setPosition(player()->get < CTransform>().pos);


	//set the rotation of the shape based ont the entity tranfrom ->angle
	player()->get<CTransform>().angle += 1.0f;
	player()->get<CShape>().circle.setRotation(player()->get<CTransform>().angle);

	//draw the entity sf::CircleShape


m_window.draw(player()->get<CShape>().circle);


//draw the ui last
ImGui::SFML::Render(m_window);
m_window.display();

}
void Game::sUserInput()
{
	//TODO : handle user input here
	// note that you should only be setting the player input component variables here
	//you should not implement the player movement logic here
	//the movement system will read the variable you set in this function 

	sf::Event event;
	while (m_window.pollEvent(event)) {

		//pass the event to imgui to be parserd 
		ImGui::SFML::ProcessEvent(m_window, event);

		//this event triggers when the window is closed
		if (event.type == sf::Event::Closed) {
			m_running = false;
		}

		//this event is triggered when a key is pressed 
		if (event.type == sf::Event::KeyPressed)
		{
			switch (event.key.code)
			{
			case sf::Keyboard::W:
					std::cout << "W KEY is pressed\n";
					//TODO set player input component "UP" to true;
					break;
				default:break;
			}
		}
		if (event.type == sf::Event::KeyReleased)
		{
			switch (event.key.code)
			{
			case sf::Keyboard::W:
				std::cout << "W key released\n";
				//Todo: set player input component  up to false
				break;
			default:break;
			}

		}
		if (event.type == sf::Event::MouseButtonPressed)
		{
			//this line ignores mouse events if ImGUi is the thing being clicked 
			if (ImGui::GetIO().WnatCaptureMouse) { continue; }

			if (event.mouseButton.button == sf::Mouse::Left) {
				std::cout << "Left mouse button cliecket at " << event.mouseButton.x << ",";
				//call spawn Bullet here
			}
			if (event.mouseButton.button == sf::Mouse::Right)
			{
				std::cout << "Right Mouse Button CLicket at (" << event.mouseButton.x << ",";
			}
		}

	}
}
