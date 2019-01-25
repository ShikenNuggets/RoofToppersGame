#include "DefaultScene.h"

#include <Audio/AudioListener.h>
#include <Audio/AudioSource.h>
#include <Graphics/Sky/SkyBox.h>
#include <Graphics/Camera.h>
#include <Graphics/Models/MeshRender.h>
#include <Physics/Collider.h>
#include <Physics/Rigidbody.h>

#include "../Scripts/CharacterController.h"

using namespace GamePackage;

DefaultScene::DefaultScene() : Scene(){
}

DefaultScene::~DefaultScene(){
}

bool DefaultScene::Initialize(){
	SetSky(new PizzaBox::SkyBox("LakeSkybox", "SkyBoxShader", 1000.0f));

	//Create all GameObjects for this scene
	PizzaBox::GameObject* mainCamera = CreateObject<PizzaBox::GameObject>(PizzaBox::Vector3(0.0f, 0.0f, 20.0f));
	mainCamera->AddComponent(new PizzaBox::Camera(PizzaBox::ViewportRect::fullScreen, PizzaBox::Camera::RenderMode::Perspective));
	mainCamera->AddComponent(new PizzaBox::AudioListener());
	mainCamera->AddComponent(new CharacterController());

	auto dirLight = CreateObject<PizzaBox::GameObject>(PizzaBox::Vector3(), PizzaBox::Euler(-35.0f, 12.0f, 0.0f));
	dirLight->AddComponent(new PizzaBox::DirectionalLight(2.0f));

	PizzaBox::GameObject* cube = CreateObject<PizzaBox::GameObject>(PizzaBox::Vector3(0.0f, 0.0f, -20.0f));
	cube->AddComponent(new PizzaBox::MeshRender("SkullModel", "SkullTexture"));
	cube->AddComponent(new PizzaBox::Collider(cube->GetTransform()->GlobalScale()));
	auto rb = new PizzaBox::Rigidbody(1.0f, false);
	rb->Impulse(PizzaBox::Vector3(-5.0f, 0.0f, 0.0f));
	cube->AddComponent(rb);

	PizzaBox::GameObject* cubeRight = CreateObject<PizzaBox::GameObject>(PizzaBox::Vector3(10.0f, 0.0f, -20.0f), PizzaBox::Euler(), PizzaBox::Vector3(1.0f, 5.0f, 5.0f));
	cubeRight->AddComponent(new PizzaBox::MeshRender("CubeModel", "MarsTexture"));
	cubeRight->AddComponent(new PizzaBox::Collider(cubeRight->GetTransform()->GlobalScale()));
	cubeRight->AddComponent(new PizzaBox::Rigidbody(1.0f, false));

	PizzaBox::GameObject* cubeLeft = CreateObject<PizzaBox::GameObject>(PizzaBox::Vector3(-10.0f, 0.0f, -20.0f), PizzaBox::Euler(), PizzaBox::Vector3(1.0f, 5.0f, 5.0f));
	cubeLeft->AddComponent(new PizzaBox::MeshRender("CubeModel", "MarsTexture"));
	cubeLeft->AddComponent(new PizzaBox::Collider(cubeLeft->GetTransform()->GlobalScale()));
	cubeLeft->AddComponent(new PizzaBox::Rigidbody(1.0f, false));

	PizzaBox::GameObject* floor = CreateObject<PizzaBox::GameObject>(PizzaBox::Vector3(0.0f, -10.0f, 0.0f), PizzaBox::Euler(), PizzaBox::Vector3(32.0f, 0.01f, 32.0f));
	floor->AddComponent(new PizzaBox::MeshRender("CubeModel", "EarthTexture"));

	return true;
}

void DefaultScene::Destroy(){
	Scene::Destroy();
}