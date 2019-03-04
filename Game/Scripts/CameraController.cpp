#include "CameraController.h"

#include <Audio/AudioSource.h>
#include <Core/SceneManager.h>
#include <Core/Time.h>
#include <Input/InputManager.h>
#include <Math/Math.h>
#include <Tools/EngineStats.h>
#include <Tools/Debug.h>
#include <Tools/Random.h>

using namespace GamePackage;

CameraController::CameraController() : camera(nullptr), isShaking(false), shakeStartPos(), shakeDuration(0.0f), shakeFrequency(0.0f), shakeDir(), shakeTargetPos(), shakeTimer(0.0f), shakeTime(0.0f), rotateSpeed(0.0f){
}

void CameraController::OnStart(){
	camera = gameObject->GetComponent<PizzaBox::Camera>();

	auto musicPlayer = gameObject->GetComponent<PizzaBox::AudioSource>();
	if(musicPlayer != nullptr){
		musicPlayer->PlayContinuous();
	}

	shakeTime = 0.05f;
	rotateSpeed = 45.0f;
}

void CameraController::OnDestroy(){
	camera = nullptr;
}

void CameraController::Update(const float deltaTime_){
	if(camera == nullptr){
		PizzaBox::Debug::LogWarning("CameraController does not have Camera reference!", __FILE__, __LINE__);
		return;
	}

	if(PizzaBox::InputManager::GetKeyDown(SDLK_3)){
		BeginShaking(5.0f, 2.5f);
	}

	if(isShaking){
		gameObject->SetPosition(shakeStartPos);
	}

	float moveY = PizzaBox::InputManager::GetAxis("RotateZ");
	float moveZ = PizzaBox::InputManager::GetAxis("RotateY");

	gameObject->GetTransform()->Translate(gameObject->GetTransform()->GetUp() * rotateSpeed * moveY * PizzaBox::Time::RealDeltaTime());
	gameObject->GetTransform()->Translate(gameObject->GetTransform()->GetRight() * -rotateSpeed * moveZ * PizzaBox::Time::RealDeltaTime());

	//v1 is camera facing direction
	PizzaBox::Vector3 cameraForward = camera->GetGameObject()->GetTransform()->GetForward();

	auto target = PizzaBox::SceneManager::CurrentScene()->FindWithTag("Player");
	if(target == nullptr){
		return;
	}

	PizzaBox::Vector3 targetPos = target->GetTransform()->GetPosition();
	//Target's center is it's feet, so we'll adjust our target position based on half it's scale
	//Fudge factor of ~100 because our model is weird
	targetPos.y += (target->GlobalScale().y / 2.0f) * 100.0f;

	////build v2 using v1 and difference between camera position and target
	//PizzaBox::Vector3 targetRotation = targetPos - camera->GetGameObject()->GetTransform()->GetPosition();
	//float angle = PizzaBox::Vector3::Dot(cameraForward, targetRotation);
	////Clamp the value to ensure that we get a numerical result
	//float angle2 = PizzaBox::Math::Acos(PizzaBox::Math::Clamp(-1.0f, 1.0f, angle / (cameraForward.Magnitude() * targetRotation.Magnitude())));
	//if(std::isnan(angle2)){
	//	PizzaBox::Debug::LogWarning("Angle was NaN!", __FILE__, __LINE__);
	//	return;
	//}

	float desiredFollowDistance = 130.0f;
	PizzaBox::Vector3 newPosition = targetPos + (-camera->GetGameObject()->GetTransform()->GetForward() * desiredFollowDistance);
	camera->GetGameObject()->SetPosition(newPosition);
	 
	//Get rid of any roll since that doesn't work so well for cameras
	auto currentRotation = gameObject->GetTransform()->GetRotation();
	currentRotation.z = 0.0f;
	gameObject->SetRotation(currentRotation);
	 
	if(isShaking){
		Shake();
	}
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

	//int choose = PizzaBox::Random::Range(1, 3);
	//switch(choose){
	//	case 1:
	//		result.x = -PizzaBox::Random::Range(-shakeFrequency, shakeFrequency);
	//		break;
	//	case 2:
	//		result.y = -PizzaBox::Random::Range(-shakeFrequency, shakeFrequency);
	//		break;
	//	case 3:
	//		//result.z = -PizzaBox::Random::Range(-freq, freq);
	//		break;
	//}

	return result;
}