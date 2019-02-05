#include "Game.h" 
#include "Scenes/LogoScene.h"
#include "Scenes/MainMenuScene.h"
#include <Core/SceneManager.h>
#include <Input/InputManager.h>

using namespace GamePackage;

Game::Game(const std::string name_) : GameInterface(name_){
}

Game::~Game(){
}

bool Game::Initialize(){
	//Add scenes to the SceneManager

	PizzaBox::SceneManager::AddScene(new LogoScene());
	PizzaBox::SceneManager::AddScene(new MainMenuScene());

	return true;
}

void Game::Destroy(){
}