#include "Level2.h"

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

Level2::Level2() : Scene() {
}

Level2::~Level2() {
}

bool Level2::Initialize() {
	PizzaBox::RenderEngine::SetFogDensity(0.0010f);
	PizzaBox::RenderEngine::SetWaterFogDensity(0.0010f);

	constexpr float skySize = 5000.0f;

	//SkyBox
	SetSky(new PizzaBox::SkyBox("SummerSkyBox", skySize));

	//Music
	auto gpm1 = new PizzaBox::AudioSource("GameplayMusic2", PizzaBox::AudioSource::SoundType::_2D, "Music");
	PizzaBox::GameObject* music = CreateObject<PizzaBox::GameObject>(PizzaBox::Vector3(0.0f, 55.0f, 80.0f), PizzaBox::Euler(-15.0f, 0.0f, 0.0f));
	music->AddComponent(gpm1);
	music->AddComponent(new MusicScript(gpm1));

	//Waves
	auto wve1 = new PizzaBox::AudioSource("WavesSFXQuiet", PizzaBox::AudioSource::SoundType::_2D, "SFX");
	PizzaBox::GameObject* waves = CreateObject<PizzaBox::GameObject>(PizzaBox::Vector3(0.0f, 55.0f, 80.0f), PizzaBox::Euler(-15.0f, 0.0f, 0.0f));
	waves->AddComponent(wve1);
	waves->AddComponent(new MusicScript(wve1));
	//Water
	PizzaBox::GameObject* baseWater = CreateObject<PizzaBox::GameObject>(PizzaBox::Vector3(0.0f, -20.0f, 0.0f), PizzaBox::Euler(), PizzaBox::Vector3(140.0f, 40.0f, 140.0f));
	auto water = new PizzaBox::WaterMaterial("WaterTexture", "", "", 32.0f, 256.0f);
	water->SetWaveParamaters(PizzaBox::Vector4(2.0f, 4.0f, 4.0f, 2.0f), PizzaBox::Vector4(0.8f, 0.2f, 0.2f, 0.2f), PizzaBox::Vector4(0.4f, 0.4f, 0.4f, 0.2f));
	water->SetFlowDirection(PizzaBox::Vector2(0.0f, 1.0f));
	auto mr = new PizzaBox::MeshRender("WaterMesh", water);
	mr->SetCastsShadows(false);
	baseWater->AddComponent(mr);

	//Camera
	PizzaBox::GameObject* mainCamera = CreateObject<PizzaBox::GameObject>(PizzaBox::Vector3(0.0f, 0.0f, -1600), PizzaBox::Euler(-15.0f, 0.0f, 0.0f));
	mainCamera->SetTag("Camera");
	auto cam = new PizzaBox::Camera(PizzaBox::ViewportRect::fullScreen, PizzaBox::Camera::RenderMode::Perspective);
	cam->SetFarPlane(skySize);
	mainCamera->AddComponent(cam);
	auto controller = new CameraController();
	mainCamera->AddComponent(controller);
	mainCamera->AddComponent(new PizzaBox::AudioListener());

	//mainCamera->AddComponent(new MusicScript(as1));

	//Directional Light
	auto dirLight = CreateObject<PizzaBox::GameObject>(PizzaBox::Vector3(400.0f,400.0f,-4600.0f), PizzaBox::Euler(-35.0f, 12.0f, 0.0f));
	dirLight->AddComponent(new PizzaBox::DirectionalLight(2.0f));

	auto gameController = CreateObject<PizzaBox::GameObject>();
	gameController->AddComponent(new GameController(PizzaBox::Vector3(0.0f, 200.0f, -1600.0f), PizzaBox::Euler(0.0f, 180.0f, 0.0f)));

	CreateObject<Building>(PizzaBox::Vector3(0.0f, -20.0f, -1105.0f), PizzaBox::Euler(/*-25.0f*/), PizzaBox::Vector3(40.0f, 100.0f, 40.0f), "BrickTextureThree");
	CreateObject<Platform>(PizzaBox::Vector3(0.0f, 60.0f, -1600.0f), PizzaBox::Euler(), PizzaBox::Vector3(70.0f, 10.0f, 30.0f), "GoldTexture", 128,false);
	CreateObject<Platform>(PizzaBox::Vector3(0.0f, 80.0f, -1600.0f), PizzaBox::Euler(), PizzaBox::Vector3(70.0f, 10.0f, 30.0f), "GoldTexture", 128, false);
	CreateObject<Platform>(PizzaBox::Vector3(0.0f, 100.0f, -1600.0f), PizzaBox::Euler(), PizzaBox::Vector3(70.0f, 10.0f, 30.0f), "GoldTexture", 128, false);
	CreateObject<Platform>(PizzaBox::Vector3(0.0f, 120.0f, -1600.0f), PizzaBox::Euler(), PizzaBox::Vector3(70.0f, 10.0f, 30.0f), "GoldTexture", 128, false);
	CreateObject<Building>(PizzaBox::Vector3(0.0f, -5.0f, -1600.0f), PizzaBox::Euler(), PizzaBox::Vector3(60.0f, 300.0f, 20.0f), "BrickTextureTwo", 64, true);
	//2nd building
	CreateObject<Building>(PizzaBox::Vector3(0.0f, -5.0f, -1700.0f), PizzaBox::Euler(), PizzaBox::Vector3(60.0f, 295.0f, 60.0f), "BrickTextureFour", 64, true, true, 20.0f);
	CreateObject<Building>(PizzaBox::Vector3(2.0f, -5.0f, -1800.0f), PizzaBox::Euler(), PizzaBox::Vector3(60.0f, 295.0f, 60.0f), "BrickTextureTwo", 64);
	CreateObject<Building>(PizzaBox::Vector3(4.0f, -5.0f, -1950.0f), PizzaBox::Euler(), PizzaBox::Vector3(60.0f, 295.0f, 60.0f), "BrickTextureThree", 64);
	CreateObject<Building>(PizzaBox::Vector3(6.0f, -5.0f, -2050.0f), PizzaBox::Euler(), PizzaBox::Vector3(60.0f, 295.0f, 60.0f), "BrickTextureFour", 64);
	CreateObject<Building>(PizzaBox::Vector3(8.0f, -5.0f, -2150.0f), PizzaBox::Euler(), PizzaBox::Vector3(60.0f, 295.0f, 60.0f), "BrickTextureFive", 64);
	CreateObject<Building>(PizzaBox::Vector3(10.0f, -5.0f, -2300.0f), PizzaBox::Euler(), PizzaBox::Vector3(30.0f, 400.0f, 30.0f), "BrickTexture", 64);
	CreateObject<Building>(PizzaBox::Vector3(12.0f, -5.0f, -2400.0f), PizzaBox::Euler(), PizzaBox::Vector3(30.0f, 400.0f, 30.0f), "BrickTextureTwo", 64);
	CreateObject<Building>(PizzaBox::Vector3(14.0f, -5.0f, -2450.0f), PizzaBox::Euler(), PizzaBox::Vector3(30.0f, 400.0f, 30.0f), "BrickTextureThree", 64);
	CreateObject<Building>(PizzaBox::Vector3(16.0f, -5.0f, -2500.0f), PizzaBox::Euler(), PizzaBox::Vector3(30.0f, 400.0f, 30.0f), "BrickTextureFive", 64);

	CreateObject<Building>(PizzaBox::Vector3(55.0f, -5.0f, -2550.0f), PizzaBox::Euler(), PizzaBox::Vector3(60.0f, 375.0f, 60.0f), "BrickTextureThree", 64);

	CreateObject<Building>(PizzaBox::Vector3(55.0f, -5.0f, -2650.0f), PizzaBox::Euler(), PizzaBox::Vector3(100.0f, 375.0f, 50.0f), "BrickTextureThree", 64);
	CreateObject<Building>(PizzaBox::Vector3(0.0f, -5.0f, -2750.0f), PizzaBox::Euler(), PizzaBox::Vector3(125.0f, 365.0f, 50.0f), "BrickTextureThree", 64);
	
	CreateObject<Building>(PizzaBox::Vector3(0.0f, -5.0f, -2850.0f), PizzaBox::Euler(), PizzaBox::Vector3(125.0f, 315.0f, 50.0f),"BrickTextureTwo", 64, true, true);
	
	CreateObject<Building>(PizzaBox::Vector3(0.0f, -5.0f, -2950.0f), PizzaBox::Euler(), PizzaBox::Vector3(125.0f, 295.0f, 50.0f), "BrickTextureFour", 64);
	
	CreateObject<Building>(PizzaBox::Vector3(0.0f, -5.0f, -3050.0f), PizzaBox::Euler(), PizzaBox::Vector3(125.0f, 285.0f, 50.0f), "BrickTextureFive", 64, true, true);
	
	
	CreateObject<Building>(PizzaBox::Vector3(0.0f, -5.0f, -3150.0f), PizzaBox::Euler(), PizzaBox::Vector3(20.0f, 275.0f, 50.0f), "BrickTextureFive", 64);

	CreateObject<Building>(PizzaBox::Vector3(0.0f, -5.0f, -3350.0f), PizzaBox::Euler(), PizzaBox::Vector3(20.0f, 275.0f, 50.0f), "BrickTextureThree", 64, true, true);

	CreateObject<Building>(PizzaBox::Vector3(0.0f, -5.0f, -3580.0f), PizzaBox::Euler(), PizzaBox::Vector3(50.0f, 275.0f, 50.0f), "BrickTextureFour", 64);

	CreateObject<Building>(PizzaBox::Vector3(0.0f, -5.0f, -3700.0f), PizzaBox::Euler(), PizzaBox::Vector3(50.0f, 275.0f, 50.0f), "BrickTextureTwo", 64, true, true);
	
	CreateObject<Building>(PizzaBox::Vector3(0.0f, -5.0f, -3800.0f), PizzaBox::Euler(), PizzaBox::Vector3(50.0f, 265.0f, 50.0f), "BrickTextureThree", 64);
	
	CreateObject<Building>(PizzaBox::Vector3(0.0f, -5.0f, -3900.0f), PizzaBox::Euler(), PizzaBox::Vector3(50.0f, 250.0f, 50.0f), "BrickTextureTwo", 64, true, true);

	CreateObject<Building>(PizzaBox::Vector3(0.0f, -5.0f, -4000.0f), PizzaBox::Euler(), PizzaBox::Vector3(150.0f, 230.0f, 50.0f), "BrickTexture", 64, true, true, 1.0f);

	CreateObject<Building>(PizzaBox::Vector3(-50.0f, -5.0f, -4100.0f), PizzaBox::Euler(), PizzaBox::Vector3(50.0f, 230.0f, 50.0f), "BrickTexture", 64);

	CreateObject<Building>(PizzaBox::Vector3(-40.0f, -5.0f, -4200.0f), PizzaBox::Euler(), PizzaBox::Vector3(50.0f, 180.0f, 50.0f), "BrickTextureTwo", 64);

	CreateObject<Building>(PizzaBox::Vector3(-40.0f, -5.0f, -4300.0f), PizzaBox::Euler(), PizzaBox::Vector3(50.0f, 100.0f, 50.0f), "BrickTextureFour", 64);

	CreateObject<Building>(PizzaBox::Vector3(-40.0f, -5.0f, -4400.0f), PizzaBox::Euler(), PizzaBox::Vector3(50.0f, 100.0f, 50.0f), "BrickTexture", 64);

	CreateObject<Building>(PizzaBox::Vector3(-40.0f, -5.0f, -4500.0f), PizzaBox::Euler(), PizzaBox::Vector3(50.0f, 100.0f, 50.0f), "BrickTextureFive", 64);

	CreateObject<Building>(PizzaBox::Vector3(-40.0f, -5.0f, -4600.0f), PizzaBox::Euler(), PizzaBox::Vector3(50.0f, 100.0f, 50.0f), "BrickTextureThree", 64);

	CreateObject<Building>(PizzaBox::Vector3(0.0f, 10.0f, -4700.0f), PizzaBox::Euler(), PizzaBox::Vector3(100.0f, 300.0f, 20.0f), "BrickTextureTwo", 64);


	CreateObject<Platform>(PizzaBox::Vector3(0.0f, 45.0f, -4700.0f), PizzaBox::Euler(), PizzaBox::Vector3(120.0f, 5.0f, 60.0f));
	CreateObject<Platform>(PizzaBox::Vector3(0.0f, -5.0f, -3430.0f), PizzaBox::Euler(), PizzaBox::Vector3(10.0f, 265.0f, 10.0f), "WoodTexture", 16);
	CreateObject<Platform>(PizzaBox::Vector3(0.0f, -5.0f, -3530.0f), PizzaBox::Euler(), PizzaBox::Vector3(15.0f, 265.0f, 15.0f), "WoodTexture", 16);


	CreateObject<GrapplePointObject>(PizzaBox::Vector3(0.0f, 170.0f, -1650.0f), PizzaBox::Euler(), PizzaBox::Vector3(0.5f, 0.5f, 0.5f));
	CreateObject<GrapplePointObject>(PizzaBox::Vector3(0.0f, 170.0f, -1750.0f), PizzaBox::Euler(), PizzaBox::Vector3(0.5f, 0.5f, 0.5f));
	CreateObject<GrapplePointObject>(PizzaBox::Vector3(0.0f, 170.0f, -1850.0f), PizzaBox::Euler(), PizzaBox::Vector3(0.5f, 0.5f, 0.5f));
	CreateObject<GrapplePointObject>(PizzaBox::Vector3(0.0f, 170.0f, -2000.0f), PizzaBox::Euler(), PizzaBox::Vector3(0.5f, 0.5f, 0.5f));
	CreateObject<GrapplePointObject>(PizzaBox::Vector3(0.0f, 174.0f, -1900.0f), PizzaBox::Euler(), PizzaBox::Vector3(0.5f, 0.5f, 0.5f));
	CreateObject<GrapplePointObject>(PizzaBox::Vector3(20.0f, 170.0f, -2100.0f), PizzaBox::Euler(), PizzaBox::Vector3(0.5f, 0.5f, 0.5f));
	CreateObject<GrapplePointObject>(PizzaBox::Vector3(20.0f, 175.0f, -2200.0f), PizzaBox::Euler(), PizzaBox::Vector3(0.5f, 0.5f, 0.5f));
	CreateObject<GrapplePointObject>(PizzaBox::Vector3(25.0f, 180.0f, -2250.0f), PizzaBox::Euler(), PizzaBox::Vector3(0.5f, 0.5f, 0.5f));
	CreateObject<GrapplePointObject>(PizzaBox::Vector3(30.0f, 185.0f, -2300.0f), PizzaBox::Euler(), PizzaBox::Vector3(0.5f, 0.5f, 0.5f));
	CreateObject<GrapplePointObject>(PizzaBox::Vector3(35.0f, 190.0f, -2300.0f), PizzaBox::Euler(), PizzaBox::Vector3(0.5f, 0.5f, 0.5f));
	CreateObject<GrapplePointObject>(PizzaBox::Vector3(40.0f, 195.0f, -2350.0f), PizzaBox::Euler(), PizzaBox::Vector3(0.5f, 0.5f, 0.5f));
	CreateObject<GrapplePointObject>(PizzaBox::Vector3(45.0f, 205.0f, -2400.0f), PizzaBox::Euler(), PizzaBox::Vector3(0.5f, 0.5f, 0.5f));
	CreateObject<GrapplePointObject>(PizzaBox::Vector3(50.0f, 210.0f, -2450.0f), PizzaBox::Euler(), PizzaBox::Vector3(0.5f, 0.5f, 0.5f));
	CreateObject<GrapplePointObject>(PizzaBox::Vector3(55.0f, 215.0f, -2500.0f), PizzaBox::Euler(), PizzaBox::Vector3(0.5f, 0.5f, 0.5f));
	CreateObject<GrapplePointObject>(PizzaBox::Vector3(55.0f, 215.0f, -2600.0f), PizzaBox::Euler(), PizzaBox::Vector3(0.5f, 0.5f, 0.5f));
	CreateObject<GrapplePointObject>(PizzaBox::Vector3(0.0f, 215.0f, -2700.0f), PizzaBox::Euler(), PizzaBox::Vector3(0.5f, 0.5f, 0.5f));
	CreateObject<GrapplePointObject>(PizzaBox::Vector3(0.0f, 205.0f, -2800.0f), PizzaBox::Euler(), PizzaBox::Vector3(0.5f, 0.5f, 0.5f));
	CreateObject<GrapplePointObject>(PizzaBox::Vector3(0.0f, 185.0f, -2900.0f), PizzaBox::Euler(), PizzaBox::Vector3(0.5f, 0.5f, 0.5f));
	CreateObject<GrapplePointObject>(PizzaBox::Vector3(0.0f, 185.0f, -3000.0f), PizzaBox::Euler(), PizzaBox::Vector3(0.5f, 0.5f, 0.5f));
	CreateObject<GrapplePointObject>(PizzaBox::Vector3(0.0f, 165.0f, -3100.0f), PizzaBox::Euler(), PizzaBox::Vector3(0.5f, 0.5f, 0.5f));
	CreateObject<GrapplePointObject>(PizzaBox::Vector3(0.0f, 165.0f, -3200.0f), PizzaBox::Euler(), PizzaBox::Vector3(0.5f, 0.5f, 0.5f));
	CreateObject<GrapplePointObject>(PizzaBox::Vector3(0.0f, 165.0f, -3250.0f), PizzaBox::Euler(), PizzaBox::Vector3(0.5f, 0.5f, 0.5f));
	CreateObject<GrapplePointObject>(PizzaBox::Vector3(0.0f, 165.0f, -3300.0f), PizzaBox::Euler(), PizzaBox::Vector3(0.5f, 0.5f, 0.5f));
	CreateObject<GrapplePointObject>(PizzaBox::Vector3(0.0f, 165.0f, -3400.0f), PizzaBox::Euler(), PizzaBox::Vector3(0.5f, 0.5f, 0.5f));
	CreateObject<GrapplePointObject>(PizzaBox::Vector3(0.0f, 160.0f, -3450.0f), PizzaBox::Euler(), PizzaBox::Vector3(0.5f, 0.5f, 0.5f));
	CreateObject<GrapplePointObject>(PizzaBox::Vector3(0.0f, 160.0f, -3500.0f), PizzaBox::Euler(), PizzaBox::Vector3(0.5f, 0.5f, 0.5f));
	CreateObject<GrapplePointObject>(PizzaBox::Vector3(0.0f, 160.0f, -3550.0f), PizzaBox::Euler(), PizzaBox::Vector3(0.5f, 0.5f, 0.5f));
	CreateObject<GrapplePointObject>(PizzaBox::Vector3(0.0f, 165.0f, -3625.0f), PizzaBox::Euler(), PizzaBox::Vector3(0.5f, 0.5f, 0.5f));
	CreateObject<GrapplePointObject>(PizzaBox::Vector3(0.0f, 170.0f, -3675.0f), PizzaBox::Euler(), PizzaBox::Vector3(0.5f, 0.5f, 0.5f));
	CreateObject<GrapplePointObject>(PizzaBox::Vector3(0.0f, 160.0f, -3750.0f), PizzaBox::Euler(), PizzaBox::Vector3(0.5f, 0.5f, 0.5f));
	CreateObject<GrapplePointObject>(PizzaBox::Vector3(0.0f, 155.0f, -3850.0f), PizzaBox::Euler(), PizzaBox::Vector3(0.5f, 0.5f, 0.5f));
	CreateObject<GrapplePointObject>(PizzaBox::Vector3(0.0f, 150.0f, -3950.0f), PizzaBox::Euler(), PizzaBox::Vector3(0.5f, 0.5f, 0.5f));
	CreateObject<GrapplePointObject>(PizzaBox::Vector3(-50.0f, 140.0f, -4050.0f), PizzaBox::Euler(), PizzaBox::Vector3(0.5f, 0.5f, 0.5f));
	CreateObject<GrapplePointObject>(PizzaBox::Vector3(-40.0f, 120.0f, -4150.0f), PizzaBox::Euler(), PizzaBox::Vector3(0.5f, 0.5f, 0.5f));
	CreateObject<GrapplePointObject>(PizzaBox::Vector3(-40.0f, 120.0f, -4250.0f), PizzaBox::Euler(), PizzaBox::Vector3(0.5f, 0.5f, 0.5f));
	CreateObject<GrapplePointObject>(PizzaBox::Vector3(-40.0f, 65.0f, -4350.0f), PizzaBox::Euler(), PizzaBox::Vector3(0.5f, 0.5f, 0.5f));
	CreateObject<GrapplePointObject>(PizzaBox::Vector3(-40.0f, 65.0f, -4450.0f), PizzaBox::Euler(), PizzaBox::Vector3(0.5f, 0.5f, 0.5f));
	CreateObject<GrapplePointObject>(PizzaBox::Vector3(-40.0f, 65.0f, -4550.0f), PizzaBox::Euler(), PizzaBox::Vector3(0.5f, 0.5f, 0.5f));
	CreateObject<GrapplePointObject>(PizzaBox::Vector3(-40.0f, 65.0f, -4650.0f), PizzaBox::Euler(), PizzaBox::Vector3(0.5f, 0.5f, 0.5f));

	auto endLevelObj = CreateObject<PizzaBox::GameObject>(PizzaBox::Vector3(0.0f, 48.2f, -4689.25f), PizzaBox::Euler(-90.0f, 90.0f, 0.0f), PizzaBox::Vector3(0.85f, 0.85f, 0.85f));
	endLevelObj->SetTag("EndLevelTrigger");
	endLevelObj->AddComponent(new PizzaBox::MeshRender("DoorModel", "DoorTexture"));
	endLevelObj->AddComponent(new PizzaBox::Collider(endLevelObj->GlobalScale()));
	endLevelObj->AddComponent(new EndLevelTrigger());
	
	//LEVEL ONE BACKGROUND DETAILS

	CreateObject<Building>(PizzaBox::Vector3(0.0f, 30.0f, 200.0f), PizzaBox::Euler(), PizzaBox::Vector3(20.0f, 100.0f, 20.0f), "BrickTextureFive", 32.0f, false);
	CreateObject<Building>(PizzaBox::Vector3(0.0f, 23.0f, 200.0f), PizzaBox::Euler(), PizzaBox::Vector3(200.0f, 100.0f, 200.0f), "BrickTextureTwo", 32.0f, false);
	CreateObject<Building>(PizzaBox::Vector3(0.0f, 34.0f, 150.0f), PizzaBox::Euler(), PizzaBox::Vector3(40.0f, 100.0f, 40.0f), "BrickTextureThree", 32.0f, false);
	CreateObject<Building>(PizzaBox::Vector3(0.0f, 34.0f, 100.0f), PizzaBox::Euler(), PizzaBox::Vector3(60.0f, 100.0f, 20.0f), "BrickTextureFour", 32.0f, false);


	CreateObject<Building>(PizzaBox::Vector3(0.0f, -5.0f, 15.0f), PizzaBox::Euler(), PizzaBox::Vector3(50.0f, 100.0f, 50.0f), "BrickTextureTwo", 32.0f, false);

	CreateObject<Building>(PizzaBox::Vector3(0.0f, -5.0f, -120.0f), PizzaBox::Euler(), PizzaBox::Vector3(32.0f, 100.0f, 32.0f), "BrickTextureFive", 32.0f, false);
	CreateObject<Building>(PizzaBox::Vector3(0.0f, -5.0f, -280.0f), PizzaBox::Euler(/*-25.0f*/), PizzaBox::Vector3(20.0f, 100.0f, 20.0f), "BrickTextureTwo", 32.0f, false);

	CreateObject<Building>(PizzaBox::Vector3(0.0f, -10.0f, -805.0f), PizzaBox::Euler(/*-25.0f*/), PizzaBox::Vector3(40.0f, 100.0f, 20.0f),"BrickTexture", 32, false);


	CreateObject<Platform>(PizzaBox::Vector3(0.0f, 40.0f, -55.0f), PizzaBox::Euler(), PizzaBox::Vector3(32.0f, 2.0f, 32.0f),"WoodTexture", 10.0f, false);
	CreateObject<Platform>(PizzaBox::Vector3(0.0f, 45.0f, -150.0f), PizzaBox::Euler(), PizzaBox::Vector3(24.0f, 2.0f, 24.0f), "WoodTexture", 10.0f, false);
	CreateObject<Platform>(PizzaBox::Vector3(0.0f, 40.0f, -375.0f), PizzaBox::Euler(), PizzaBox::Vector3(24.0f, 2.0f, 24.0f), "WoodTexture", 10.0f, false);
	CreateObject<Platform>(PizzaBox::Vector3(0.0f, 35.0f, -450.0f), PizzaBox::Euler(), PizzaBox::Vector3(32.0f, 5.0f, 32.0f), "WoodTexture", 10.0f, false);
	CreateObject<Platform>(PizzaBox::Vector3(0.0f, 35.0f, -500.0f), PizzaBox::Euler(), PizzaBox::Vector3(32.0f, 5.0f, 32.0f), "WoodTexture", 10.0f, false);
	CreateObject<Platform>(PizzaBox::Vector3(0.0f, 35.0f, -550.0f), PizzaBox::Euler(), PizzaBox::Vector3(32.0f, 5.0f, 32.0f), "WoodTexture", 10.0f, false);
	CreateObject<Platform>(PizzaBox::Vector3(0.0f, 35.0f, -600.0f), PizzaBox::Euler(), PizzaBox::Vector3(32.0f, 5.0f, 32.0f), "WoodTexture", 10.0f, false);
	CreateObject<Platform>(PizzaBox::Vector3(0.0f, 35.0f, -650.0f), PizzaBox::Euler(), PizzaBox::Vector3(16.0f, 5.0f, 32.0f), "WoodTexture", 10.0f, false);
	CreateObject<Platform>(PizzaBox::Vector3(0.0f, 35.0f, -700.0f), PizzaBox::Euler(), PizzaBox::Vector3(16.0f, 5.0f, 32.0f), "WoodTexture", 10.0f, false);
	CreateObject<Platform>(PizzaBox::Vector3(0.0f, 37.0f, -750.0f), PizzaBox::Euler(), PizzaBox::Vector3(16.0f, 5.0f, 32.0f), "WoodTexture", 10.0f, false);

	CreateObject<Platform>(PizzaBox::Vector3(0.0f, 25.0f, -975.0f), PizzaBox::Euler(), PizzaBox::Vector3(52.0f, 5.0f, 52.0f), "WoodTexture", 10.0f, false);
	CreateObject<Platform>(PizzaBox::Vector3(0.0f, 25.0f, -1450.0f), PizzaBox::Euler(), PizzaBox::Vector3(52.0f, 5.0f, 52.0f), "WoodTexture", 10.0f, false);
	CreateObject<Platform>(PizzaBox::Vector3(0.0f, 25.0f, -1525.0f), PizzaBox::Euler(), PizzaBox::Vector3(52.0f, 5.0f, 52.0f), "WoodTexture", 10.0f, false);

	CreateObject<Platform>(PizzaBox::Vector3(0.0f, 35.0f, -1600.0f), PizzaBox::Euler(), PizzaBox::Vector3(80.0f, 5.0f, 60.0f), "WoodTexture", 10.0f, false);


	auto oldDoor = CreateObject<PizzaBox::GameObject>(PizzaBox::Vector3(0.0f, 38.2f, -1589.25f), PizzaBox::Euler(-90.0f, 90.0f, 0.0f), PizzaBox::Vector3(0.85f, 0.85f, 0.85f));
	oldDoor->AddComponent(new PizzaBox::MeshRender("DoorModel", "DoorTexture"));


	//Background Design
	for (int i = 0; i < 40; i++) {
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

	return true;
}

void Level2::Destroy() {
	Scene::Destroy();
}