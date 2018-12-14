#include "CharacterController.h"

#include <Core/GameManager.h>
#include <Core/Time.h>
#include <Graphics/MeshRender.h>
#include <Input/InputManager.h>
#include <Object/GameObject.h>
#include <Tools/Debug.h>

using namespace GamePackage;

CharacterController::CharacterController() : pauseToggle(false){
}

void CharacterController::OnStart(){
	Script::OnStart();
	pauseToggle = false;
}

void CharacterController::Update(const float deltaTime_){
	PizzaBox::Vector3 currentPosition = gameObject->GetTransform()->GetPosition();
	float moveX = PizzaBox::InputManager::GetAxis("Horizontal");
	float moveY = PizzaBox::InputManager::GetAxis("Vertical");
	float moveZ = PizzaBox::InputManager::GetAxis("Depth");

	gameObject->GetTransform()->Translate(gameObject->GetTransform()->GetRight() * 15.0f * moveX * PizzaBox::Time::RealDeltaTime());
	gameObject->GetTransform()->Translate(gameObject->GetTransform()->GetUp() * 15.0f * moveY * PizzaBox::Time::RealDeltaTime());
	gameObject->GetTransform()->Translate(gameObject->GetTransform()->GetForward() * -15.0f * moveZ * PizzaBox::Time::RealDeltaTime());

	//----------------------------------------------------------------------------------//

	PizzaBox::Euler currentRotation = gameObject->GetTransform()->GetRotation();
	float rotateX = PizzaBox::InputManager::GetAxis("RotateX");
	float rotateY = PizzaBox::InputManager::GetAxis("RotateY");
	PizzaBox::Euler rotateAxis = PizzaBox::Euler(90.0f * rotateX, 90.0f * rotateY, 0.0f) * PizzaBox::Time::RealDeltaTime();
	gameObject->GetTransform()->Rotate(rotateAxis);

	//Remove any Z axis rotation
	currentRotation = gameObject->GetTransform()->GetRotation();
	currentRotation.z = 0.0f;
	gameObject->SetRotation(currentRotation);

	//----------------------------------------------------------------------------------//

	if(PizzaBox::InputManager::GetButtonDown("ResetPos")){
		gameObject->GetTransform()->SetPosition(PizzaBox::Vector3(0.0f, 0.0f, 0.0f));
	}

	if(PizzaBox::InputManager::GetButtonDown("ResetRot")){
		gameObject->GetTransform()->SetRotation(PizzaBox::Euler(0.0f, 0.0f, 0.0f));
	}

	if(PizzaBox::InputManager::GetButtonDown("ResetScale")){
		gameObject->GetTransform()->SetScale(PizzaBox::Vector3(1.0f, 1.0f, 1.0f));
	}

	if(PizzaBox::InputManager::GetButtonDown("Exit")){
		PizzaBox::GameManager::Stop();
	}

	if(PizzaBox::InputManager::GetButtonDown("PauseToggle")){
		pauseToggle = !pauseToggle;

		if(pauseToggle == true){
			PizzaBox::Time::SetTimeScale(0.0f);
		}else{
			PizzaBox::Time::SetTimeScale(1.0f);
		}
	}
}

void CharacterController::OnDestroy(){
}