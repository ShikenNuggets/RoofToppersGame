#include "Tutorial.h"

#include <Animation/AnimMeshRender.h> 
#include <Graphics/Camera.h>
#include <Graphics/RenderEngine.h>
#include <Graphics/Materials/ColorMaterial.h>
#include <Graphics/Materials/ReflectiveMaterial.h>
#include <Graphics/Materials/TexturedMaterial.h>
#include <Graphics/Materials/WaterMaterial.h>
#include <Graphics/Models/MeshRender.h>
#include <Graphics/Particles/ParticleSystem.h>
#include <Graphics/Sky/SkyBox.h>
#include <Graphics/UI/UIManager.h>
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
#include "Scripts/CameraController.h"
#include "Scripts/CharacterController.h"
#include "Scripts/EndLevelTrigger.h"
#include "Scripts/GameController.h"
#include "Scripts/GrapplePoint.h"
#include "Scripts/MovingPlatform.h"
#include "Scripts/MusicScript.h"
#include "Scripts/PlayerController.h"

using namespace GamePackage;

Tutorial::Tutorial() : Scene() {
}

Tutorial::~Tutorial() {
}

bool Tutorial::Initialize() {
	PizzaBox::RenderEngine::SetFogDensity(0.000001f);
	PizzaBox::RenderEngine::SetWaterFogDensity(0.000001f);

	constexpr float skySize = 5000.0f;

	//SkyBox
	SetSky(new PizzaBox::SkyBox("SummerSkyBox", skySize));

	//Music
	auto gpm1 = new PizzaBox::AudioSource("TutorialMusic", PizzaBox::AudioSource::SoundType::_2D, "Music");
	PizzaBox::GameObject* music = CreateObject<PizzaBox::GameObject>(PizzaBox::Vector3(0.0f, 55.0f, 80.0f), PizzaBox::Euler(-15.0f, 0.0f, 0.0f));
	music->AddComponent(gpm1);
	music->AddComponent(new MusicScript(gpm1));

	//Waves
	/**
	auto wve1 = new PizzaBox::AudioSource("WavesSFX", PizzaBox::AudioSource::SoundType::_2D, "SFX");
	PizzaBox::GameObject* waves = CreateObject<PizzaBox::GameObject>(PizzaBox::Vector3(0.0f, 55.0f, 80.0f), PizzaBox::Euler(-15.0f, 0.0f, 0.0f));
	waves->AddComponent(wve1);
	waves->AddComponent(new MusicScript(wve1));
	*/
	//Camera
	PizzaBox::GameObject* mainCamera = CreateObject<PizzaBox::GameObject>(PizzaBox::Vector3(0.0f, 125.0f, 250.0f), PizzaBox::Euler(-15.0f, 0.0f, 0.0f));
	mainCamera->SetTag("Camera");
	auto cam = new PizzaBox::Camera(PizzaBox::ViewportRect::fullScreen, PizzaBox::Camera::RenderMode::Perspective);
	cam->SetFarPlane(skySize);
	mainCamera->AddComponent(cam);
	auto controller = new CameraController();
	//auto controller = new CharacterController();
	mainCamera->AddComponent(controller);
	mainCamera->AddComponent(new PizzaBox::AudioListener());
	
	//Directional Light
	auto dirLight = CreateObject<PizzaBox::GameObject>(PizzaBox::Vector3(), PizzaBox::Euler(-35.0f, 12.0f, 0.0f));
	dirLight->AddComponent(new PizzaBox::DirectionalLight(2.0f));

	auto gameController = CreateObject<PizzaBox::GameObject>();
	gameController->AddComponent(new GameController(PizzaBox::Vector3(0.0f, 80.0f, 300.0f), PizzaBox::Euler(0.0f, 180.0f, 0.0f)));

	CreateObject<Building>(PizzaBox::Vector3(0.0f, 30.0f, 200.0f), PizzaBox::Euler(), PizzaBox::Vector3(1250.0f, 100.0f, 8000.0f), "BrickTexture",1024);



	CreateObject<Building>(PizzaBox::Vector3(-200.0f, 30.0f, 200.0f), PizzaBox::Euler(), PizzaBox::Vector3(10.0f, 200.0f, 4000.0f), "BrickTextureTwo", 64);
	CreateObject<Building>(PizzaBox::Vector3(200.0f, 30.0f, 200.0f), PizzaBox::Euler(), PizzaBox::Vector3(10.0f, 200.0f, 4000.0f), "BrickTextureTwo", 64);

	

	CreateObject<Building>(PizzaBox::Vector3(0.0f, 30.0f, 400.0f), PizzaBox::Euler(), PizzaBox::Vector3(1000.0f, 200.0f, 10.0f), "BrickTextureFive", 64);

	
	CreateObject<Building>(PizzaBox::Vector3(0.0f, 40.0f, 200.0f), PizzaBox::Euler(), PizzaBox::Vector3(40.0f, 100.0f, 40.0f), "BrickTextureThree");
	CreateObject<Building>(PizzaBox::Vector3(0.0f, 35.0f, 240.0f), PizzaBox::Euler(), PizzaBox::Vector3(40.0f, 100.0f, 40.0f), "BrickTextureThree");
	//CreateObject<Building>(PizzaBox::Vector3(0.0f, 34.0f, 100.0f), PizzaBox::Euler(), PizzaBox::Vector3(60.0f, 100.0f, 20.0f), "BrickTextureFour");
	CreateObject<Building>(PizzaBox::Vector3(0.0f, 45.0f, 150.0f), PizzaBox::Euler(), PizzaBox::Vector3(40.0f, 100.0f, 40.0f), "BrickTextureThree");


	CreateObject<Building>(PizzaBox::Vector3(0.0f, 50.0f, 85.0f), PizzaBox::Euler(), PizzaBox::Vector3(400.0f, 100.0f, 30.0f), "BrickTextureThree");

	CreateObject<Building>(PizzaBox::Vector3(0.0f, 50.0f, 35.0f), PizzaBox::Euler(), PizzaBox::Vector3(30.0f, 100.0f, 30.0f), "BrickTextureFour", 64);
	
	CreateObject<Building>(PizzaBox::Vector3(0.0f, 50.0f, -35.0f), PizzaBox::Euler(), PizzaBox::Vector3(30.0f, 100.0f, 30.0f), "BrickTextureTwo", 64);

	CreateObject<Building>(PizzaBox::Vector3(-50.0f, 37.0f, 70.0f), PizzaBox::Euler(), PizzaBox::Vector3(25.0f, 100.0f, 24.5f), "BrickTextureFive", 64);
	CreateObject<Building>(PizzaBox::Vector3(50.0f, 37.0f, 70.0f), PizzaBox::Euler(), PizzaBox::Vector3(25.0f, 100.0f, 24.5f), "BrickTextureFive", 64);

	CreateObject<Building>(PizzaBox::Vector3(-65.0f, 42.0f, 70.0f), PizzaBox::Euler(), PizzaBox::Vector3(25.0f, 100.0f, 25.0f), "BrickTexture", 64);
	CreateObject<Building>(PizzaBox::Vector3(65.0f, 42.0f, 70.0f), PizzaBox::Euler(), PizzaBox::Vector3(25.0f, 100.0f, 25.0f), "BrickTexture", 64);


	PizzaBox::GameObject* spotlightOne = CreateObject<PizzaBox::GameObject>(PizzaBox::Vector3(-50.0f,140.0f,95.0f), PizzaBox::Euler(), PizzaBox::Vector3());
	spotlightOne->AddComponent(new PizzaBox::SpotLight(2.0f));

	PizzaBox::GameObject* spotlightTwo = CreateObject<PizzaBox::GameObject>(PizzaBox::Vector3(50.0f, 140.0f, 95.0f), PizzaBox::Euler(), PizzaBox::Vector3());
	spotlightTwo->AddComponent(new PizzaBox::SpotLight(2.0f));
	CreateObject<Building>(PizzaBox::Vector3(0.0f, 50.0f, -170.0f), PizzaBox::Euler(), PizzaBox::Vector3(1000.0f, 100.0f, 40.0f), "BrickTextureTwo", 256);

	CreateObject<Building>(PizzaBox::Vector3(0.0, 30.0f, -185.0f), PizzaBox::Euler(), PizzaBox::Vector3(1000.0f, 200.0f, 10.0f), "BrickTextureFive", 256);

	CreateObject<GrapplePointObject>(PizzaBox::Vector3(0.0f, 120.0f, 115.0f), PizzaBox::Euler(), PizzaBox::Vector3(0.5f, 0.5f, 0.5f));

	CreateObject<GrapplePointObject>(PizzaBox::Vector3(0.0f, 120.0f, 60.0f), PizzaBox::Euler(), PizzaBox::Vector3(0.5f, 0.5f, 0.5f));

	CreateObject<GrapplePointObject>(PizzaBox::Vector3(0.0f, 120.0f, 0.0f), PizzaBox::Euler(), PizzaBox::Vector3(0.5f, 0.5f, 0.5f));

	CreateObject<GrapplePointObject>(PizzaBox::Vector3(0.0f, 125.0f, -75.0f), PizzaBox::Euler(), PizzaBox::Vector3(0.5f, 0.5f, 0.5f));

	CreateObject<GrapplePointObject>(PizzaBox::Vector3(0.0f, 125.0f, -125.0f), PizzaBox::Euler(), PizzaBox::Vector3(0.5f, 0.5f, 0.5f));

	auto endLevelObj = CreateObject<PizzaBox::GameObject>(PizzaBox::Vector3(0.0f, 100.2f, -179.30f), PizzaBox::Euler(-90.0f, 90.0f, 0.0f), PizzaBox::Vector3(0.85f, 0.85f, 0.85f));
	endLevelObj->SetTag("EndLevelTrigger");
	endLevelObj->AddComponent(new PizzaBox::MeshRender("DoorModel", "DoorTexture"));
	endLevelObj->AddComponent(new PizzaBox::Collider(endLevelObj->GlobalScale()));
	endLevelObj->AddComponent(new EndLevelTrigger());

	//Test Water Object
	/**
	PizzaBox::GameObject* baseWater = CreateObject<PizzaBox::GameObject>(PizzaBox::Vector3(0.0f, -20.0f, 0.0f), PizzaBox::Euler(), PizzaBox::Vector3(140.0f, 40.0f, 140.0f));
	auto water = new PizzaBox::WaterMaterial("WaterTexture", "", "", 32.0f, 256.0f);
	water->SetWaveParamaters(PizzaBox::Vector4(2.0f, 4.0f, 4.0f, 2.0f), PizzaBox::Vector4(0.8f, 0.2f, 0.2f, 0.2f), PizzaBox::Vector4(0.4f, 0.4f, 0.4f, 0.2f));
	water->SetFlowDirection(PizzaBox::Vector2(0.0f, 1.0f));
	auto mr = new PizzaBox::MeshRender("WaterMesh", water);
	mr->SetCastsShadows(false);
	baseWater->AddComponent(mr);
	*/
	//Background Design

	/**
	for (int i = 0; i < 30; i++) {
		int randomPositionx = PizzaBox::Random::Range(-50, 50);
		int randomPositiony = PizzaBox::Random::Range(-100, 100);
		int randomPositionz = PizzaBox::Random::Range(-25, 25);
		CreateObject<BuildingScenery>(PizzaBox::Vector3(-400.0f + randomPositionx, -5.0f + randomPositiony, 400.0f - (i * 150.0f + randomPositionz)), PizzaBox::Euler(), PizzaBox::Vector3(100.0f, 300.0f, 100.0f));
		CreateObject<BuildingScenery>(PizzaBox::Vector3(400.0f + randomPositionx, -5.0f + randomPositiony, 400.0f - (i * 150.0f + randomPositionz)), PizzaBox::Euler(), PizzaBox::Vector3(100.0f, 300.0f, 100.0f));
		CreateObject<BuildingScenery>(PizzaBox::Vector3(-600.0f + randomPositionx, -5.0f + randomPositiony, 400.0f - (i * 150.0f + randomPositionz)), PizzaBox::Euler(), PizzaBox::Vector3(100.0f, 300.0f, 100.0f));
		CreateObject<BuildingScenery>(PizzaBox::Vector3(600.0f + randomPositionx, -5.0f + randomPositiony, 400.0f - (i * 150.0f + randomPositionz)), PizzaBox::Euler(), PizzaBox::Vector3(100.0f, 300.0f, 100.0f));
		CreateObject<BuildingScenery>(PizzaBox::Vector3(-300.0f + randomPositionx, -5.0f + randomPositiony, 200.0f - (i * 1200.0f + randomPositionz)), PizzaBox::Euler(25.0f + randomPositionx, 0.0f + randomPositiony, 0.0f), PizzaBox::Vector3(100.0f, 300.0f, 100.0f), false, false);
		CreateObject<BuildingScenery>(PizzaBox::Vector3(300.0f + randomPositionx, -5.0f + randomPositiony, 200.0f - (i * 1200.0f + randomPositionz)), PizzaBox::Euler(25.0f + randomPositionx, 90.0f + randomPositiony, 0.0f), PizzaBox::Vector3(100.0f, 300.0f, 100.0f), false, false);
	}
	*/
	return true;
}

void Tutorial::Destroy() {
	Scene::Destroy();
}