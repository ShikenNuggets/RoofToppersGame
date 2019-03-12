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
#include <Audio/AudioListener.h>
#include <Audio/AudioSource.h>

// Script Includes


#include "../Scripts/CharacterController.h"
#include "Scripts/MusicScript.h"
#include "Scripts/CameraController.h"
#include "Scripts/GrapplePoint.h"
#include "Scripts/PlayerController.h"
#include "Scripts/MovingPlatform.h"
#include <Graphics/Materials/WaterMaterial.h>
#include <Graphics/Materials/ReflectiveMaterial.h>
// Animator Includes
#include "Animators/PlayerAnimator.h"

using namespace GamePackage;

Level1::Level1() : Scene() {
}
 
Level1::~Level1() {
}

bool Level1::Initialize() {
	//SkyBox
	SetSky(new PizzaBox::SkyBox("LakeSkybox", "SkyBoxShader", 68000.0f));
	//Music
	auto gpm1 = new PizzaBox::AudioSource("GameplayMusic1", PizzaBox::AudioSource::SoundType::_2D, "Music");
	PizzaBox::GameObject* music = CreateObject<PizzaBox::GameObject>(PizzaBox::Vector3(0.0f, 55.0f, 80.0f), PizzaBox::Euler(-15.0f, 0.0f, 0.0f));
	music->AddComponent(gpm1);
	music->AddComponent(new MusicScript(gpm1));

	//Waves
	auto wve1 = new PizzaBox::AudioSource("WavesSFX", PizzaBox::AudioSource::SoundType::_2D, "SFX");
	PizzaBox::GameObject* waves = CreateObject<PizzaBox::GameObject>(PizzaBox::Vector3(0.0f, 55.0f, 80.0f), PizzaBox::Euler(-15.0f, 0.0f, 0.0f));
	waves->AddComponent(wve1);
	waves->AddComponent(new MusicScript(wve1));

	//Camera
	PizzaBox::GameObject* mainCamera = CreateObject<PizzaBox::GameObject>(PizzaBox::Vector3(0.0f, 55.0f, 80.0f), PizzaBox::Euler(-15.0f, 0.0f, 0.0f));
	auto cam = new PizzaBox::Camera(PizzaBox::ViewportRect::fullScreen, PizzaBox::Camera::RenderMode::Perspective);
	mainCamera->AddComponent(cam);
	auto controller = new CameraController();
	mainCamera->AddComponent(controller);
	mainCamera->AddComponent(new PizzaBox::AudioListener());
	


	//mainCamera->AddComponent(new MusicScript(as1));

	//Directional Light
	auto dirLight = CreateObject<PizzaBox::GameObject>(PizzaBox::Vector3(), PizzaBox::Euler(-35.0f, 12.0f, 0.0f));
	dirLight->AddComponent(new PizzaBox::DirectionalLight(2.0f));

	//Player 
	PizzaBox::GameObject* Player = CreateObject<PizzaBox::GameObject>(PizzaBox::Vector3(0.0f, 60.0f, 0.0f), PizzaBox::Euler(0.0f, 180.0f, 0.0f), PizzaBox::Vector3(0.01f, 0.01f, 0.01f));
	Player->SetTag("Player");
	PlayerAnimator* animator = new PlayerAnimator();
	std::vector<PizzaBox::MeshMaterial*> materials;
	materials.push_back(new PizzaBox::TexturedMaterial("RemyBody", true));
	materials.push_back(new PizzaBox::TexturedMaterial("RemyBody", true));
	materials.push_back(new PizzaBox::TexturedMaterial("RemyBody", true));
	materials.push_back(new PizzaBox::TexturedMaterial("RemyHair", true));
	materials.push_back(new PizzaBox::TexturedMaterial("RemyBottom", true));
	materials.push_back(new PizzaBox::TexturedMaterial("RemyTop", true));
	materials.push_back(new PizzaBox::TexturedMaterial("RemyShoes", true));
	Player->AddComponent(new PizzaBox::AnimMeshRender("DudeModel", materials, animator));
	auto rb = new PizzaBox::Rigidbody(80.0f, true, true);
	rb->SetMaterial(PizzaBox::PhysicsMaterial(0.0f, 0.0f));
	rb->AddCollider(new PizzaBox::CapsuleCollider(5.0f, 10.0f), PizzaBox::Vector3(0.0f, 10.0f, 0.0f));

	auto grappleSFX = new PizzaBox::AudioSource("GrappleSFX", PizzaBox::AudioSource::SoundType::_2D, "SFX");
	auto jumpSFX = new PizzaBox::AudioSource("JumpingSFX", PizzaBox::AudioSource::SoundType::_2D, "SFX");
	auto walkSFX = new PizzaBox::AudioSource("WalkingSFX", PizzaBox::AudioSource::SoundType::_2D, "SFX");
	auto landingSFX = new PizzaBox::AudioSource("LandingSFX", PizzaBox::AudioSource::SoundType::_2D, "SFX");
	auto swingingSFX = new PizzaBox::AudioSource("SwingingSFX", PizzaBox::AudioSource::SoundType::_2D, "SFX");

	Player->AddComponent(rb);
	Player->AddComponent(grappleSFX);
	Player->AddComponent(jumpSFX);
	Player->AddComponent(walkSFX);
	Player->AddComponent(landingSFX);
	Player->AddComponent(swingingSFX);
	Player->AddComponent(new PlayerController(cam, animator,walkSFX,grappleSFX,jumpSFX,landingSFX,swingingSFX));
	
	controller->SetTarget(Player);

	//Grapple Point
	//auto grapplePoint = CreateObject<PizzaBox::GameObject>(PizzaBox::Vector3(0.0f, 50.0f, -50.0f), PizzaBox::Euler(), PizzaBox::Vector3::Fill(2.0f));
	//grapplePoint->AddComponent(new PizzaBox::MeshRender("SphereModel", new PizzaBox::ColorMaterial(PizzaBox::Color::Yellow)));
	//grapplePoint->AddComponent(new GrapplePoint(35.0f));

	//Test Static platfrom
	PizzaBox::GameObject* platform = CreateObject<PizzaBox::GameObject>(PizzaBox::Vector3(0.0f, -5.0f, 0.0f), PizzaBox::Euler(), PizzaBox::Vector3(20.0f, 100.0f, 20.0f));
	platform->SetTag("Platform");
	auto texMat = new PizzaBox::TexturedMaterial("ConcreteTexture", false, "", "", 32.0f, 20.0f);
	platform->AddComponent(new PizzaBox::MeshRender("CubeModel", texMat));
	//platform->AddComponent(new PizzaBox::Collider(platform->GetTransform()->GlobalScale())); 
	auto rb2 = new PizzaBox::Rigidbody(1.0f, false, true);
	rb2->SetMaterial(PizzaBox::PhysicsMaterial(0.0f, 0.0f));
	rb2->AddCollider(new PizzaBox::BoxCollider(platform->GetScale()));
	platform->AddComponent(rb2);
	platform->SetStatic(true);

	PizzaBox::GameObject* platform2 = CreateObject<PizzaBox::GameObject>(PizzaBox::Vector3(0.0f, 40.0f, -60.0f), PizzaBox::Euler(), PizzaBox::Vector3(12.0f, 4.0f, 12.0f));
	platform2->SetTag("Platform");
	auto platformTexMat = new PizzaBox::TexturedMaterial("HazardTexture", false, "", "", 32.0f, 10.0f);
	platform2->AddComponent(new PizzaBox::MeshRender("CubeModel", platformTexMat));
	//platform2->AddComponent(new PizzaBox::Collider(platform2->GetTransform()->GlobalScale()));
	auto rb3 = new PizzaBox::Rigidbody(1.0f, false, true);
	rb3->SetMaterial(PizzaBox::PhysicsMaterial(0.0f, 0.0f));
	rb3->AddCollider(new PizzaBox::BoxCollider(platform2->GetScale()));
	platform2->AddComponent(rb3);
	platform2->SetStatic(true);

	PizzaBox::GameObject* platform3 = CreateObject<PizzaBox::GameObject>(PizzaBox::Vector3(0.0f, -5.0f, -120.0f), PizzaBox::Euler(), PizzaBox::Vector3(20.0f, 100.0f, 20.0f));
	platform3->SetTag("Platform");
	texMat = new PizzaBox::TexturedMaterial("ConcreteTexture", false, "", "", 32.0f, 20.0f);
	platform3->AddComponent(new PizzaBox::MeshRender("CubeModel", texMat));
	//platform->AddComponent(new PizzaBox::Collider(platform->GetTransform()->GlobalScale())); 
	auto rb4 = new PizzaBox::Rigidbody(1.0f, false, true);
	rb4->SetMaterial(PizzaBox::PhysicsMaterial(0.0f, 0.0f));
	rb4->AddCollider(new PizzaBox::BoxCollider(platform3->GetScale()));
	platform3->AddComponent(rb4);
	platform3->SetStatic(true);

	PizzaBox::GameObject* platform4 = CreateObject<PizzaBox::GameObject>(PizzaBox::Vector3(0.0f, 40.0f, -170.0f), PizzaBox::Euler(), PizzaBox::Vector3(12.0f, 4.0f, 32.0f));
	platform4->SetTag("Platform");
	platformTexMat = new PizzaBox::TexturedMaterial("HazardTexture", false, "", "", 32.0f, 30.0f);
	platform4->AddComponent(new PizzaBox::MeshRender("CubeModel", platformTexMat));
	//platform2->AddComponent(new PizzaBox::Collider(platform2->GetTransform()->GlobalScale()));
	auto rb5 = new PizzaBox::Rigidbody(1.0f, false, true);
	rb5->SetMaterial(PizzaBox::PhysicsMaterial(0.0f, 0.0f));
	rb5->AddCollider(new PizzaBox::BoxCollider(platform4->GetScale()));
	platform4->AddComponent(rb5);
	platform4->SetStatic(true);

	PizzaBox::GameObject* platform5 = CreateObject<PizzaBox::GameObject>(PizzaBox::Vector3(0.0f, -5.0f, -270.0f), PizzaBox::Euler(/*-25.0f*/), PizzaBox::Vector3(20.0f, 100.0f, 20.0f));
	platform5->SetTag("Platform");
	texMat = new PizzaBox::TexturedMaterial("ConcreteTexture", false, "", "", 32.0f, 20.0f);
	platform5->AddComponent(new PizzaBox::MeshRender("CubeModel", texMat));
	//platform->AddComponent(new PizzaBox::Collider(platform->GetTransform()->GlobalScale())); 
	auto rb6 = new PizzaBox::Rigidbody(1.0f, false, true);
	rb6->SetMaterial(PizzaBox::PhysicsMaterial(0.0f, 0.0f));
	rb6->AddCollider(new PizzaBox::BoxCollider(platform5->GetScale()));
	platform5->AddComponent(rb6);
	platform5->SetStatic(true);

	PizzaBox::GameObject* platform6 = CreateObject<PizzaBox::GameObject>(PizzaBox::Vector3(0.0f, 40.0f, -355.0f), PizzaBox::Euler(), PizzaBox::Vector3(8.0f, 4.0f, 8.0f));
	platform6->SetTag("Platform");
	platformTexMat = new PizzaBox::TexturedMaterial("HazardTexture", false, "", "", 32.0f, 5.0f);
	platform6->AddComponent(new PizzaBox::MeshRender("CubeModel", platformTexMat));
	//platform2->AddComponent(new PizzaBox::Collider(platform2->GetTransform()->GlobalScale()));
	auto rb7 = new PizzaBox::Rigidbody(1.0f, false, true);
	rb7->SetMaterial(PizzaBox::PhysicsMaterial(0.0f, 0.0f));
	rb7->AddCollider(new PizzaBox::BoxCollider(platform6->GetScale()));
	platform6->AddComponent(rb7);
	platform6->SetStatic(true);

	PizzaBox::GameObject* platform7 = CreateObject<PizzaBox::GameObject>(PizzaBox::Vector3(0.0f, 60.0f, -440.0f), PizzaBox::Euler(), PizzaBox::Vector3(4.0f, 4.0f, 8.0f));
	platform7->SetTag("Platform");
	platformTexMat = new PizzaBox::TexturedMaterial("HazardTexture", false, "", "", 32.0f, 5.0f);
	platform7->AddComponent(new PizzaBox::MeshRender("CubeModel", platformTexMat));
	//platform2->AddComponent(new PizzaBox::Collider(platform2->GetTransform()->GlobalScale()));
	auto rb8 = new PizzaBox::Rigidbody(1.0f, false, true);
	rb8->SetMaterial(PizzaBox::PhysicsMaterial(0.0f, 0.0f));
	rb8->AddCollider(new PizzaBox::BoxCollider(platform7->GetScale()));
	platform7->AddComponent(rb8);
	platform7->SetStatic(true);

	PizzaBox::GameObject* platform8 = CreateObject<PizzaBox::GameObject>(PizzaBox::Vector3(0.0f, -5.0f, -600.0f), PizzaBox::Euler(), PizzaBox::Vector3(20.0f, 300.0f, 20.0f));
	platform8->SetTag("Platform");
	texMat = new PizzaBox::TexturedMaterial("ConcreteTexture", false, "", "", 32.0f, 20.0f);
	platform8->AddComponent(new PizzaBox::MeshRender("CubeModel", texMat));
	//platform->AddComponent(new PizzaBox::Collider(platform->GetTransform()->GlobalScale())); 
	auto rb9 = new PizzaBox::Rigidbody(1.0f, false, true);
	rb9->SetMaterial(PizzaBox::PhysicsMaterial(0.0f, 0.0f));
	rb9->AddCollider(new PizzaBox::BoxCollider(platform8->GetScale()));
	platform8->AddComponent(rb9);
	platform8->SetStatic(true);

	PizzaBox::GameObject* platform9 = CreateObject<PizzaBox::GameObject>(PizzaBox::Vector3(0.0f, 45.0f, -600.0f), PizzaBox::Euler(), PizzaBox::Vector3(32.0f, 10.0f, 32.0f));
	platform9->SetTag("Platform");
	platformTexMat = new PizzaBox::TexturedMaterial("HazardTexture", false, "", "", 32.0f, 5.0f);
	platform9->AddComponent(new PizzaBox::MeshRender("CubeModel", platformTexMat));
	//platform->AddComponent(new PizzaBox::Collider(platform->GetTransform()->GlobalScale())); 
	auto rb10 = new PizzaBox::Rigidbody(1.0f, false, true);
	rb10->SetMaterial(PizzaBox::PhysicsMaterial(0.0f, 0.0f));
	rb10->AddCollider(new PizzaBox::BoxCollider(platform9->GetScale()));
	platform9->AddComponent(rb10);
	platform9->SetStatic(true);


	//Grapple Points
	PizzaBox::GameObject* grapplePoint1 = CreateObject<PizzaBox::GameObject>(PizzaBox::Vector3(0.0f, 60.0f, -30.0f), PizzaBox::Euler(), PizzaBox::Vector3(2.0f, 2.0f, 2.0f));
	grapplePoint1->AddComponent(new PizzaBox::MeshRender("SphereModel", new PizzaBox::ColorMaterial(PizzaBox::Color::Yellow)));
	grapplePoint1->AddComponent(new GrapplePoint(20.0f));
		auto child = CreateObject<PizzaBox::GameObject>(grapplePoint1, PizzaBox::Vector3(0.0f, -3.5f, 0.0f));
		child->AddComponent(new PizzaBox::PointLight(1.0f, PizzaBox::Color::Yellow, 5.0f));

	PizzaBox::GameObject* grapplePoint2 = CreateObject<PizzaBox::GameObject>(PizzaBox::Vector3(0.0f, 60.0f, -90.0f), PizzaBox::Euler(), PizzaBox::Vector3(2.0f, 2.0f, 2.0f));
	grapplePoint2->AddComponent(new PizzaBox::MeshRender("SphereModel", new PizzaBox::ColorMaterial(PizzaBox::Color::Yellow)));
	grapplePoint2->AddComponent(new GrapplePoint(20.0f));
		child = CreateObject<PizzaBox::GameObject>(grapplePoint2, PizzaBox::Vector3(0.0f, -3.5f, 0.0f));
		child->AddComponent(new PizzaBox::PointLight(1.0f, PizzaBox::Color::Yellow, 5.0f));

	PizzaBox::GameObject* grapplePoint3 = CreateObject<PizzaBox::GameObject>(PizzaBox::Vector3(0.0f, 60.0f, -120.0f), PizzaBox::Euler(), PizzaBox::Vector3(2.0f, 2.0f, 2.0f));
	grapplePoint3->AddComponent(new PizzaBox::MeshRender("SphereModel", new PizzaBox::ColorMaterial(PizzaBox::Color::Yellow)));
	grapplePoint3->AddComponent(new GrapplePoint(20.0f));
		child = CreateObject<PizzaBox::GameObject>(grapplePoint3, PizzaBox::Vector3(0.0f, -3.5f, 0.0f));
		child->AddComponent(new PizzaBox::PointLight(1.0f, PizzaBox::Color::Yellow, 5.0f));

	PizzaBox::GameObject* grapplePoint4 = CreateObject<PizzaBox::GameObject>(PizzaBox::Vector3(0.0f, 60.0f, -150.0f), PizzaBox::Euler(), PizzaBox::Vector3(2.0f, 2.0f, 2.0f));
	grapplePoint4->AddComponent(new PizzaBox::MeshRender("SphereModel", new PizzaBox::ColorMaterial(PizzaBox::Color::Yellow)));
	grapplePoint4->AddComponent(new GrapplePoint(20.0f));
		child = CreateObject<PizzaBox::GameObject>(grapplePoint4, PizzaBox::Vector3(0.0f, -3.5f, 0.0f));
		child->AddComponent(new PizzaBox::PointLight(1.0f, PizzaBox::Color::Yellow, 5.0f));

	PizzaBox::GameObject* grapplePoint5 = CreateObject<PizzaBox::GameObject>(PizzaBox::Vector3(0.0f, 60.0f, -180.0f), PizzaBox::Euler(), PizzaBox::Vector3(2.0f, 2.0f, 2.0f));
	grapplePoint5->AddComponent(new PizzaBox::MeshRender("SphereModel", new PizzaBox::ColorMaterial(PizzaBox::Color::Yellow)));
	grapplePoint5->AddComponent(new GrapplePoint(20.0f));
		child = CreateObject<PizzaBox::GameObject>(grapplePoint5, PizzaBox::Vector3(0.0f, -3.5f, 0.0f));
		child->AddComponent(new PizzaBox::PointLight(1.0f, PizzaBox::Color::Yellow, 5.0f));

	PizzaBox::GameObject* grapplePoint6 = CreateObject<PizzaBox::GameObject>(PizzaBox::Vector3(0.0f, 60.0f, -210.0f), PizzaBox::Euler(), PizzaBox::Vector3(2.0f, 2.0f, 2.0f));
	grapplePoint6->AddComponent(new PizzaBox::MeshRender("SphereModel", new PizzaBox::ColorMaterial(PizzaBox::Color::Yellow)));
	grapplePoint6->AddComponent(new GrapplePoint(20.0f));
		child = CreateObject<PizzaBox::GameObject>(grapplePoint6, PizzaBox::Vector3(0.0f, -3.5f, 0.0f));
		child->AddComponent(new PizzaBox::PointLight(1.0f, PizzaBox::Color::Yellow, 5.0f));

	//Test Water Object
	PizzaBox::GameObject* baseWater = CreateObject<PizzaBox::GameObject>(PizzaBox::Vector3(0.0f, 0.0f, 0.0f), PizzaBox::Euler(), PizzaBox::Vector3(140.0f, 40.0f, 140.0f));
	auto water = new PizzaBox::WaterMaterial("WaterTexture","","",32.0f,60.0f);
	water->SetWaveParamaters(PizzaBox::Vector4(2.0f, 4.0f, 4.0f, 2.0f), PizzaBox::Vector4(0.8f, 0.2f, 0.2f, 0.2f), PizzaBox::Vector4(0.4f, 0.4f, 0.4f, 0.2f));
	baseWater->AddComponent(new PizzaBox::MeshRender("WaterMesh", water));


	//Background Design
	for(int i = 0; i < 30; i++){
		auto window = new PizzaBox::ReflectiveMaterial(true, PizzaBox::ReflectiveMaterial::glass);

		PizzaBox::GameObject* backgroundHouse1 = CreateObject<PizzaBox::GameObject>(PizzaBox::Vector3(-400.0f, -5.0f, 400.0f - (i * 150.0f)), PizzaBox::Euler(), PizzaBox::Vector3(100.0f, 300.0f, 100.0f));
		texMat = new PizzaBox::TexturedMaterial("ConcreteTexture", false, "", "", 32.0f, 1.0f);
		backgroundHouse1->AddComponent(new PizzaBox::MeshRender("CubeModel", texMat));

		PizzaBox::GameObject* backgroundHouse2 = CreateObject<PizzaBox::GameObject>(PizzaBox::Vector3(400.0f, -5.0f, 400.0f - (i * 150.0f)), PizzaBox::Euler(), PizzaBox::Vector3(100.0f, 300.0f, 100.0f));
		texMat = new PizzaBox::TexturedMaterial("ConcreteTexture", false, "", "", 32.0f, 10.0f);
		backgroundHouse2->AddComponent(new PizzaBox::MeshRender("CubeModel", texMat));


		PizzaBox::GameObject* backgroundHouse3 = CreateObject<PizzaBox::GameObject>(PizzaBox::Vector3(-600.0f, -5.0f, 400.0f - (i * 150.0f)), PizzaBox::Euler(), PizzaBox::Vector3(100.0f, 300.0f, 100.0f));
		texMat = new PizzaBox::TexturedMaterial("ApartmentTexture", false, "", "", 32.0f, 10.0f);
		backgroundHouse3->AddComponent(new PizzaBox::MeshRender("CubeModel", texMat));

		PizzaBox::GameObject* backgroundHouse4 = CreateObject<PizzaBox::GameObject>(PizzaBox::Vector3(600.0f, -5.0f, 400.0f - (i * 150.0f)), PizzaBox::Euler(), PizzaBox::Vector3(100.0f, 300.0f, 100.0f));
		texMat = new PizzaBox::TexturedMaterial("ApartmentTexture", false, "", "", 32.0f, 10.0f);
		backgroundHouse4->AddComponent(new PizzaBox::MeshRender("CubeModel", texMat));


		PizzaBox::GameObject* backgroundHouseWindow = CreateObject<PizzaBox::GameObject>(PizzaBox::Vector3(-354.75f, 100.0f, 385.0f - (i * 150.0f)), PizzaBox::Euler(0.0f, 90.0f, 90.0f), PizzaBox::Vector3(5.0f, 5.0f, 5.0f));
		backgroundHouseWindow->AddComponent(new PizzaBox::MeshRender("BuildingGlassModel", window));
		window = new PizzaBox::ReflectiveMaterial(true, PizzaBox::ReflectiveMaterial::glass);

		PizzaBox::GameObject* backgroundHouseWindow2 = CreateObject<PizzaBox::GameObject>(PizzaBox::Vector3(354.75f, 100.0f, 385.0f - (i * 150.0f)), PizzaBox::Euler(0.0f, 90.0f, 90.0f), PizzaBox::Vector3(5.0f, 5.0f, 5.0f));
		backgroundHouseWindow2->AddComponent(new PizzaBox::MeshRender("BuildingGlassModel", window));
		window = new PizzaBox::ReflectiveMaterial(true, PizzaBox::ReflectiveMaterial::glass);
		
		PizzaBox::GameObject* backgroundHouseTippedOver = CreateObject<PizzaBox::GameObject>(PizzaBox::Vector3(-200.0f, -5.0f, 200.0f - (i * 600.0f)), PizzaBox::Euler(25.0f,0.0f,0.0f), PizzaBox::Vector3(100.0f, 300.0f, 100.0f));
		texMat = new PizzaBox::TexturedMaterial("ConcreteTextureTwo", false, "", "", 32.0f, 5.0f);
		backgroundHouseTippedOver->AddComponent(new PizzaBox::MeshRender("CubeModel", texMat));


		PizzaBox::GameObject* backgroundHouseWindow3 = CreateObject<PizzaBox::GameObject>(PizzaBox::Vector3(-200.05f, 95.0f, 195.0f - (i * 600.0f)), PizzaBox::Euler(25.0f, 0.0f, 0.0f), PizzaBox::Vector3(5.0f, 5.0f, 5.0f));
		backgroundHouseWindow3->AddComponent(new PizzaBox::MeshRender("BuildingGlassModel", window));
		window = new PizzaBox::ReflectiveMaterial(true, PizzaBox::ReflectiveMaterial::glass);


		PizzaBox::GameObject* backgroundHouseTippedOver2 = CreateObject<PizzaBox::GameObject>(PizzaBox::Vector3(200.0f, -5.0f, 200.0f - (i * 600.0f)), PizzaBox::Euler(25.0f, 90.0f, 0.0f), PizzaBox::Vector3(100.0f, 300.0f, 100.0f));
		texMat = new PizzaBox::TexturedMaterial("ConcreteTextureTwo", false, "", "", 32.0f, 5.0f);
		backgroundHouseTippedOver2->AddComponent(new PizzaBox::MeshRender("CubeModel", texMat));


		PizzaBox::GameObject* backgroundHouseWindow4 = CreateObject<PizzaBox::GameObject>(PizzaBox::Vector3(195.0f, 95.0f, 200.0f - (i * 600.0f)), PizzaBox::Euler(25.0f, 90.0f, 0.0f), PizzaBox::Vector3(5.0f, 5.0f, 5.0f));
		backgroundHouseWindow4->AddComponent(new PizzaBox::MeshRender("BuildingGlassModel", window));
		window = new PizzaBox::ReflectiveMaterial(true, PizzaBox::ReflectiveMaterial::glass);




	}

	return true;
}

void Level1::Destroy(){
	Scene::Destroy();
}