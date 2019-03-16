#include "Level1.h"

#include <Animation/AnimMeshRender.h> 
#include <Graphics/Sky/SkyBox.h>
#include <Graphics/Camera.h>
#include <Graphics/RenderEngine.h>
#include <Graphics/Models/MeshRender.h>
#include <Graphics/Materials/ColorMaterial.h>
#include <Graphics/Materials/ReflectiveMaterial.h>
#include <Graphics/Materials/TexturedMaterial.h>
#include <Graphics/Materials/WaterMaterial.h>
#include <Graphics/Particles/ParticleSystem.h>
#include <Physics/Collider.h>
#include <Physics/Rigidbody.h>
#include <Audio/AudioListener.h>
#include <Audio/AudioSource.h>

#include "Animators/PlayerAnimator.h"
#include "Objects/Building.h"
#include "Objects/BuildingScenery.h"
#include "Objects/GrapplePointObject.h"
#include "Objects/Platform.h"
#include "Objects/Player.h"
#include "Scripts/CharacterController.h"
#include "Scripts/MusicScript.h"
#include "Scripts/CameraController.h"
#include "Scripts/GameController.h"
#include "Scripts/GrapplePoint.h"
#include "Scripts/PlayerController.h"
#include "Scripts/MovingPlatform.h"
#include "Scripts/EndLevelTrigger.h"

using namespace GamePackage;

Level1::Level1() : Scene(){
}
 
Level1::~Level1(){
}

