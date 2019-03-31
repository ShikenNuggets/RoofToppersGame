#include "MainMenuScene.h"

#include <Audio/AudioListener.h>
#include <Audio/AudioSource.h>
#include <Graphics/RenderEngine.h>
#include <Graphics/Materials/WaterMaterial.h>
#include <Graphics/Sky/SkyBox.h>
#include <Graphics/UI/UIManager.h>

#include "Objects/Building.h"
#include "Objects/BuildingScenery.h"
#include "Objects/GrapplePointObject.h"
#include "Objects/Platform.h"
#include "Scripts/CharacterController.h"
#include "Scripts/MusicScript.h"

using namespace GamePackage;

MainMenuScene::MainMenuScene(){
}

MainMenuScene::~MainMenuScene(){
}

bool MainMenuScene::Initialize(){
	PizzaBox::RenderEngine::SetFogDensity(0.0f);
	PizzaBox::RenderEngine::SetWaterFogDensity(0.0f);

	//Music
	PizzaBox::GameObject* music = CreateObject<PizzaBox::GameObject>(PizzaBox::Vector3(0.0f, 55.0f, 80.0f), PizzaBox::Euler(-15.0f, 0.0f, 0.0f));
	auto mmu1 = new PizzaBox::AudioSource("MenuMusic", PizzaBox::AudioSource::SoundType::_2D, "Music");
	music->AddComponent(mmu1);
	music->AddComponent(new MusicScript(mmu1));

	constexpr float skySize = 5000.0f;
	auto skybox = new PizzaBox::SkyBox("SummerSkyBox", skySize);
	skybox->SetUseFog(false);
	SetSky(skybox);

	PizzaBox::GameObject* mainCamera = CreateObject<PizzaBox::GameObject>(PizzaBox::Vector3(-0.0f, 175.0f, 75.0f), PizzaBox::Euler(-15.0f, 20.0f, 0.0f));
	auto cam = new PizzaBox::Camera(PizzaBox::ViewportRect::fullScreen, PizzaBox::Camera::RenderMode::Perspective);
	cam->SetFarPlane(skySize);
	mainCamera->AddComponent(cam);
	mainCamera->AddComponent(new PizzaBox::AudioListener());
	mainCamera->AddComponent(new CharacterController());
	 
	PizzaBox::RenderEngine::SetFogDensity(0.0003f);
	PizzaBox::RenderEngine::SetWaterFogDensity(0.00001f);

	//Waves
	auto wve1 = new PizzaBox::AudioSource("WavesSFX", PizzaBox::AudioSource::SoundType::_2D, "SFX");
	PizzaBox::GameObject* waves = CreateObject<PizzaBox::GameObject>(PizzaBox::Vector3(0.0f, 55.0f, 80.0f), PizzaBox::Euler(-15.0f, 0.0f, 0.0f));
	waves->AddComponent(wve1);
	waves->AddComponent(new MusicScript(wve1));

	//Directional Light
	auto dirLight = CreateObject<PizzaBox::GameObject>(PizzaBox::Vector3(), PizzaBox::Euler(-35.0f, 12.0f, 0.0f));
	dirLight->AddComponent(new PizzaBox::DirectionalLight(2.0f));

	CreateObject<Building>(PizzaBox::Vector3(0.0f, 30.0f, 200.0f), PizzaBox::Euler(), PizzaBox::Vector3(20.0f, 100.0f, 20.0f), "BrickTextureFive");
	CreateObject<Building>(PizzaBox::Vector3(0.0f, 23.0f, 200.0f), PizzaBox::Euler(), PizzaBox::Vector3(200.0f, 100.0f, 200.0f), "BrickTextureTwo");
	CreateObject<Building>(PizzaBox::Vector3(0.0f, 34.0f, 150.0f), PizzaBox::Euler(), PizzaBox::Vector3(40.0f, 100.0f, 40.0f), "BrickTextureThree");
	CreateObject<Building>(PizzaBox::Vector3(0.0f, 34.0f, 100.0f), PizzaBox::Euler(), PizzaBox::Vector3(60.0f, 100.0f, 20.0f), "BrickTextureFour");


	CreateObject<Building>(PizzaBox::Vector3(0.0f, -5.0f, 15.0f), PizzaBox::Euler(), PizzaBox::Vector3(50.0f, 100.0f, 50.0f), "BrickTextureTwo");

	CreateObject<Building>(PizzaBox::Vector3(0.0f, -5.0f, -120.0f), PizzaBox::Euler(), PizzaBox::Vector3(32.0f, 100.0f, 32.0f), "BrickTextureFive");
	CreateObject<Building>(PizzaBox::Vector3(0.0f, -5.0f, -280.0f), PizzaBox::Euler(/*-25.0f*/), PizzaBox::Vector3(20.0f, 100.0f, 20.0f), "BrickTextureTwo");

	CreateObject<Building>(PizzaBox::Vector3(0.0f, -10.0f, -805.0f), PizzaBox::Euler(/*-25.0f*/), PizzaBox::Vector3(40.0f, 100.0f, 20.0f));

	CreateObject<Building>(PizzaBox::Vector3(0.0f, -20.0f, -1105.0f), PizzaBox::Euler(/*-25.0f*/), PizzaBox::Vector3(40.0f, 100.0f, 40.0f), "BrickTextureThree");
	CreateObject<Building>(PizzaBox::Vector3(0.0f, 60.0f, -1600.0f), PizzaBox::Euler(), PizzaBox::Vector3(70.0f, 10.0f, 30.0f), "GoldTexture", 128.0f);
	CreateObject<Building>(PizzaBox::Vector3(0.0f, 80.0f, -1600.0f), PizzaBox::Euler(), PizzaBox::Vector3(70.0f, 10.0f, 30.0f), "GoldTexture", 128.0f);
	CreateObject<Building>(PizzaBox::Vector3(0.0f, 100.0f, -1600.0f), PizzaBox::Euler(), PizzaBox::Vector3(70.0f, 10.0f, 30.0f), "GoldTexture", 128.0f);
	CreateObject<Building>(PizzaBox::Vector3(0.0f, 120.0f, -1600.0f), PizzaBox::Euler(), PizzaBox::Vector3(70.0f, 10.0f, 30.0f), "GoldTexture", 128.0f);
	CreateObject<Building>(PizzaBox::Vector3(0.0f, -5.0f, -1600.0f), PizzaBox::Euler(), PizzaBox::Vector3(60.0f, 300.0f, 20.0f), "BrickTextureTwo", 64.0f);

	CreateObject<Building>(PizzaBox::Vector3(0.0f, -5.0f, -1700.0f), PizzaBox::Euler(), PizzaBox::Vector3(60.0f, 300.0f, 60.0f));
	CreateObject<Building>(PizzaBox::Vector3(0.0f, -5.0f, -1800.0f), PizzaBox::Euler(), PizzaBox::Vector3(60.0f, 300.0f, 60.0f), "BrickTextureFive");

	CreateObject<Platform>(PizzaBox::Vector3(0.0f, 40.0f, -55.0f), PizzaBox::Euler(), PizzaBox::Vector3(32.0f, 2.0f, 32.0f));
	CreateObject<Platform>(PizzaBox::Vector3(0.0f, 45.0f, -150.0f), PizzaBox::Euler(), PizzaBox::Vector3(24.0f, 2.0f, 24.0f));
	CreateObject<Platform>(PizzaBox::Vector3(0.0f, 40.0f, -375.0f), PizzaBox::Euler(), PizzaBox::Vector3(24.0f, 2.0f, 24.0f));
	CreateObject<Platform>(PizzaBox::Vector3(0.0f, 35.0f, -450.0f), PizzaBox::Euler(), PizzaBox::Vector3(32.0f, 5.0f, 32.0f));
	CreateObject<Platform>(PizzaBox::Vector3(0.0f, 35.0f, -500.0f), PizzaBox::Euler(), PizzaBox::Vector3(32.0f, 5.0f, 32.0f));
	CreateObject<Platform>(PizzaBox::Vector3(0.0f, 35.0f, -550.0f), PizzaBox::Euler(), PizzaBox::Vector3(32.0f, 5.0f, 32.0f));
	CreateObject<Platform>(PizzaBox::Vector3(0.0f, 35.0f, -600.0f), PizzaBox::Euler(), PizzaBox::Vector3(32.0f, 5.0f, 32.0f));
	CreateObject<Platform>(PizzaBox::Vector3(0.0f, 35.0f, -650.0f), PizzaBox::Euler(), PizzaBox::Vector3(16.0f, 5.0f, 32.0f));
	CreateObject<Platform>(PizzaBox::Vector3(0.0f, 35.0f, -700.0f), PizzaBox::Euler(), PizzaBox::Vector3(16.0f, 5.0f, 32.0f));
	CreateObject<Platform>(PizzaBox::Vector3(0.0f, 37.0f, -750.0f), PizzaBox::Euler(), PizzaBox::Vector3(16.0f, 5.0f, 32.0f));

	CreateObject<Platform>(PizzaBox::Vector3(0.0f, 25.0f, -975.0f), PizzaBox::Euler(), PizzaBox::Vector3(52.0f, 5.0f, 52.0f));
	CreateObject<Platform>(PizzaBox::Vector3(0.0f, 25.0f, -1450.0f), PizzaBox::Euler(), PizzaBox::Vector3(52.0f, 5.0f, 52.0f));
	CreateObject<Platform>(PizzaBox::Vector3(0.0f, 25.0f, -1525.0f), PizzaBox::Euler(), PizzaBox::Vector3(52.0f, 5.0f, 52.0f));



	CreateObject<Platform>(PizzaBox::Vector3(0.0f, 35.0f, -1600.0f), PizzaBox::Euler(), PizzaBox::Vector3(80.0f, 5.0f, 60.0f));


	//Grapple Points
	CreateObject<GrapplePointObject>(PizzaBox::Vector3(0.0f, 105.0f, 180.0f), PizzaBox::Euler(), PizzaBox::Vector3(0.5f, 0.5f, 0.5f));
	CreateObject<GrapplePointObject>(PizzaBox::Vector3(0.0f, 108.0f, 120.0f), PizzaBox::Euler(), PizzaBox::Vector3(0.5f, 0.5f, 0.5f));
	CreateObject<GrapplePointObject>(PizzaBox::Vector3(0.0f, 90.0f, 60.0f), PizzaBox::Euler(), PizzaBox::Vector3(0.5f, 0.5f, 0.5f));

	CreateObject<GrapplePointObject>(PizzaBox::Vector3(0.0f, 60.0f, -30.0f), PizzaBox::Euler(), PizzaBox::Vector3(0.5f, 0.5f, 0.5f));
	CreateObject<GrapplePointObject>(PizzaBox::Vector3(0.0f, 60.0f, -90.0f), PizzaBox::Euler(), PizzaBox::Vector3(0.5f, 0.5f, 0.5f));
	//CreateObject<GrapplePointObject>(PizzaBox::Vector3(0.0f, 60.0f, -120.0f), PizzaBox::Euler(), PizzaBox::Vector3(0.5f, 0.5f, 0.5f));
	//CreateObject<GrapplePointObject>(PizzaBox::Vector3(0.0f, 60.0f, -150.0f), PizzaBox::Euler(), PizzaBox::Vector3(0.5f, 0.5f, 0.5f));
	CreateObject<GrapplePointObject>(PizzaBox::Vector3(0.0f, 65.0f, -190.0f), PizzaBox::Euler(), PizzaBox::Vector3(0.5f, 0.5f, 0.5f));
	CreateObject<GrapplePointObject>(PizzaBox::Vector3(0.0f, 70.0f, -240.0f), PizzaBox::Euler(), PizzaBox::Vector3(0.5f, 0.5f, 0.5f));
	CreateObject<GrapplePointObject>(PizzaBox::Vector3(20.0f, 65.0f, -300.0f), PizzaBox::Euler(), PizzaBox::Vector3(0.5f, 0.5f, 0.5f));
	CreateObject<GrapplePointObject>(PizzaBox::Vector3(20.0f, 65.0f, -350.0f), PizzaBox::Euler(), PizzaBox::Vector3(0.5f, 0.5f, 0.5f));
	CreateObject<GrapplePointObject>(PizzaBox::Vector3(0.0f, 65.0f, -410.0f), PizzaBox::Euler(), PizzaBox::Vector3(0.5f, 0.5f, 0.5f));
	CreateObject<GrapplePointObject>(PizzaBox::Vector3(0.0f, 65.0f, -475.0f), PizzaBox::Euler(), PizzaBox::Vector3(0.5f, 0.5f, 0.5f));
	CreateObject<GrapplePointObject>(PizzaBox::Vector3(0.0f, 65.0f, -525.0f), PizzaBox::Euler(), PizzaBox::Vector3(0.5f, 0.5f, 0.5f));
	CreateObject<GrapplePointObject>(PizzaBox::Vector3(0.0f, 65.0f, -575.0f), PizzaBox::Euler(), PizzaBox::Vector3(0.5f, 0.5f, 0.5f));
	CreateObject<GrapplePointObject>(PizzaBox::Vector3(0.0f, 65.0f, -625.0f), PizzaBox::Euler(), PizzaBox::Vector3(0.5f, 0.5f, 0.5f));
	CreateObject<GrapplePointObject>(PizzaBox::Vector3(0.0f, 65.0f, -675.0f), PizzaBox::Euler(), PizzaBox::Vector3(0.5f, 0.5f, 0.5f));
	CreateObject<GrapplePointObject>(PizzaBox::Vector3(0.0f, 65.0f, -725.0f), PizzaBox::Euler(), PizzaBox::Vector3(0.5f, 0.5f, 0.5f));
	CreateObject<GrapplePointObject>(PizzaBox::Vector3(0.0f, 65.0f, -780.0f), PizzaBox::Euler(), PizzaBox::Vector3(0.5f, 0.5f, 0.5f));
	CreateObject<GrapplePointObject>(PizzaBox::Vector3(-20.0f, 65.0f, -850.0f), PizzaBox::Euler(), PizzaBox::Vector3(0.5f, 0.5f, 0.5f));
	CreateObject<GrapplePointObject>(PizzaBox::Vector3(-20.0f, 70.0f, -875.0f), PizzaBox::Euler(), PizzaBox::Vector3(0.5f, 0.5f, 0.5f));
	CreateObject<GrapplePointObject>(PizzaBox::Vector3(-20.0f, 70.0f, -900.0f), PizzaBox::Euler(), PizzaBox::Vector3(0.5f, 0.5f, 0.5f));
	CreateObject<GrapplePointObject>(PizzaBox::Vector3(-20.0f, 70.0f, -925.0f), PizzaBox::Euler(), PizzaBox::Vector3(0.5f, 0.5f, 0.5f));
	CreateObject<GrapplePointObject>(PizzaBox::Vector3(0.0f, 60.0f, -1050.0f), PizzaBox::Euler(), PizzaBox::Vector3(0.5f, 0.5f, 0.5f));
	CreateObject<GrapplePointObject>(PizzaBox::Vector3(20.0f, 60.0f, -1150.0f), PizzaBox::Euler(), PizzaBox::Vector3(0.5f, 0.5f, 0.5f));
	CreateObject<GrapplePointObject>(PizzaBox::Vector3(10.0f, 60.0f, -1200.0f), PizzaBox::Euler(), PizzaBox::Vector3(0.5f, 0.5f, 0.5f));
	CreateObject<GrapplePointObject>(PizzaBox::Vector3(0.0f, 60.0f, -1250.0f), PizzaBox::Euler(), PizzaBox::Vector3(0.5f, 0.5f, 0.5f));
	CreateObject<GrapplePointObject>(PizzaBox::Vector3(10.0f, 60.0f, -1300.0f), PizzaBox::Euler(), PizzaBox::Vector3(0.5f, 0.5f, 0.5f));
	CreateObject<GrapplePointObject>(PizzaBox::Vector3(20.0f, 60.0f, -1350.0f), PizzaBox::Euler(), PizzaBox::Vector3(0.5f, 0.5f, 0.5f));
	CreateObject<GrapplePointObject>(PizzaBox::Vector3(0.0f, 60.0f, -1400.0f), PizzaBox::Euler(), PizzaBox::Vector3(0.5f, 0.5f, 0.5f));
	CreateObject<GrapplePointObject>(PizzaBox::Vector3(0.0f, 70.0f, -1475.0f), PizzaBox::Euler(), PizzaBox::Vector3(0.5f, 0.5f, 0.5f));
	CreateObject<GrapplePointObject>(PizzaBox::Vector3(0.0f, 70.0f, -1560.0f), PizzaBox::Euler(), PizzaBox::Vector3(0.5f, 0.5f, 0.5f));

	auto endLevelObj = CreateObject<PizzaBox::GameObject>(PizzaBox::Vector3(0.0f, 38.2f, -1589.25f), PizzaBox::Euler(-90.0f, 90.0f, 0.0f), PizzaBox::Vector3(0.85f, 0.85f, 0.85f));
	endLevelObj->SetTag("EndLevelTrigger");
	endLevelObj->AddComponent(new PizzaBox::MeshRender("DoorModel", "DoorTexture"));

	//Test Water Object
	PizzaBox::GameObject* baseWater = CreateObject<PizzaBox::GameObject>(PizzaBox::Vector3(0.0f, -20.0f, 0.0f), PizzaBox::Euler(), PizzaBox::Vector3(140.0f, 40.0f, 140.0f));
	auto water = new PizzaBox::WaterMaterial("WaterTexture", "", "", 32.0f, 256.0f);
	water->SetWaveParamaters(PizzaBox::Vector4(2.0f, 4.0f, 4.0f, 2.0f), PizzaBox::Vector4(0.8f, 0.2f, 0.2f, 0.2f), PizzaBox::Vector4(0.4f, 0.4f, 0.4f, 0.2f));
	water->SetFlowDirection(PizzaBox::Vector2(0.0f, 1.0f));
	auto mr = new PizzaBox::MeshRender("WaterMesh", water);
	mr->SetCastsShadows(false);
	baseWater->AddComponent(mr);

	//Background Design
	for(int i = 0; i < 30; i++){
		float randomPositionx = PizzaBox::Random::Range(-50.0, 50.0f);
		float randomPositiony = PizzaBox::Random::Range(-100.0f, 100.0f);
		float randomPositionz = PizzaBox::Random::Range(-25.0f, 25.0f);
		CreateObject<BuildingScenery>(PizzaBox::Vector3(-400.0f + randomPositionx, -5.0f + randomPositiony, 400.0f - (i * 150.0f + randomPositionz)), PizzaBox::Euler(), PizzaBox::Vector3(100.0f, 300.0f, 100.0f));
		CreateObject<BuildingScenery>(PizzaBox::Vector3(400.0f + randomPositionx, -5.0f + randomPositiony, 400.0f - (i * 150.0f + randomPositionz)), PizzaBox::Euler(), PizzaBox::Vector3(100.0f, 300.0f, 100.0f));
		CreateObject<BuildingScenery>(PizzaBox::Vector3(-600.0f + randomPositionx, -5.0f + randomPositiony, 400.0f - (i * 150.0f + randomPositionz)), PizzaBox::Euler(), PizzaBox::Vector3(100.0f, 300.0f, 100.0f));
		CreateObject<BuildingScenery>(PizzaBox::Vector3(600.0f + randomPositionx, -5.0f + randomPositiony, 400.0f - (i * 150.0f + randomPositionz)), PizzaBox::Euler(), PizzaBox::Vector3(100.0f, 300.0f, 100.0f));
		CreateObject<BuildingScenery>(PizzaBox::Vector3(-300.0f + randomPositionx, -5.0f + randomPositiony, 200.0f - (i * 1200.0f + randomPositionz)), PizzaBox::Euler(25.0f + randomPositionx, 0.0f + randomPositiony, 0.0f), PizzaBox::Vector3(100.0f, 300.0f, 100.0f), false, false);
		CreateObject<BuildingScenery>(PizzaBox::Vector3(300.0f + randomPositionx, -5.0f + randomPositiony, 200.0f - (i * 1200.0f + randomPositionz)), PizzaBox::Euler(25.0f + randomPositionx, 90.0f + randomPositiony, 0.0f), PizzaBox::Vector3(100.0f, 300.0f, 100.0f), false, false);
	}

	PizzaBox::UIManager::EnableSet("MainMenuSet");
	  
	return true;
}

void MainMenuScene::Destroy(){
	Scene::Destroy();
}