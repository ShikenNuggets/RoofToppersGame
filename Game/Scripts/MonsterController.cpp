#include "MonsterController.h"

#include <Core/SceneManager.h>
#include <Core/Time.h>
#include <Input/InputManager.h>
#include <Math/Math.h>
#include <Object/GameObject.h>
#include <Tools/Random.h>

using namespace GGJ;

MonsterController::MonsterController(PizzaBox::Camera* camera_, MonsterAnimator* animator_, PizzaBox::Collider* collider_, PizzaBox::AudioSource* punch1_, PizzaBox::AudioSource* punch2_, PizzaBox::AudioSource* walk_) : camera(camera_), animator(animator_), punchCollider(collider_), punch1(punch1_), punch2(punch2_), walk(walk_), isWalking(false), isPunching(false), maxRotationPerSecond(0.0f), isGrowing(false), isShrinking(false), growSpeed(0.1f), shrinkSpeed(0.05f), oldScale(0.0f), sizeTimer(0.0f){
}

MonsterController::~MonsterController(){
}

void MonsterController::OnStart(){
	maxRotationPerSecond = 180.0f;
}

void MonsterController::Update(const float deltaTime_){
	float moveSpeed = 15.0f;
	float rotateSpeed = 90.0f;

	if(PizzaBox::InputManager::GetKeyHeld(SDLK_LCTRL) && PizzaBox::InputManager::GetKeyHeld(SDLK_r)){
		PizzaBox::SceneManager::LoadScene(0);
	}

	if(PizzaBox::InputManager::GetKeyDown(SDLK_1)){
		BeginShrink();
	}else if(PizzaBox::InputManager::GetKeyDown(SDLK_2)){
		BeginGrow();
	}

	if(isShrinking){
		Shrink();
	}else if(isGrowing){
		Grow();
	}

	if(!isPunching && animator != nullptr && animator->isPunching){
		isPunching = true;

		int rand = PizzaBox::Random::Range(0, 2); //Will either be 0 or 1
		if(rand == 0){
			punch2->PlayOnce();
		}else{
			punch1->PlayOnce();
		}
		
		punchCollider->SetEnable(true);
		return;
	}else if(animator == nullptr || !animator->isPunching){
		isPunching = false;
		punch1->StopOnce();
		punch2->StopOnce();
		punchCollider->SetEnable(false);
	}

	if(animator != nullptr && animator->isJumping){
		return;
	}

	if(animator != nullptr && animator->isPunching){
		return;
	}

	float moveX = -PizzaBox::InputManager::GetAxis("Horizontal");
	float moveZ = -PizzaBox::InputManager::GetAxis("Depth");

	if(!PizzaBox::Math::NearZero(moveX) || !PizzaBox::Math::NearZero(moveZ)){
		PizzaBox::Vector3 targetDir = PizzaBox::Vector3(moveX, 0.0f, moveZ).Normalized();
		targetDir = camera->GetGameObject()->GlobalRotation().ToMatrix4() * targetDir;

		//if(PizzaBox::Math::NearZero(moveX)){
		//	PizzaBox::Debug::Log("Happens");
		//	targetDir = camera->GetGameObject()->GetTransform()->GetForward();
		//	if(moveZ < 0){
		//		targetDir = -targetDir;
		//	}
		//}else if(PizzaBox::Math::NearZero(moveZ)){
		//	PizzaBox::Debug::Log("Also Happens");
		//	targetDir = camera->GetGameObject()->GetTransform()->GetRight();
		//	if(moveX < 0){
		//		targetDir = -targetDir;
		//	}
		//}

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

	//float rotateY = -PizzaBox::InputManager::GetAxis("RotateY");

	//gameObject->GetTransform()->Translate(gameObject->GetTransform()->GetRight() * moveX * moveSpeed * deltaTime_);
	float moveValue = (fabs(moveX) + fabs(moveZ)) / 2.0f;
	float scaleFactor = gameObject->GlobalScale().x * 10.0f;

	if(isWalking && PizzaBox::Math::NearZero(moveValue)){
		isWalking = false;
		walk->StopContinuous();
	}else if(!isWalking && !PizzaBox::Math::NearZero(moveValue)){
		isWalking = true;
		walk->PlayContinuous();
	}

	gameObject->GetTransform()->Translate(gameObject->GetTransform()->GetForward() * -fabs(moveValue) * moveSpeed * scaleFactor * deltaTime_);

	//gameObject->GetTransform()->Rotate(PizzaBox::Euler(0.0f, rotateY, 0.0f) * rotateSpeed * deltaTime_);

	if(PizzaBox::InputManager::GetButtonDown("JumpButton") && animator != nullptr && !animator->IsTransitioning() && !animator->isPunching){
		animator->isJumping = true;
	}

	if(PizzaBox::InputManager::GetButtonDown("PunchButton") && animator != nullptr && !animator->IsTransitioning() && !animator->isJumping){
		animator->isPunching = true;
	}

	if(animator != nullptr){
		animator->moveValue = moveValue;
	}
}

void MonsterController::OnDestroy(){
}

void MonsterController::OnCollision(const PizzaBox::GameObject* const other_){
	if(other_->HasTag("EnemyProjectile") && !isShrinking){
		isShrinking = true;
		isGrowing = false;
		oldScale = gameObject->GlobalScale().x;
		sizeTimer = 0.0f;
	}
}

void MonsterController::BeginGrow(){
	isGrowing = true;
	isShrinking = false;
	oldScale = gameObject->GlobalScale().x;
	sizeTimer = 0.0f;
}

void MonsterController::BeginShrink(){
	isShrinking = true;
	isGrowing = false;
	oldScale = gameObject->GlobalScale().x;
	sizeTimer = 0.0f;
}

void MonsterController::Grow(){
	PizzaBox::Vector3 currentScale = gameObject->GetTransform()->GetScale();
	PizzaBox::Vector3 grow = PizzaBox::Vector3(growSpeed * oldScale, growSpeed * oldScale, growSpeed * oldScale) * PizzaBox::Time::DeltaTime();
	PizzaBox::Vector3 newScale = currentScale + grow;

	gameObject->GetTransform()->SetScale(newScale);

	sizeTimer += PizzaBox::Time::DeltaTime();
	if(sizeTimer >= 1.0f){
		isGrowing = false;
	}
}

void MonsterController::Shrink(){
	PizzaBox::Vector3 currentScale = gameObject->GetTransform()->GetScale();
	PizzaBox::Vector3 shrink = PizzaBox::Vector3(shrinkSpeed * oldScale, shrinkSpeed * oldScale, shrinkSpeed * oldScale) * PizzaBox::Time::DeltaTime();
	PizzaBox::Vector3 newScale = currentScale - shrink;

	gameObject->GetTransform()->SetScale(newScale);

	sizeTimer += PizzaBox::Time::DeltaTime();
	if(sizeTimer >= 1.0f){
		isShrinking = false;
	}
}