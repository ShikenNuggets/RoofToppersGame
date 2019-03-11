#include "MovingPlatform.h"

#include <Object/GameObject.h> 

using namespace GamePackage;

MovingPlatform::MovingPlatform() : direction(PizzaBox::Vector3(1, 0, 0)), directionSpeed(1.0f), distance(1.0f) {

}

void MovingPlatform::OnStart() {
	origin = gameObject->GetTransform()->GetPosition().x;
	useSpeed = -directionSpeed;
}

void MovingPlatform::Update(const float deltaTime_) {
	if (direction.x > 0) {
		if (origin - gameObject->GetTransform()->GetPosition().x > distance) {
			//flip direction
			useSpeed = directionSpeed;
		}
		else if (origin - gameObject->GetTransform()->GetPosition().x < -distance) {
			//flip direction
			useSpeed = -directionSpeed;
		}
		gameObject->GetTransform()->Translate(PizzaBox::Vector3(useSpeed * deltaTime_, 0, 0));
	}
	else if (direction.y > 0) {
		if (origin - gameObject->GetTransform()->GetPosition().y > distance) {
			//flip direction
			useSpeed = directionSpeed;
		}
		else if (origin - gameObject->GetTransform()->GetPosition().y < -distance) {
			//flip direction
			useSpeed = -directionSpeed;
		}
		gameObject->GetTransform()->Translate(PizzaBox::Vector3(0, useSpeed * deltaTime_, 0));
	}
	else if (direction.z > 0) {
		if (origin - gameObject->GetTransform()->GetPosition().z > distance) {
			//flip direction
			useSpeed = directionSpeed;
		}
		else if (origin - gameObject->GetTransform()->GetPosition().z < -distance) {
			//flip direction
			useSpeed = -directionSpeed;
		}
		gameObject->GetTransform()->Translate(PizzaBox::Vector3(0, 0, useSpeed * deltaTime_));
	}
}

void MovingPlatform::OnDestroy() {

}

void MovingPlatform::SetDirection(PizzaBox::Vector3 dir) {
	direction = dir;
}

void MovingPlatform::SetDirectionSpeed(float speed_) {
	directionSpeed = speed_;
}

void MovingPlatform::SetDistance(float dis) {
	distance = dis;
}

void MovingPlatform::OnCollision(const PizzaBox::CollisionInfo&){

}