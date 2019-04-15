#include "CameraController.h"

#include <Audio/AudioSource.h>
#include <Core/Config.h>
#include <Core/SceneManager.h>
#include <Core/Time.h>
#include <Input/InputManager.h>
#include <Math/Math.h>
#include <Tools/EngineStats.h>
#include <Tools/Debug.h>
#include <Tools/Random.h>
#include <Graphics/RenderEngine.h>

using namespace GamePackage;

CameraController::CameraController(PizzaBox::GameObject* target_) : camera(nullptr), isShaking(false), shakeStartPos(), shakeDuration(0.0f), shakeFrequency(0.0f), shakeDir(), shakeTargetPos(), shakeTimer(0.0f), shakeTime(0.0f), rotateSpeed(0.0f), gamepadSensitivity(2.5f), hasControl(true), minRotation(-60.0f), maxRotation(12.5f){
	target = target_;
}

void CameraController::OnStart(){
	camera = gameObject->GetComponent<PizzaBox::Camera>();

	auto musicPlayer = gameObject->GetComponent<PizzaBox::AudioSource>();
	if(musicPlayer != nullptr){
		musicPlayer->PlayContinuous();
	}

	shakeTime = 0.05f;
	rotateSpeed = 45.0f;

	gamepadSensitivity = 2.5f;
}

void CameraController::OnDestroy(){
	camera = nullptr;
}

void CameraController::Update(const float deltaTime_){
	if(camera == nullptr){
		PizzaBox::Debug::LogWarning("CameraController does not have Camera reference!", __FILE__, __LINE__);
		return;
	}

	if(!hasControl){
		return;
	}

	if(PizzaBox::InputManager::GetKeyDown(SDLK_3)){
		BeginShaking(5.0f, 2.5f);
	}

	if(isShaking){
		gameObject->SetPosition(shakeStartPos);
	}

	float mouseSensitivity = static_cast<float>(PizzaBox::Config::GetInt("MouseSensitivity"));

	//Camera rotation
	float rotX = -PizzaBox::InputManager::GetAxis("MouseX") * mouseSensitivity * 75.0f;
	float rotY = -PizzaBox::InputManager::GetAxis("MouseY") * mouseSensitivity * 30.0f;

	if(PizzaBox::Math::NearZero(rotX) && PizzaBox::Math::NearZero(rotY)){
		rotX = -PizzaBox::InputManager::GetAxis("RightStickX") * gamepadSensitivity * 75.0f;
		rotY = -PizzaBox::InputManager::GetAxis("RightStickY") * gamepadSensitivity * 30.0f;
	}
	
	gameObject->GetTransform()->Rotate(rotY * PizzaBox::Time::RealDeltaTime(), rotX * PizzaBox::Time::RealDeltaTime(), 0.0f);

	float x = gameObject->GetRotation().x;
	x = PizzaBox::Math::Clamp(minRotation, maxRotation, x);
	gameObject->SetRotation(PizzaBox::Euler(x, gameObject->GetRotation().y, gameObject->GetRotation().z));

	//v1 is camera facing direction
	PizzaBox::Vector3 cameraForward = camera->GetGameObject()->GetTransform()->GetForward();
	 
	//Get rid of any roll since that doesn't work so well for cameras
	PizzaBox::Euler currentRotation = gameObject->GetTransform()->GetRotation();
	currentRotation.z = 0.0f;
	gameObject->SetRotation(currentRotation);
	 
	if(isShaking){
		Shake();
	}

	// If there is no target, do not skip this stuff
	if(target == nullptr){
		return;
	}

	//Quick reference to target's global position
	PizzaBox::Vector3 targetPos = target->GetTransform()->GlobalPosition();

	//Target's center is it's feet, so we'll adjust our target position based on half it's scale
	//Multiplied by a fudge factor because our model is weird
	targetPos.y += (target->GlobalScale().y / 2.0f) * 750.0f;

	//Sets camera position based on camera rotation and target position
	float desiredFollowDistance = 10.0f;
	PizzaBox::Vector3 newPosition = targetPos + (-camera->GetGameObject()->GetTransform()->GetForward() * desiredFollowDistance);
	camera->GetGameObject()->SetPosition(newPosition);

}

void CameraController::BeginShaking(float duration_, float frequency_){
	shakeStartPos = gameObject->GetPosition();
	shakeDuration = duration_;
	shakeFrequency = frequency_ * PizzaBox::EngineStats::GetFloat("Average FPS");
	shakeDir = NewRandomDirection();
	shakeTargetPos = shakeStartPos + shakeDir * PizzaBox::Time::DeltaTime();
	isShaking = true;
}

void CameraController::Shake(){
	//Reset the start position for this frame
	shakeStartPos = gameObject->GetPosition();

	if(shakeDuration > 0.0f){
		shakeDir = NewRandomDirection();
		PizzaBox::Vector3 newPosition = gameObject->GetPosition() + shakeDir * PizzaBox::Time::DeltaTime();

		shakeTimer += PizzaBox::Time::DeltaTime();
		if(shakeTimer >= shakeTime){
			shakeDir = NewRandomDirection();
			shakeTargetPos = shakeStartPos + shakeDir * PizzaBox::Time::DeltaTime();
			shakeTimer -= shakeTime;
		}else{
			auto finalPos = PizzaBox::Vector3::Lerp(shakeStartPos, shakeTargetPos, shakeTimer / shakeTime);
			gameObject->SetPosition(finalPos);
		}

		shakeDuration -= PizzaBox::Time::DeltaTime();
	}else{
		gameObject->SetPosition(shakeStartPos);
		isShaking = false;
	}
}

PizzaBox::Vector3 CameraController::NewRandomDirection() const{
	PizzaBox::Vector3 result = PizzaBox::Vector3::Zero();
	result.x = -PizzaBox::Random::Range(-shakeFrequency, shakeFrequency);
	result.y = -PizzaBox::Random::Range(-shakeFrequency, shakeFrequency);

	return result;
}

PizzaBox::GameObject* CameraController::GetTarget(){
	return target;
}

void CameraController::SetTarget(PizzaBox::GameObject* target_){
	target = target_;
}