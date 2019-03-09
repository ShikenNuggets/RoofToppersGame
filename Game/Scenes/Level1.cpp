#include "Level1.h"

// Engine Includes 
#include <Animation/AnimMeshRender.h> 
#include <Graphics/Sky/SkyBox.h>
#include <Graphics/Camera.h>
#include <Graphics/Models/MeshRender.h>
#include <Graphics/Materials/ColorMaterial.h>
#include <Physics/Collider.h>
#include <Physics/Rigidbody.h>
//#include <Audio/AudioListener.h>
//#include <Audio/AudioSource.h>

// Script Includes
#include "Scripts/CameraController.h"
#include "Scripts/PlayerController.h"
#include "Scripts/MovingPlatform.h"

// Animator Includes
#include "Animators/PlayerAnimator.h"

using namespace GamePackage;

Level1::Level1() : Scene() {
}
 
Level1::~Level1() {
}

bool Level1::Initialize() {
	// SkyBox
	SetSky(new PizzaBox::SkyBox("CloudSkybox", "SkyBoxShader", 68000.0f));

	// Camera
	PizzaBox::GameObject* mainCamera = CreateObject<PizzaBox::GameObject>(PizzaBox::Vector3(0.0f, 55.0f, 80.0f), PizzaBox::Euler(-15.0f, 0.0f, 0.0f));
	auto cam = new PizzaBox::Camera(PizzaBox::ViewportRect::fullScreen, PizzaBox::Camera::RenderMode::Perspective);
	mainCamera->AddComponent(cam); 
	mainCamera->AddComponent(new CameraController());
	//mainCamera->AddComponent(new PizzaBox::AudioListener());
	//mainCamera->AddComponent(new PizzaBox::AudioSource("GameplayMusic", PizzaBox::AudioSource::SoundType::_2D, "Music"));

	// Directional Light
	auto dirLight = CreateObject<PizzaBox::GameObject>(PizzaBox::Vector3(), PizzaBox::Euler(-35.0f, 12.0f, 0.0f));
	dirLight->AddComponent(new PizzaBox::DirectionalLight(2.0f));

	// Player 
	PizzaBox::GameObject* Player = CreateObject<PizzaBox::GameObject>(PizzaBox::Vector3(0.0f, 10.0f, 0.0f), PizzaBox::Euler(0.0f, 180.0f, 0.0f), PizzaBox::Vector3(0.1f, 0.1f, 0.1f));
	Player->SetTag("Player");
	PlayerAnimator* animator = new PlayerAnimator();
	Player->AddComponent(new PizzaBox::AnimMeshRender("BotModel", PizzaBox::Color(0.1f, 0.1f, 0.8f), animator));
	auto rb = new PizzaBox::Rigidbody(80.0f, true, true);
	rb->SetMaterial(PizzaBox::PhysicsMaterial(0.0f, 0.0f));
	rb->AddCollider(new PizzaBox::CapsuleCollider(5.0f, 10.0f), PizzaBox::Vector3(0.0f, 10.0f, 0.0f));
	Player->AddComponent(rb);
	Player->AddComponent(new PlayerController(cam, animator));

	// Test Static platfrom
	PizzaBox::GameObject* platform = CreateObject<PizzaBox::GameObject>(PizzaBox::Vector3(0.0f, -5.0f, 0.0f), PizzaBox::Euler(), PizzaBox::Vector3(50.0f, 2.0f, 50.0f));
	platform->SetTag("Platform");
	platform->AddComponent(new PizzaBox::MeshRender("CubeModel", new PizzaBox::ColorMaterial(PizzaBox::Color::Green)));
	//platform->AddComponent(new PizzaBox::Collider(platform->GetTransform()->GlobalScale())); 
	auto rb2 = new PizzaBox::Rigidbody(1.0f, false, true);
	rb2->SetMaterial(PizzaBox::PhysicsMaterial(0.0f, 0.0f));
	rb2->AddCollider(new PizzaBox::BoxCollider(platform->GetScale()));
	platform->AddComponent(rb2);
	platform->SetStatic(true);

	// Test Moving Platform
	PizzaBox::GameObject* platform2 = CreateObject<PizzaBox::GameObject>(PizzaBox::Vector3(0.0f, 10.0f, -100.0f), PizzaBox::Euler(), PizzaBox::Vector3(10.0f, 2.0f, 10.0f));
	platform2->SetTag("Platform");
	platform2->AddComponent(new PizzaBox::MeshRender("CubeModel", new PizzaBox::ColorMaterial(PizzaBox::Color::Red)));
	//platform2->AddComponent(new PizzaBox::Collider(platform2->GetTransform()->GlobalScale()));
	auto mp = new MovingPlatform();
	mp->SetDistance(5.0f);
	mp->SetDirectionSpeed(10.0f);
	platform2->AddComponent(mp); 
	auto rb3 = new PizzaBox::Rigidbody(1.0f, false, true);
	rb3->SetMaterial(PizzaBox::PhysicsMaterial(0.0f, 0.0f));
	rb3->AddCollider(new PizzaBox::BoxCollider(platform2->GetScale()));
	platform2->AddComponent(rb3);
	platform2->SetStatic(true);

	// Test Death Object


	// Test Disappearing platfrom


	return true;
}

void Level1::Destroy() {
	Scene::Destroy();
}
