#include "Level1.h"

#include <Animation/AnimMeshRender.h> 
#include <Graphics/Sky/SkyBox.h>
#include <Graphics/Camera.h>
#include <Graphics/Models/MeshRender.h>
#include <Graphics/Materials/ColorMaterial.h>
#include <Graphics/Materials/TexturedMaterial.h>
#include <Graphics/Materials/WaterMaterial.h>
#include <Physics/Collider.h>
#include <Physics/Rigidbody.h>
#include <Audio/AudioListener.h>
#include <Audio/AudioSource.h>

#include "Animators/PlayerAnimator.h"
#include "Objects/Building.h"
#include "Objects/GrapplePointObject.h"
#include "Objects/Platform.h"
#include "Objects/Player.h"
#include "Scripts/CharacterController.h"
#include "Scripts/MusicScript.h"
#include "Scripts/CameraController.h"
#include "Scripts/GrapplePoint.h"
#include "Scripts/PlayerController.h"
#include "Scripts/MovingPlatform.h"

using namespace GamePackage;

Level1::Level1() : Scene(){
}
 
Level1::~Level1(){
}

bool Level1::Initialize(){
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
	mainCamera->SetTag("Camera");
	auto cam = new PizzaBox::Camera(PizzaBox::ViewportRect::fullScreen, PizzaBox::Camera::RenderMode::Perspective);
	mainCamera->AddComponent(cam);
	auto controller = new CameraController();
	mainCamera->AddComponent(controller);
	mainCamera->AddComponent(new PizzaBox::AudioListener());

	//mainCamera->AddComponent(new MusicScript(as1));

	//Directional Light
	auto dirLight = CreateObject<PizzaBox::GameObject>(PizzaBox::Vector3(), PizzaBox::Euler(-35.0f, 12.0f, 0.0f));
	dirLight->AddComponent(new PizzaBox::DirectionalLight(2.0f));

	//player
	PizzaBox::GameObject* player = CreateObject<Player>(PizzaBox::Vector3(0.0f, 60.0f, 0.0f), PizzaBox::Euler(0.0f, 180.0f, 0.0f), PizzaBox::Vector3(0.01f, 0.01f, 0.01f));
	controller->SetTarget(player);

	//Grapple Point
	//auto grapplePoint = CreateObject<PizzaBox::GameObject>(PizzaBox::Vector3(0.0f, 50.0f, -50.0f), PizzaBox::Euler(), PizzaBox::Vector3::Fill(2.0f));
	//grapplePoint->AddComponent(new PizzaBox::MeshRender("SphereModel", new PizzaBox::ColorMaterial(PizzaBox::Color::Yellow)));
	//grapplePoint->AddComponent(new GrapplePoint(35.0f));

	//Test Static platfrom
	CreateObject<Building>(PizzaBox::Vector3(0.0f, -5.0f, 0.0f), PizzaBox::Euler(), PizzaBox::Vector3(20.0f, 100.0f, 20.0f));
	CreateObject<Building>(PizzaBox::Vector3(0.0f, -5.0f, -120.0f), PizzaBox::Euler(), PizzaBox::Vector3(20.0f, 100.0f, 20.0f));
	CreateObject<Building>(PizzaBox::Vector3(0.0f, -5.0f, -280.0f), PizzaBox::Euler(/*-25.0f*/), PizzaBox::Vector3(20.0f, 100.0f, 20.0f));
	CreateObject<Building>(PizzaBox::Vector3(0.0f, -5.0f, -600.0f), PizzaBox::Euler(), PizzaBox::Vector3(20.0f, 300.0f, 20.0f));

	CreateObject<Platform>(PizzaBox::Vector3(0.0f, 40.0f, -60.0f), PizzaBox::Euler(), PizzaBox::Vector3(12.0f, 4.0f, 12.0f));
	CreateObject<Platform>(PizzaBox::Vector3(0.0f, 45.0f, -150.0f), PizzaBox::Euler(), PizzaBox::Vector3(12.0f, 4.0f, 32.0f));
	CreateObject<Platform>(PizzaBox::Vector3(0.0f, 40.0f, -355.0f), PizzaBox::Euler(), PizzaBox::Vector3(8.0f, 4.0f, 8.0f));
	CreateObject<Platform>(PizzaBox::Vector3(0.0f, 60.0f, -440.0f), PizzaBox::Euler(), PizzaBox::Vector3(4.0f, 4.0f, 8.0f));
	CreateObject<Platform>(PizzaBox::Vector3(0.0f, 45.0f, -600.0f), PizzaBox::Euler(), PizzaBox::Vector3(32.0f, 10.0f, 32.0f));

	//Grapple Points
	CreateObject<GrapplePointObject>(PizzaBox::Vector3(0.0f, 60.0f, -30.0f), PizzaBox::Euler(), PizzaBox::Vector3(2.0f, 2.0f, 2.0f));
	CreateObject<GrapplePointObject>(PizzaBox::Vector3(0.0f, 60.0f, -90.0f), PizzaBox::Euler(), PizzaBox::Vector3(2.0f, 2.0f, 2.0f));
	//CreateObject<GrapplePointObject>(PizzaBox::Vector3(0.0f, 60.0f, -120.0f), PizzaBox::Euler(), PizzaBox::Vector3(2.0f, 2.0f, 2.0f));
	//CreateObject<GrapplePointObject>(PizzaBox::Vector3(0.0f, 60.0f, -150.0f), PizzaBox::Euler(), PizzaBox::Vector3(2.0f, 2.0f, 2.0f));
	CreateObject<GrapplePointObject>(PizzaBox::Vector3(0.0f, 65.0f, -190.0f), PizzaBox::Euler(), PizzaBox::Vector3(2.0f, 2.0f, 2.0f));
	CreateObject<GrapplePointObject>(PizzaBox::Vector3(0.0f, 70.0f, -240.0f), PizzaBox::Euler(), PizzaBox::Vector3(2.0f, 2.0f, 2.0f));

	//Test Water Object
	PizzaBox::GameObject* baseWater = CreateObject<PizzaBox::GameObject>(PizzaBox::Vector3(0.0f, 0.0f, 0.0f), PizzaBox::Euler(), PizzaBox::Vector3(140.0f, 40.0f, 140.0f));
	auto water = new PizzaBox::WaterMaterial("WaterTexture", "", "", 32.0f, 512.0f);
	water->SetWaveParamaters(PizzaBox::Vector4(2.0f, 4.0f, 4.0f, 2.0f), PizzaBox::Vector4(0.8f, 0.2f, 0.2f, 0.2f), PizzaBox::Vector4(0.4f, 0.4f, 0.4f, 0.2f));
	baseWater->AddComponent(new PizzaBox::MeshRender("WaterMesh", water));

	//Background Design
	for(int i = 0; i < 30; i++){
		PizzaBox::GameObject* backgroundHouse1 = CreateObject<Building>(PizzaBox::Vector3(-400.0f, -5.0f, 400.0f - (i * 150.0f)), PizzaBox::Euler(), PizzaBox::Vector3(100.0f, 300.0f, 100.0f));
		PizzaBox::GameObject* backgroundHouse2 = CreateObject<Building>(PizzaBox::Vector3(400.0f, -5.0f, 400.0f - (i * 150.0f)), PizzaBox::Euler(), PizzaBox::Vector3(100.0f, 300.0f, 100.0f));
	}

	return true;
}

void Level1::Destroy(){
	Scene::Destroy();
}