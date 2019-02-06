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

// Animator Includes
#include "Animators/PlayerAnimator.h"

using namespace GamePackage;

Level1::Level1() : Scene() {
}
 
Level1::~Level1() {
}

bool Level1::Initialize() {
	// SkyBox
	SetSky(new PizzaBox::SkyBox("LakeSkybox", "SkyBoxShader", 68000.0f));

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
	PizzaBox::GameObject* Player = CreateObject<PizzaBox::GameObject>(PizzaBox::Vector3(0.0f, 0.0f, 0.0f), PizzaBox::Euler(0.0f, 180.0f, 0.0f), PizzaBox::Vector3(0.1f, 0.1f, 0.1f));
	Player->SetTag("Player");
	PlayerAnimator* animator = new PlayerAnimator();
	Player->AddComponent(new PizzaBox::AnimMeshRender("BotModel", PizzaBox::Color(0.1f, 0.1f, 0.8f), animator));
	auto rb = new PizzaBox::Rigidbody(10000.0f, true, true);
	rb->AddCollider(new PizzaBox::CapsuleCollider(5.0f, 10.0f), PizzaBox::Vector3(0.0f, 10.0f, 0.0f));
	Player->AddComponent(rb);
	Player->AddComponent(new PlayerController(cam, animator));

	// Test Static platfrom
	PizzaBox::GameObject* Platfrom = CreateObject<PizzaBox::GameObject>(PizzaBox::Vector3(0.0f, -5.0f, 0.0f), PizzaBox::Euler(), PizzaBox::Vector3(20.0f, 2.0f, 20.0f));
	Platfrom->AddComponent(new PizzaBox::MeshRender("CubeModel", new PizzaBox::ColorMaterial(PizzaBox::Color::Green)));
	Platfrom->AddComponent(new PizzaBox::Collider(Platfrom->GetTransform()->GlobalScale()));

	// Test Moving Platform


	// Test Death Object


	// Test Disappearing platfrom


	return true;
}

void Level1::Destroy() {

}
