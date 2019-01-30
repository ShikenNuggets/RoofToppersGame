#include "Missile.h"

#include <Core/Time.h>
#include <Math/Math.h>

using namespace GGJ;

Missile::Missile(PizzaBox::GameObject* target_) : target(target_), speed(0.0f), lifeSpan(0.0f), elapsedTime(0.0f), targetingDuration(0.0f), targetingStart(0.0f), isTracking(false){
	_ASSERT(target != nullptr);
}

void Missile::OnStart(){
	Script::OnStart();

	lifeSpan = 30.0f;
	speed = 5.0f;
	isTracking = false;
	elapsedTime = 0.0f;
	targetingDuration = lifeSpan * 0.3f; //30% of life span
}

void Missile::Update(const float deltaTime_){
	if(elapsedTime > lifeSpan){
		//Missile DIES - TODO
		return;
	}

	PizzaBox::Vector3 dir;
	if(gameObject->GetPosition().y <= (target->GetScale().y * 2.0f) && isTracking == false){
		dir = PizzaBox::Transform::worldUp;
		targetingStart = elapsedTime;
	}else{
		isTracking = true;
	}

	if(isTracking == true && elapsedTime < targetingStart + targetingDuration){
		//Get direction to target
		dir = (target->GetPosition() - gameObject->GetPosition()).Normalized();
		//Update rotation
		UpdateRotation(dir);
	}else{
		dir = gameObject->GetTransform()->GetForward(); //This depends on how the model is rotated
	}

	PizzaBox::Vector3 velocity = dir * speed;

	//Update the current position (S_final = S_initial + v * time)  
	gameObject->SetPosition(velocity * deltaTime_);

	//Update Elapsed Time (how long its lived)
	elapsedTime += deltaTime_;
}

void Missile::UpdateRotation(const PizzaBox::Vector3 targetDir){
	constexpr float maxRotationPerSecond = 180.0f;

	PizzaBox::Vector3 playerPosition = target->GlobalPosition();
	float arg1 = PizzaBox::Vector3::Dot(playerPosition, targetDir);
	float arg2 = playerPosition.Magnitude() * targetDir.Magnitude();

	auto val = arg1 / arg2;
	float rotationAngle = PizzaBox::Math::Acos(PizzaBox::Math::Clamp(-1.0f, 1.0f, val));
	auto axis = PizzaBox::Vector3::Cross(playerPosition, targetDir);
	auto s = PizzaBox::Math::Sin(rotationAngle / 2.0f);

	axis *= s;
	PizzaBox::Quaternion q = PizzaBox::Quaternion(PizzaBox::Math::Cos(rotationAngle / 2.0f), axis);
	float desiredAngle = q.ToEuler().x;
	float finalAngle = 0.0f;

	if(desiredAngle < 0){
		if(fabs(desiredAngle) > (maxRotationPerSecond * PizzaBox::Time::DeltaTime())){
			finalAngle = -(maxRotationPerSecond * PizzaBox::Time::DeltaTime());
		} else{
			finalAngle = desiredAngle;
		}
	}else{
		if(fabs(desiredAngle) > (maxRotationPerSecond * PizzaBox::Time::DeltaTime())){
			finalAngle = (maxRotationPerSecond * PizzaBox::Time::DeltaTime());
		}else{
			finalAngle = desiredAngle;
		}
	}

	gameObject->GetTransform()->Rotate(PizzaBox::Euler(finalAngle, 0.0f, 0.0f));
}

void Missile::OnDestroy(){
	target = nullptr;
}