bool Level1::Initialize(){
	PizzaBox::RenderEngine::SetFogDensity(0.0003f);
	PizzaBox::RenderEngine::SetWaterFogDensity(0.00001f);

	constexpr float skySize = 5000.0f;
	
	//SkyBox
	SetSky(new PizzaBox::SkyBox("CloudSkybox", skySize));

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
	mainCamera->SetTag("Camera");
	auto cam = new PizzaBox::Camera(PizzaBox::ViewportRect::fullScreen, PizzaBox::Camera::RenderMode::Perspective);
	cam->SetFarPlane(skySize);
	mainCamera->AddComponent(cam);
	auto controller = new CameraController();
	mainCamera->AddComponent(controller);
	mainCamera->AddComponent(new PizzaBox::AudioListener());

	//mainCamera->AddComponent(new MusicScript(as1));

	//Directional Light
	auto dirLight = CreateObject<PizzaBox::GameObject>(PizzaBox::Vector3(), PizzaBox::Euler(-35.0f, 12.0f, 0.0f));
	dirLight->AddComponent(new PizzaBox::DirectionalLight(2.0f));
	
	auto gameController = CreateObject<PizzaBox::GameObject>();
	gameController->AddComponent(new GameController(PizzaBox::Vector3(0.0f, 60.0f, 0.0f), PizzaBox::Euler(0.0f, 180.0f, 0.0f)));

	//Grapple Point
	//auto grapplePoint = CreateObject<PizzaBox::GameObject>(PizzaBox::Vector3(0.0f, 50.0f, -50.0f), PizzaBox::Euler(), PizzaBox::Vector3::Fill(2.0f));
	//grapplePoint->AddComponent(new PizzaBox::MeshRender("SphereModel", new PizzaBox::ColorMaterial(PizzaBox::Color::Yellow)));
	//grapplePoint->AddComponent(new GrapplePoint(35.0f));

	//Test Static platfrom
	CreateObject<Building>(PizzaBox::Vector3(0.0f, -5.0f, 0.0f), PizzaBox::Euler(), PizzaBox::Vector3(20.0f, 100.0f, 20.0f));
	CreateObject<Building>(PizzaBox::Vector3(0.0f, -5.0f, -120.0f), PizzaBox::Euler(), PizzaBox::Vector3(20.0f, 100.0f, 20.0f));
	CreateObject<Building>(PizzaBox::Vector3(0.0f, -5.0f, -280.0f), PizzaBox::Euler(/*-25.0f*/), PizzaBox::Vector3(20.0f, 100.0f, 20.0f));
	CreateObject<Building>(PizzaBox::Vector3(0.0f, -5.0f, -300.0f), PizzaBox::Euler(), PizzaBox::Vector3(20.0f, 300.0f, 20.0f));
	CreateObject<Building>(PizzaBox::Vector3(0.0f, -5.0f, -450.0f), PizzaBox::Euler(), PizzaBox::Vector3(20.0f, 300.0f, 20.0f));

	CreateObject<Platform>(PizzaBox::Vector3(0.0f, 40.0f, -60.0f), PizzaBox::Euler(), PizzaBox::Vector3(12.0f, 2.0f, 12.0f));
	CreateObject<Platform>(PizzaBox::Vector3(0.0f, 45.0f, -150.0f), PizzaBox::Euler(), PizzaBox::Vector3(12.0f, 2.0f, 32.0f));
	CreateObject<Platform>(PizzaBox::Vector3(0.0f, 40.0f, -375.0f), PizzaBox::Euler(), PizzaBox::Vector3(16.0f, 2.0f, 16.0f));
	CreateObject<Platform>(PizzaBox::Vector3(0.0f, 35.0f, -450.0f), PizzaBox::Euler(), PizzaBox::Vector3(32.0f, 5.0f, 32.0f));

	//Grapple Points
	CreateObject<GrapplePointObject>(PizzaBox::Vector3(0.0f, 60.0f, -30.0f), PizzaBox::Euler(), PizzaBox::Vector3(0.5f, 0.5f, 0.5f));
	CreateObject<GrapplePointObject>(PizzaBox::Vector3(0.0f, 60.0f, -90.0f), PizzaBox::Euler(), PizzaBox::Vector3(0.5f, 0.5f, 0.5f));
	//CreateObject<GrapplePointObject>(PizzaBox::Vector3(0.0f, 60.0f, -120.0f), PizzaBox::Euler(), PizzaBox::Vector3(0.5f, 0.5f, 0.5f));
	//CreateObject<GrapplePointObject>(PizzaBox::Vector3(0.0f, 60.0f, -150.0f), PizzaBox::Euler(), PizzaBox::Vector3(0.5f, 0.5f, 0.5f));
	CreateObject<GrapplePointObject>(PizzaBox::Vector3(0.0f, 65.0f, -190.0f), PizzaBox::Euler(), PizzaBox::Vector3(0.5f, 0.5f, 0.5f));
	CreateObject<GrapplePointObject>(PizzaBox::Vector3(0.0f, 70.0f, -240.0f), PizzaBox::Euler(), PizzaBox::Vector3(0.5f, 0.5f, 0.5f));
	CreateObject<GrapplePointObject>(PizzaBox::Vector3(20.0f, 65.0f, -300.0f), PizzaBox::Euler(), PizzaBox::Vector3(0.5f, 0.5f, 0.5f));
	CreateObject<GrapplePointObject>(PizzaBox::Vector3(20.0f, 60.0f, -350.0f), PizzaBox::Euler(), PizzaBox::Vector3(0.5f, 0.5f, 0.5f));
	CreateObject<GrapplePointObject>(PizzaBox::Vector3(0.0f, 60.0f, -410.0f), PizzaBox::Euler(), PizzaBox::Vector3(0.5f, 0.5f, 0.5f));

	auto endLevelObj = CreateObject<PizzaBox::GameObject>(PizzaBox::Vector3(0.0f, 38.2f, -439.25f), PizzaBox::Euler(-90.0f, 90.0f, 0.0f), PizzaBox::Vector3(0.85f, 0.85f, 0.85f));
	endLevelObj->SetTag("EndLevelTrigger");
	endLevelObj->AddComponent(new PizzaBox::MeshRender("DoorModel", "DoorTexture"));
	endLevelObj->AddComponent(new PizzaBox::Collider(endLevelObj->GlobalScale()));
	endLevelObj->AddComponent(new EndLevelTrigger());

	//Test Water Object
	PizzaBox::GameObject* baseWater = CreateObject<PizzaBox::GameObject>(PizzaBox::Vector3(0.0f, 0.0f, 0.0f), PizzaBox::Euler(), PizzaBox::Vector3(140.0f, 40.0f, 140.0f));
	auto water = new PizzaBox::WaterMaterial("WaterTexture", "", "", 32.0f, 256.0f);
	water->SetWaveParamaters(PizzaBox::Vector4(2.0f, 4.0f, 4.0f, 2.0f), PizzaBox::Vector4(0.8f, 0.2f, 0.2f, 0.2f), PizzaBox::Vector4(0.4f, 0.4f, 0.4f, 0.2f));
	water->SetFlowDirection(PizzaBox::Vector2(0.0f, 1.0f));
	baseWater->AddComponent(new PizzaBox::MeshRender("WaterMesh", water));

	//Background Design
	for(int i = 0; i < 30; i++){
		CreateObject<BuildingScenery>(PizzaBox::Vector3(-400.0f, -5.0f, 400.0f - (i * 150.0f)), PizzaBox::Euler(), PizzaBox::Vector3(100.0f, 300.0f, 100.0f));
		CreateObject<BuildingScenery>(PizzaBox::Vector3(400.0f, -5.0f, 400.0f - (i * 150.0f)), PizzaBox::Euler(), PizzaBox::Vector3(100.0f, 300.0f, 100.0f));
		CreateObject<BuildingScenery>(PizzaBox::Vector3(-600.0f, -5.0f, 400.0f - (i * 150.0f)), PizzaBox::Euler(), PizzaBox::Vector3(100.0f, 300.0f, 100.0f));
		CreateObject<BuildingScenery>(PizzaBox::Vector3(600.0f, -5.0f, 400.0f - (i * 150.0f)), PizzaBox::Euler(), PizzaBox::Vector3(100.0f, 300.0f, 100.0f));
		CreateObject<BuildingScenery>(PizzaBox::Vector3(-200.0f, -5.0f, 200.0f - (i * 600.0f)), PizzaBox::Euler(25.0f,0.0f,0.0f), PizzaBox::Vector3(100.0f, 300.0f, 100.0f), false);
		CreateObject<BuildingScenery>(PizzaBox::Vector3(200.0f, -5.0f, 200.0f - (i * 600.0f)), PizzaBox::Euler(25.0f, 90.0f, 0.0f), PizzaBox::Vector3(100.0f, 300.0f, 100.0f), false);
	}

	return true;
}

void Level1::Destroy(){
	Scene::Destroy();
}