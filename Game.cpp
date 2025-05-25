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

	}
}