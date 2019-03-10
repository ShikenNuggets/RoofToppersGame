#include "Level1.h"

// Engine Includes 
#include <Animation/AnimMeshRender.h> 
#include <Graphics/Sky/SkyBox.h>
#include <Graphics/Camera.h>
#include <Graphics/Models/MeshRender.h>
#include <Graphics/Materials/ColorMaterial.h>
#include <Graphics/Materials/TexturedMaterial.h>
#include <Physics/Collider.h>
#include <Physics/Rigidbody.h>
//#include <Audio/AudioListener.h>
//#include <Audio/AudioSource.h>

// Script Includes


#include "../Scripts/CharacterController.h"

#include "Scripts/CameraController.h"
#include "Scripts/PlayerController.h"
#include "Scripts/MovingPlatform.h"
#include <Graphics/Materials/WaterMaterial.h>
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
	mainCamera->AddComponent(new CharacterController());
	//mainCamera->AddComponent(new PizzaBox::AudioListener());
	//mainCamera->AddComponent(new PizzaBox::AudioSource("GameplayMusic", PizzaBox::AudioSource::SoundType::_2D, "Music"));

	// Directional Light
	auto dirLight = CreateObject<PizzaBox::GameObject>(PizzaBox::Vector3(), PizzaBox::Euler(-35.0f, 12.0f, 0.0f));
	dirLight->AddComponent(new PizzaBox::DirectionalLight(2.0f));

	// Player 
	/**
	PizzaBox::GameObject* Player = CreateObject<PizzaBox::GameObject>(PizzaBox::Vector3(0.0f, 10.0f, 0.0f), PizzaBox::Euler(0.0f, 180.0f, 0.0f), PizzaBox::Vector3(0.1f, 0.1f, 0.1f));
	Player->SetTag("Player");
	PlayerAnimator* animator = new PlayerAnimator();
	Player->AddComponent(new PizzaBox::AnimMeshRender("BotModel", PizzaBox::Color(0.1f, 0.1f, 0.8f), animator));
	auto rb = new PizzaBox::Rigidbody(80.0f, true, true);
	rb->SetMaterial(PizzaBox::PhysicsMaterial(0.0f, 0.0f));
	rb->AddCollider(new PizzaBox::CapsuleCollider(5.0f, 10.0f), PizzaBox::Vector3(0.0f, 10.0f, 0.0f));
	Player->AddComponent(rb);
	Player->AddComponent(new PlayerController(cam, animator));
	*/
	// Platform Level
	PizzaBox::GameObject* platform = CreateObject<PizzaBox::GameObject>(PizzaBox::Vector3(0.0f, -5.0f, 0.0f), PizzaBox::Euler(), PizzaBox::Vector3(50.0f, 50.0f, 50.0f));
	platform->SetTag("Platform");
	auto texMat = new PizzaBox::TexturedMaterial("ConcreteTexture", false, "", "", 32.0f, 20.0f);
	platform->AddComponent(new PizzaBox::MeshRender("CubeModel", texMat));
	//platform->AddComponent(new PizzaBox::Collider(platform->GetTransform()->GlobalScale())); 
	auto rb2 = new PizzaBox::Rigidbody(1.0f, false, true);
	rb2->SetMaterial(PizzaBox::PhysicsMaterial(0.0f, 0.0f));
	rb2->AddCollider(new PizzaBox::BoxCollider(platform->GetScale()));
	platform->AddComponent(rb2);
	platform->SetStatic(true);

	PizzaBox::GameObject* platform2 = CreateObject<PizzaBox::GameObject>(PizzaBox::Vector3(0.0f, 40.0f, -150.0f), PizzaBox::Euler(), PizzaBox::Vector3(30.0f, 2.0f, 30.0f));
	platform2->SetTag("Platform");
	platform2->AddComponent(new PizzaBox::MeshRender("CubeModel", new PizzaBox::ColorMaterial(PizzaBox::Color::Red)));
	//platform2->AddComponent(new PizzaBox::Collider(platform2->GetTransform()->GlobalScale()));
	auto rb3 = new PizzaBox::Rigidbody(1.0f, false, true);
	rb3->SetMaterial(PizzaBox::PhysicsMaterial(0.0f, 0.0f));
	rb3->AddCollider(new PizzaBox::BoxCollider(platform2->GetScale()));
	platform2->AddComponent(rb3);
	platform2->SetStatic(true);

	PizzaBox::GameObject* platform3 = CreateObject<PizzaBox::GameObject>(PizzaBox::Vector3(0.0f, -5.0f, -300.0f), PizzaBox::Euler(), PizzaBox::Vector3(50.0f, 50.0f, 50.0f));
	platform3->SetTag("Platform");
	texMat = new PizzaBox::TexturedMaterial("ConcreteTexture", false, "", "", 32.0f, 20.0f);
	platform3->AddComponent(new PizzaBox::MeshRender("CubeModel", texMat));
	//platform->AddComponent(new PizzaBox::Collider(platform->GetTransform()->GlobalScale())); 
	auto rb4 = new PizzaBox::Rigidbody(1.0f, false, true);
	rb4->SetMaterial(PizzaBox::PhysicsMaterial(0.0f, 0.0f));
	rb4->AddCollider(new PizzaBox::BoxCollider(platform3->GetScale()));
	platform3->AddComponent(rb4);
	platform3->SetStatic(true);

	PizzaBox::GameObject* platform4 = CreateObject<PizzaBox::GameObject>(PizzaBox::Vector3(0.0f, 40.0f, -350.0f), PizzaBox::Euler(), PizzaBox::Vector3(30.0f, 2.0f, 80.0f));
	platform4->SetTag("Platform");
	platform4->AddComponent(new PizzaBox::MeshRender("CubeModel", new PizzaBox::ColorMaterial(PizzaBox::Color::Red)));
	//platform2->AddComponent(new PizzaBox::Collider(platform2->GetTransform()->GlobalScale()));
	auto rb5 = new PizzaBox::Rigidbody(1.0f, false, true);
	rb5->SetMaterial(PizzaBox::PhysicsMaterial(0.0f, 0.0f));
	rb5->AddCollider(new PizzaBox::BoxCollider(platform4->GetScale()));
	platform4->AddComponent(rb5);
	platform4->SetStatic(true);

	PizzaBox::GameObject* platform5 = CreateObject<PizzaBox::GameObject>(PizzaBox::Vector3(0.0f, -5.0f, -450.0f), PizzaBox::Euler(-25.0f), PizzaBox::Vector3(50.0f, 50.0f, 50.0f));
	platform5->SetTag("Platform");
	texMat = new PizzaBox::TexturedMaterial("ConcreteTexture", false, "", "", 32.0f, 20.0f);
	platform5->AddComponent(new PizzaBox::MeshRender("CubeModel", texMat));
	//platform->AddComponent(new PizzaBox::Collider(platform->GetTransform()->GlobalScale())); 
	auto rb6 = new PizzaBox::Rigidbody(1.0f, false, true);
	rb6->SetMaterial(PizzaBox::PhysicsMaterial(0.0f, 0.0f));
	rb6->AddCollider(new PizzaBox::BoxCollider(platform5->GetScale()));
	platform5->AddComponent(rb6);
	platform5->SetStatic(true);

	PizzaBox::GameObject* platform6 = CreateObject<PizzaBox::GameObject>(PizzaBox::Vector3(0.0f, 40.0f, -535.0f), PizzaBox::Euler(), PizzaBox::Vector3(20.0f, 2.0f, 20.0f));
	platform6->SetTag("Platform");
	platform6->AddComponent(new PizzaBox::MeshRender("CubeModel", new PizzaBox::ColorMaterial(PizzaBox::Color::Red)));
	//platform2->AddComponent(new PizzaBox::Collider(platform2->GetTransform()->GlobalScale()));
	auto rb7 = new PizzaBox::Rigidbody(1.0f, false, true);
	rb7->SetMaterial(PizzaBox::PhysicsMaterial(0.0f, 0.0f));
	rb7->AddCollider(new PizzaBox::BoxCollider(platform6->GetScale()));
	platform6->AddComponent(rb7);
	platform6->SetStatic(true);

	PizzaBox::GameObject* platform7 = CreateObject<PizzaBox::GameObject>(PizzaBox::Vector3(0.0f, 60.0f, -620.0f), PizzaBox::Euler(), PizzaBox::Vector3(10.0f, 2.0f, 20.0f));
	platform7->SetTag("Platform");
	platform7->AddComponent(new PizzaBox::MeshRender("CubeModel", new PizzaBox::ColorMaterial(PizzaBox::Color::Red)));
	//platform2->AddComponent(new PizzaBox::Collider(platform2->GetTransform()->GlobalScale()));
	auto rb8 = new PizzaBox::Rigidbody(1.0f, false, true);
	rb8->SetMaterial(PizzaBox::PhysicsMaterial(0.0f, 0.0f));
	rb8->AddCollider(new PizzaBox::BoxCollider(platform7->GetScale()));
	platform7->AddComponent(rb8);
	platform7->SetStatic(true);

	PizzaBox::GameObject* platform8 = CreateObject<PizzaBox::GameObject>(PizzaBox::Vector3(0.0f, -5.0f, -780.0f), PizzaBox::Euler(), PizzaBox::Vector3(50.0f, 150.0f, 50.0f));
	platform8->SetTag("Platform");
	texMat = new PizzaBox::TexturedMaterial("ConcreteTexture", false, "", "", 32.0f, 20.0f);
	platform8->AddComponent(new PizzaBox::MeshRender("CubeModel", texMat));
	//platform->AddComponent(new PizzaBox::Collider(platform->GetTransform()->GlobalScale())); 
	auto rb9 = new PizzaBox::Rigidbody(1.0f, false, true);
	rb9->SetMaterial(PizzaBox::PhysicsMaterial(0.0f, 0.0f));
	rb9->AddCollider(new PizzaBox::BoxCollider(platform8->GetScale()));
	platform8->AddComponent(rb9);
	platform8->SetStatic(true);

	PizzaBox::GameObject* platform9 = CreateObject<PizzaBox::GameObject>(PizzaBox::Vector3(0.0f, 45.0f, -780.0f), PizzaBox::Euler(), PizzaBox::Vector3(80.0f, 5.0f, 80.0f));
	platform9->SetTag("Platform");
	platform9->AddComponent(new PizzaBox::MeshRender("CubeModel", new PizzaBox::ColorMaterial(PizzaBox::Color::Red)));
	//platform->AddComponent(new PizzaBox::Collider(platform->GetTransform()->GlobalScale())); 
	auto rb10 = new PizzaBox::Rigidbody(1.0f, false, true);
	rb10->SetMaterial(PizzaBox::PhysicsMaterial(0.0f, 0.0f));
	rb10->AddCollider(new PizzaBox::BoxCollider(platform9->GetScale()));
	platform9->AddComponent(rb10);
	platform9->SetStatic(true);


	//Grapple Points

	PizzaBox::GameObject* grapplePoint1 = CreateObject<PizzaBox::GameObject>(PizzaBox::Vector3(0.0f, 80.0f, -80.0f), PizzaBox::Euler(), PizzaBox::Vector3(2.0f, 2.0f, 2.0f));
	grapplePoint1->AddComponent(new PizzaBox::MeshRender("SphereModel", new PizzaBox::ColorMaterial(PizzaBox::Color::Yellow)));
		auto child = CreateObject<PizzaBox::GameObject>(grapplePoint1, PizzaBox::Vector3(0.0f, -3.5f, 0.0f));
		child->AddComponent(new PizzaBox::PointLight(1.0f, PizzaBox::Color::Yellow, 5.0f));

	PizzaBox::GameObject* grapplePoint2 = CreateObject<PizzaBox::GameObject>(PizzaBox::Vector3(0.0f, 80.0f, -200.0f), PizzaBox::Euler(), PizzaBox::Vector3(2.0f, 2.0f, 2.0f));
	grapplePoint2->AddComponent(new PizzaBox::MeshRender("SphereModel", new PizzaBox::ColorMaterial(PizzaBox::Color::Yellow)));
		child = CreateObject<PizzaBox::GameObject>(grapplePoint2, PizzaBox::Vector3(0.0f, -3.5f, 0.0f));
		child->AddComponent(new PizzaBox::PointLight(1.0f, PizzaBox::Color::Yellow, 5.0f));

	PizzaBox::GameObject* grapplePoint3 = CreateObject<PizzaBox::GameObject>(PizzaBox::Vector3(0.0f, 80.0f, -380.0f), PizzaBox::Euler(), PizzaBox::Vector3(2.0f, 2.0f, 2.0f));
	grapplePoint3->AddComponent(new PizzaBox::MeshRender("SphereModel", new PizzaBox::ColorMaterial(PizzaBox::Color::Yellow)));
		child = CreateObject<PizzaBox::GameObject>(grapplePoint3, PizzaBox::Vector3(0.0f, -3.5f, 0.0f));
		child->AddComponent(new PizzaBox::PointLight(1.0f, PizzaBox::Color::Yellow, 5.0f));

	PizzaBox::GameObject* grapplePoint4 = CreateObject<PizzaBox::GameObject>(PizzaBox::Vector3(0.0f, 80.0f, -470.0f), PizzaBox::Euler(), PizzaBox::Vector3(2.0f, 2.0f, 2.0f));
	grapplePoint4->AddComponent(new PizzaBox::MeshRender("SphereModel", new PizzaBox::ColorMaterial(PizzaBox::Color::Yellow)));
		child = CreateObject<PizzaBox::GameObject>(grapplePoint4, PizzaBox::Vector3(0.0f, -3.5f, 0.0f));
		child->AddComponent(new PizzaBox::PointLight(1.0f, PizzaBox::Color::Yellow, 5.0f));

	PizzaBox::GameObject* grapplePoint5 = CreateObject<PizzaBox::GameObject>(PizzaBox::Vector3(0.0f, 80.0f, -560.0f), PizzaBox::Euler(), PizzaBox::Vector3(2.0f, 2.0f, 2.0f));
	grapplePoint5->AddComponent(new PizzaBox::MeshRender("SphereModel", new PizzaBox::ColorMaterial(PizzaBox::Color::Yellow)));
		child = CreateObject<PizzaBox::GameObject>(grapplePoint5, PizzaBox::Vector3(0.0f, -3.5f, 0.0f));
		child->AddComponent(new PizzaBox::PointLight(1.0f, PizzaBox::Color::Yellow, 5.0f));

	PizzaBox::GameObject* grapplePoint6 = CreateObject<PizzaBox::GameObject>(PizzaBox::Vector3(0.0f, 100.0f, -660.0f), PizzaBox::Euler(), PizzaBox::Vector3(2.0f, 2.0f, 2.0f));
	grapplePoint6->AddComponent(new PizzaBox::MeshRender("SphereModel", new PizzaBox::ColorMaterial(PizzaBox::Color::Yellow)));
		child = CreateObject<PizzaBox::GameObject>(grapplePoint6, PizzaBox::Vector3(0.0f, -3.5f, 0.0f));
		child->AddComponent(new PizzaBox::PointLight(1.0f, PizzaBox::Color::Yellow, 5.0f));

	// Test Water Object
	PizzaBox::GameObject* baseWater = CreateObject<PizzaBox::GameObject>(PizzaBox::Vector3(0.0f, 0.0f, 0.0f), PizzaBox::Euler(), PizzaBox::Vector3(70.0f, 20.0f, 70.0f));
	auto water = new PizzaBox::WaterMaterial("WaterTexture","","",32.0f,60.0f);
	water->SetWaveParamaters(PizzaBox::Vector4(2.0f, 4.0f, 4.0f, 2.0f), PizzaBox::Vector4(0.8f, 0.2f, 0.2f, 0.2f), PizzaBox::Vector4(0.4f, 0.4f, 0.4f, 0.2f));
	baseWater->AddComponent(new PizzaBox::MeshRender("WaterMesh", water));


	// Background Design

	int backgroundbuildingCount = 30;
	for (int i = 0; i < 30; i++) {
		PizzaBox::GameObject* backgroundHouse1 = CreateObject<PizzaBox::GameObject>(PizzaBox::Vector3(-400.0f, -5.0f, 400.0f - (i * 250)), PizzaBox::Euler(), PizzaBox::Vector3(50.0f, 150.0f, 50.0f));
		texMat = new PizzaBox::TexturedMaterial("ConcreteTexture", false, "", "", 32.0f, 20.0f);
		backgroundHouse1->AddComponent(new PizzaBox::MeshRender("CubeModel", texMat));
		//platform->AddComponent(new PizzaBox::Collider(platform->GetTransform()->GlobalScale())); 
	}

	for (int i = 0; i < 30; i++) {
		PizzaBox::GameObject* backgroundHouse2 = CreateObject<PizzaBox::GameObject>(PizzaBox::Vector3(400.0f, -5.0f, 400.0f - (i * 250)), PizzaBox::Euler(), PizzaBox::Vector3(50.0f, 150.0f, 50.0f));
		texMat = new PizzaBox::TexturedMaterial("ConcreteTexture", false, "", "", 32.0f, 20.0f);
		backgroundHouse2->AddComponent(new PizzaBox::MeshRender("CubeModel", texMat));
		//platform->AddComponent(new PizzaBox::Collider(platform->GetTransform()->GlobalScale())); 
	}



	return true;
}

void Level1::Destroy() {
	Scene::Destroy();
}
