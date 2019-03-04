#include "PlayerController.h"

#include <Core/SceneManager.h>
#include <Core/Time.h>
#include <Input/InputManager.h>
#include <Math/Math.h>
#include <Object/GameObject.h>
#include <Tools/Random.h>
#include <Physics/Rigidbody.h>
#include <Tools/Debug.h>

#include "GrapplePoint.h"

using namespace GamePackage;

PlayerController::PlayerController(PizzaBox::Camera* camera_, PlayerAnimator* animator_) : camera(camera_), animator(animator_), rigidbody(nullptr), isWalking(false), isGrounded(false), maxRotationPerSecond(0.0f), MoveY(0.0f) {
}

PlayerController::~PlayerController(){
}

void PlayerController::OnStart(){
	maxRotationPerSecond = 180.0f;
	MoveY = 0.0f;
	rigidbody = gameObject->GetComponent<PizzaBox::Rigidbody>();
}

void PlayerController::Update(const float deltaTime_){
	rigidbody->SetMinLinearVelocity(-PizzaBox::Math::Infinity());
	rigidbody->SetMaxLinearVelocity(PizzaBox::Math::Infinity());

	float moveSpeed = 20.0f;
	float rotateSpeed = 360.0f;

	if(PizzaBox::InputManager::GetKeyHeld(SDLK_LCTRL) && PizzaBox::InputManager::GetKeyHeld(SDLK_r)){
		PizzaBox::SceneManager::LoadScene(0);
	}

	/*
	if(animator != nullptr && animator->isJumping){ 
		//gameObject->GetTransform()->Translate(gameObject->GetTransform()->GetUp() * MoveY * moveSpeed * deltaTime_);
		return;
	}
	*/

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

	PizzaBox::Debug::Log(rigidbody->GetLinearVelocity().ToString());

	//gameObject->GetTransform()->Translate(gameObject->GetTransform()->GetForward() * -fabs(moveValue) * moveSpeed * scaleFactor * deltaTime_);
	PizzaBox::Vector3 impulse = -gameObject->GetTransform()->GetForward() * moveValue;

	if(isGrounded){
		rigidbody->Impulse(impulse * 7500.0f * 80.0f * 2.5f * deltaTime_);
	}else{
		rigidbody->Impulse(impulse * 7500.0f * 80.0f * deltaTime_);
	}

	if(PizzaBox::InputManager::GetButtonDown("JumpButton") && animator != nullptr && !animator->IsTransitioning()){
		animator->isJumping = true; 
		//MoveY = 0.8f;
		PizzaBox::Vector3 jumpImpulse = gameObject->GetTransform()->GetUp() * 10000.0f * 80.0f;
		rigidbody->Impulse(jumpImpulse);
	}
	 
	if(animator != nullptr){
		animator->moveValue = moveValue;
	}
}

void PlayerController::OnDestroy(){
}

void PlayerController::OnCollision(PizzaBox::GameObject* other_){
	if(other_->HasTag("Platform")){
		isGrounded = true;
		rigidbody->SetLinearVelocityDamping(0.98f);
		rigidbody->SetLinearVelocityLimits(-2.5f, 2.5f);
	}
}

void PlayerController::OnCollisionExit(PizzaBox::GameObject* other_){
	if(other_->HasTag("Platform")){
		isGrounded = false;
		rigidbody->SetLinearVelocityDamping(0.0f);
		rigidbody->SetLinearVelocityLimits(-PizzaBox::Math::Infinity(), PizzaBox::Math::Infinity());
	}
}

void PlayerController::Swinging(float deltaTime_){
	PizzaBox::GameObject* grapplePoint;

	float forwardRotate = PizzaBox::InputManager::GetAxis("Depth");
	float sideRotate = PizzaBox::InputManager::GetAxis("Horizontal");

	rigidbody->Impulse(-forwardRotate * camera->GetGameObject()->GetTransform()->GetForward() * 10.0f);
	rigidbody->Impulse(sideRotate * camera->GetGameObject()->GetTransform()->GetRight() * 10.0f);

	// Start the physics stuff
	//Where are we after the update
	PizzaBox::Vector3 nextPosition = gameObject->GlobalPosition() + (rigidbody->GetLinearVelocity() * deltaTime_);
	//Is that new position outside the swing limits
	if((nextPosition - grapplePoint->GlobalPosition()).Magnitude() > grapplePoint->GetComponent<GrapplePoint>()->swingDistance){
		//Pull back in if it is
		nextPosition = grapplePoint->GlobalPosition() + ((nextPosition - grapplePoint->GlobalPosition()).Normalized() * grapplePoint->GetComponent<GrapplePoint>()->swingDistance);

	}
	rigidbody->SetLinearVelocity((nextPosition - gameObject->GlobalPosition()) / deltaTime_);
	gameObject->SetPosition(nextPosition);

	gameObject->SetRotation(PizzaBox::Quaternion::LookAt(gameObject->GlobalPosition(), grapplePoint->GlobalPosition()));
	gameObject->Rotate(90.0f, 0.0f, 0.0f);
}