#include "LogoScene.h"

#include <Audio/AudioListener.h>
#include <Core/Time.h>
#include <Graphics/Camera.h>
#include <Graphics/UI/UIManager.h>
#include <Graphics/UI/ImageUI.h>
#include <Graphics/RenderEngine.h>

#include "Scripts/UI/LogoManager.h"

using namespace GamePackage;

LogoScene::LogoScene() : Scene(){}

LogoScene::~LogoScene(){}

bool LogoScene::Initialize(){ 

	PizzaBox::GameObject* mainCamera = CreateObject<PizzaBox::GameObject>(PizzaBox::Vector3(0.0f, 0.0f, 20.0f));
	mainCamera->AddComponent(new PizzaBox::Camera(PizzaBox::ViewportRect::fullScreen, PizzaBox::Camera::RenderMode::Perspective));
	mainCamera->AddComponent(new PizzaBox::AudioListener());  

	//UI
	PizzaBox::UIManager::EnableSet("LogoSet");

	PizzaBox::GameObject* logoManager = CreateObject<PizzaBox::GameObject>(PizzaBox::Vector3(0.0f, 0.0f, 0.0f));
	auto logoImage = PizzaBox::UIManager::GetElementFromSet<PizzaBox::ImageUI>("LogoSet", "Logo");
	logoManager->AddComponent(new LogoManager(logoImage, 5.0f, 1.0f));

	return true;
}

void LogoScene::Destroy(){
	Scene::Destroy();
}