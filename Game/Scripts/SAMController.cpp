#include "SAMController.h"

#include <Core/SceneManager.h>
#include <Math/Math.h>

#include "Missile.h"

using namespace GGJ;

SAMController::SAMController(PizzaBox::GameObject* target_) : target(target_), currentState(State::Idle), delay(0.0f), timeSinceLastFire(0.0f), elapsedTime(0.0f), targetDistance(0.0f), rotateSpeed(0.0f), maxRotationPerSecond(0.0f){
}

void SAMController::OnStart(){
	if(target == nullptr){
		target = PizzaBox::SceneManager::CurrentScene()->FindWithTag("Player");
	}

	currentState = State::Idle;
	delay = 5.0f;
	targetDistance = 50.0f;
	rotateSpeed = 5.0f;
	maxRotationPerSecond = 180.0f;

	Script::OnStart();
}

void SAMController::Update(const float deltaTime_){
	PizzaBox::Vector3 ray;
	PizzaBox::Vector3 playerForward;
	PizzaBox::Vector3 dir;
	PizzaBox::GameObject* missile;

	switch(currentState){
		case State::Idle:
			gameObject->GetTransform()->Rotate(PizzaBox::Euler(0.0f, 1.0f, 0.0f) * rotateSpeed * deltaTime_);
			ray = target->GlobalPosition() - gameObject->GlobalPosition();
			if(ray.Magnitude() <= targetDistance){
				currentState = State::Targeting;
			}
			break;

		case State::Targeting:
			playerForward = target->GetTransform()->GetForward();
			dir = playerForward - gameObject->GlobalPosition();
			RotateTurret(dir, deltaTime_);

			if(PizzaBox::Vector3::Dot(playerForward, gameObject->GetTransform()->GetForward()) >= 0.0f){
				currentState = State::Firing;
			}
			break;

		case State::Firing:
			if(elapsedTime >= timeSinceLastFire + delay){
				missile = PizzaBox::SceneManager::CurrentScene()->CreateObject<PizzaBox::GameObject>(gameObject->GlobalPosition());
				missile->AddComponent(new Missile(target));
				timeSinceLastFire = elapsedTime;
			}
			break;

		default:
			break;
	}

	elapsedTime += deltaTime_;
}

void SAMController::OnDestroy(){
	target = nullptr;
}

void SAMController::RotateTurret(const PizzaBox::Vector3& targetDir_, float deltaTime_){
	PizzaBox::Vector3 playerPosition = target->GlobalPosition();
	float arg1 = PizzaBox::Vector3::Dot(playerPosition, targetDir_);
	float arg2 = playerPosition.Magnitude() * targetDir_.Magnitude();

	auto val = arg1 / arg2;
	float rotationAngle = PizzaBox::Math::Acos(PizzaBox::Math::Clamp(-1.0f, 1.0f, val));
	auto axis = PizzaBox::Vector3::Cross(playerPosition, targetDir_);
	auto s = PizzaBox::Math::Sin(rotationAngle / 2.0f);

	axis *= s;
	PizzaBox::Quaternion q = PizzaBox::Quaternion(PizzaBox::Math::Cos(rotationAngle / 2.0f), axis);
	float desiredAngle = q.ToEuler().x;
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

	gameObject->GetTransform()->Rotate(PizzaBox::Euler(finalAngle, 0.0f, 0.0f));
}