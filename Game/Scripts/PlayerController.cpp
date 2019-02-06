#include "PlayerController.h"

#include <Core/SceneManager.h>
#include <Core/Time.h>
#include <Input/InputManager.h>
#include <Math/Math.h>
#include <Object/GameObject.h>
#include <Tools/Random.h>

using namespace GamePackage;

PlayerController::PlayerController(PizzaBox::Camera* camera_, PlayerAnimator* animator_) : camera(camera_), animator(animator_), isWalking(false), maxRotationPerSecond(0.0f) {
}

PlayerController::~PlayerController(){
}

void PlayerController::OnStart(){
	maxRotationPerSecond = 180.0f;
}

void PlayerController::Update(const float deltaTime_){
	float moveSpeed = 15.0f;
	float rotateSpeed = 90.0f;

	if(PizzaBox::InputManager::GetKeyHeld(SDLK_LCTRL) && PizzaBox::InputManager::GetKeyHeld(SDLK_r)){
		PizzaBox::SceneManager::LoadScene(0);
	}
	 
	if(animator != nullptr && animator->isJumping){
		return;
	}

	if(animator != nullptr && animator->isPunching){
		return;
	}

	float moveX = -PizzaBox::InputManager::GetAxis("Horizontal");
	float moveZ = -PizzaBox::InputManager::GetAxis("Depth");

	// Handles smooth rotation
	if(!PizzaBox::Math::NearZero(moveX) || !PizzaBox::Math::NearZero(moveZ)){
		PizzaBox::Vector3 targetDir = PizzaBox::Vector3(moveX, 0.0f, moveZ).Normalized();
		targetDir = camera->GetGameObject()->GlobalRotation().ToMatrix4() * targetDir;
		 
		auto playerForward = gameObject->GetTransform()->GetForward();
		float arg1 = PizzaBox::Vector3::Dot(playerForward, targetDir);
		float arg2 = playerForward.Magnitude() * targetDir.Magnitude();

		auto val = arg1 / arg2;
		float rotationAngle = PizzaBox::Math::Acos(PizzaBox::Math::Clamp(-1.0f, 1.0f, val));
		auto axis = PizzaBox::Vector3::Cross(playerForward, targetDir);
		auto s = PizzaBox::Math::Sin(rotationAngle / 2.0f);

		axis *= s;
		PizzaBox::Quaternion q = PizzaBox::Quaternion(PizzaBox::Math::Cos(rotationAngle / 2.0f), axis);
		float desiredAngle = q.ToEuler().y;
		float finalAngle = 0.0f;

		if(desiredAngle < 0){
			if(fabs(desiredAngle) > (maxRotationPerSecond * deltaTime_)){
				finalAngle = -(maxRotationPerSecond * deltaTime_);
			}else{
				finalAngle = desiredAngle;
			}
		}else{
			if(fabs(desiredAngle) > (maxRotationPerSecond * deltaTime_)){
				finalAngle = (maxRotationPerSecond * deltaTime_);
			}else{
				finalAngle = desiredAngle;
			}
		}

		gameObject->GetTransform()->Rotate(PizzaBox::Euler(0.0f, finalAngle, 0.0f));
	}
	  
	float moveValue = (fabs(moveX) + fabs(moveZ)) / 2.0f;
	float scaleFactor = gameObject->GlobalScale().x * 10.0f;

	if(isWalking && PizzaBox::Math::NearZero(moveValue)){
		isWalking = false;
		//walk->StopContinuous();				// audio
	}else if(!isWalking && !PizzaBox::Math::NearZero(moveValue)){
		isWalking = true;
		//walk->PlayContinuous();				// audio
	}

	gameObject->GetTransform()->Translate(gameObject->GetTransform()->GetForward() * -fabs(moveValue) * moveSpeed * scaleFactor * deltaTime_);
	 
	if(PizzaBox::InputManager::GetButtonDown("JumpButton") && animator != nullptr && !animator->IsTransitioning()){
		animator->isJumping = true;
	}
	 
	if(animator != nullptr){
		animator->moveValue = moveValue;
	}
}

void PlayerController::OnDestroy(){
}

void PlayerController::OnCollision(const PizzaBox::GameObject* const other_){

}