#include "Game.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include<fstream>
#include<random>
Game::Game(const std::string& config) 
{
	init(config);
}



void Game::init(const std::string& path)
{
	//TODO read in config file here 
	//use the premage PlayerConfig, ENemy COnfig , Bullet COnfig Varaibales
	std::ifstream fin(path);
	std::string first;
	while (fin >> first) {
		if (first == "Window") {
			int www, hhh, fl, fs;
			fin >> www >> hhh >> fl >> fs;
			m_window.setPosition(Vec2(www, hhh));
			m_window.setFramerateLimit(fl);

		}
		if (first == "Font") {
			std::string name;
			int size, r, g, b;
			fin >> name >> size >> r >> g >> b;
			if (!m_font.openFromFile(name))
			{
				std::cerr << "could not load the font\n";
				exit(-1);
			}

		}
		if (first == "Player") {
			fin >> m_playerConfig.SR >> m_playerConfig.CR >> m_playerConfig.S >> m_playerConfig.FR >> m_playerConfig.FB >> m_playerConfig.OR >> m_playerConfig.OG >> m_playerConfig.OB >> m_playerConfig.OT >> m_playerConfig.V;

		}
		if (first == "Enemy") {
			fin >> m_enemyConfig.SR >> m_enemyConfig.CR >> m_enemyConfig.SMIN >> m_enemyConfig.SMAX >> m_enemyConfig.OR >> m_enemyConfig.OG >> m_enemyConfig.OB >> m_enemyConfig.OT >> m_enemyConfig.VMIN >> m_enemyConfig.VMAX >> m_enemyConfig.L >> m_enemyConfig.SI;

		}
		if (first == "Bullet") {
			fin >> m_bulletConfig.SR >> m_bulletConfig.CR >> m_bulletConfig.S >> m_bulletConfig.FR >> m_bulletConfig.FG >> m_bulletConfig.FB >> m_bulletConfig.OR >> m_bulletConfig.OG >> m_bulletConfig.OB >> m_bulletConfig.OT >> m_bulletConfig.V >> m_bulletConfig.L;
		}
	}

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
	entity->add<CShape>(m_playerConfig.SR, m_playerConfig.V, sf::Color(m_playerConfig.FR, m_playerConfig.FG,m_playerConfig.FB), sf::Color(m_playerConfig.OR,m_playerConfig.OG,m_playerConfig.OB), m_playerConfig.OT);

	//adding the collision componenet
	entity->add<CCollision>(m_playerConfig.CR);
	//add a input component to the player so that we can use inputs
	entity->add<CInput>();
	
}
//spawn an enemy at a random position 
template <typename T>
int rand_gen(T min, T max) {
	std::random_device rd;  // hardware entropy source (non-deterministic)
	std::mt19937 gen(rd()); // seed the generator
	std::uniform_int_distribution<> distr(min, max); // range: 10 to 50
	return distr(gen);
}
void Game::spawnEnemy()
{
	//TODO:make sure the enemy is spawned properly with the m_enemey Config variables 
	// the enemy mush be spawneed completely within bounds fo the window 
	auto entity = m_entities.addEntity("enemy");
	entity->add<CTransform>();
	entity->add<CShape>(m_enemyConfig.SR,rand_gen(m_enemyConfig.VMIN,m_enemyConfig.VMAX),sf::Color(0.0f,0.0f,0.0f),sf::Color(m_enemyConfig.OR,m_enemyConfig.OG,m_enemyConfig.OB),m_enemyConfig.OT);
	entity->add<CCollision>(m_enemyConfig.CR);


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

void Game::spawnSpecialWeapon(std::shared_ptr<Entity> entity)
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

void Game::sGUI() {
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
	player()->get<CShape>().circle.setRotation(sf::degrees(player()->get<CTransform>().angle));

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

	//sf::Event event;
	while (m_window.isOpen()/*m_window.pollEvent(event)*/) {

		while (const auto eventOpt = m_window.pollEvent())
		{
			ImGui::SFML::ProcessEvent(m_window, *eventOpt);
			if (eventOpt->is<sf::Event::Closed>())m_running = false;

			if (eventOpt->is<sf::Event::KeyPressed>())
			{
				switch (eventOpt->getIf<sf::Event::KeyPressed>()->code)
				{
				case sf::Keyboard::Key::W:
					std::cout << "W key is pressed\n";
					//Todo set player input comment up to true
					break;
				case sf::Keyboard::Key::A:
					std::cout << "A key is pressed\n";
					//todo set player input comment up to true;
					break;
				case sf::Keyboard::Key::S:
					std::cout << "S key is pressed";
					break;
				case sf::Keyboard::Key::D:
					std::cout << "D key is pressed";
					break;
				default: break;
				}

				switch (eventOpt->getIf<sf::Event::KeyReleased>()->code)
				{
				case sf::Keyboard::Key::W:
					std::cout << "W is released";
					break;
				case sf::Keyboard::Key::A:
					std::cout << "A is released";
					break;
				case sf::Keyboard::Key::S:
					std::cout << "S key is released";
					break;
				case sf::Keyboard::Key::D:
					std::cout << "D key is released";
					break;
				default:break;
				}

			}
			if (eventOpt->getIf<sf::Event::MouseButtonPressed>())
			{

				//if mouse clicked in imgui continue
				if (ImGui::GetIO().WantCaptureMouse)continue;
				if (eventOpt->getIf<sf::Event::MouseButtonPressed>()->button == sf::Mouse::Button::Left)
				{
					std::cout << "left mouse button is clicked on " << eventOpt->getIf<sf::Event::MouseButtonPressed>()->position.x << " " << eventOpt->getIf<sf::Event::MouseButtonPressed>()->position.y << " ";
					//spawn bullet here


				}
				if (eventOpt->getIf<sf::Event::MouseButtonPressed>()->button == sf::Mouse::Button::Right)
				{
					std::cout << "left mouse button is clicked on " << eventOpt->getIf<sf::Event::MouseButtonPressed>()->position.x << " " << eventOpt->getIf<sf::Event::MouseButtonPressed>()->position.y << " ";


				}
			}



			//pass the event to imgui to be parserd 

			//ImGui::SFML::ProcessEvent(m_window, event);

			//this event triggers when the window is closed

		/*	if (event.type == sf::Event::Closed) {
				m_running = false;
			}*/

			//this event is triggered when a key is pressed 
			//if (event.type == sf::Event::KeyPressed)
			//{
			//	switch (event.key.code)
			//	{
			//	case sf::Keyboard::W:
			//			std::cout << "W KEY is pressed\n";
			//			//TODO set player input component "UP" to true;
			//			break;
			//		default:break;
			//	}
			//}
			//if (event.type == sf::Event::KeyReleased)
			//{
			//	switch (event.key.code)
			//	{
			//	case sf::Keyboard::W:
			//		std::cout << "W key released\n";
			//		//Todo: set player input component  up to false
			//		break;
			//	default:break;
			//	}

		}
		//if (event.type == sf::Event::MouseButtonPressed)
		//{
		//	//this line ignores mouse events if ImGUi is the thing being clicked 
		//	if (ImGui::GetIO().WantCaptureMouse) { continue; }

		//	if (event.mouseButton.button == sf::Mouse::Left) {
		//		std::cout << "Left mouse button cliecket at " << event.mouseButton.x << ",";
		//		//call spawn Bullet here
		//	}
		//	if (event.mouseButton.button == sf::Mouse::Right)
		//	{
		//		std::cout << "Right Mouse Button CLicket at (" << event.mouseButton.x << ",";
		//	}
		//}

	}
}
