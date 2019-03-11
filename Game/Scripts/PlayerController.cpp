#include "PlayerController.h"

#include <Core/SceneManager.h>
#include <Core/Time.h>
#include <Input/InputManager.h>
#include <Math/Math.h>
#include <Object/GameObject.h>
#include <Tools/Random.h>
#include <Physics/Rigidbody.h>
#include <Physics/PhysicsEngine.h>
#include <Tools/Debug.h>
#include <Graphics/Models/MeshRender.h>
#include <Graphics/Materials/ColorMaterial.h>

#include "CameraController.h"

using namespace GamePackage;

PlayerController::PlayerController(PizzaBox::Camera* camera_, PlayerAnimator* animator_, PizzaBox::AudioSource* walk_, PizzaBox::AudioSource* grapple_, PizzaBox::AudioSource* jump_, PizzaBox::AudioSource* land_, PizzaBox::AudioSource* swinging_) : camera(camera_), animator(animator_), walkSFX(walk_),grappleSFX(grapple_),jumpSFX(jump_),landSFX(land_),swingingSFX(swinging_), rigidbody(nullptr), grappleLine(nullptr), currentGrapplePoint(nullptr), isWalking(false), isSwinging(false), isSwitchingToSwinging(false), maxRotationPerSecond(0.0f), MoveY(0.0f), pullSpeed(0.0f), currentGrappleLength(0.0f), maxGrappleLength(80.0f), fallBooster(2.0f), deathTimer(0.0f){
}

PlayerController::~PlayerController(){
}

void PlayerController::OnStart(){
	maxRotationPerSecond = 720.0f;
	MoveY = 0.0f;
	rigidbody = gameObject->GetComponent<PizzaBox::Rigidbody>();

	isSwitchingToSwinging = false;
	pullSpeed = 0.4f;
}

void PlayerController::Update(const float deltaTime_){
	rigidbody->SetMinLinearVelocity(-PizzaBox::Math::Infinity());
	rigidbody->SetMaxLinearVelocity(PizzaBox::Math::Infinity());

	if(PizzaBox::InputManager::GetKeyHeld(SDLK_LCTRL) && PizzaBox::InputManager::GetKeyUp(SDLK_r)){
		PizzaBox::SceneManager::LoadScene(0);
	}

	if(PizzaBox::InputManager::GetButtonDown("Grapple1") || PizzaBox::InputManager::GetButtonDown("Grapple2")){
		isSwinging = !isSwinging;
		if(isSwinging){
			SwitchToSwinging();		
			walkSFX->StopContinuous();
		}else{
			SwitchToGroundMovement();
		}
	}

	if(!isSwinging){
		GroundMovement(deltaTime_);
	}else{
		Swinging(deltaTime_);
	}

	if(gameObject->GlobalPosition().y < -10.0f){
		camera->GetGameObject()->GetComponent<CameraController>()->SetTarget(nullptr);
		deathTimer += PizzaBox::Time::RealDeltaTime();
		if(deathTimer >= 1.0f){
			PizzaBox::SceneManager::ReloadCurrentScene(); //TODO - Have this trigger death UI
		}
	}
}

void PlayerController::OnDestroy(){
}

void PlayerController::OnCollision(const PizzaBox::CollisionInfo& other_){
	if(other_.other->HasTag("Platform")){
		rigidbody->SetLinearVelocityDamping(0.98f);
		rigidbody->SetLinearVelocityLimits(-2.5f, 2.5f);
	}
}

void PlayerController::OnCollisionExit(PizzaBox::GameObject* other_){
	if(other_->HasTag("Platform")){
		rigidbody->SetLinearVelocityDamping(0.0f);
		rigidbody->SetLinearVelocityLimits(-PizzaBox::Math::Infinity(), PizzaBox::Math::Infinity());
	}
}

void PlayerController::GroundMovement(float deltaTime_){
	float moveX = -PizzaBox::InputManager::GetAxis("Horizontal");
	float moveZ = -PizzaBox::InputManager::GetAxis("Depth");

	//Handles smooth rotation
	if(!PizzaBox::Math::NearZero(moveX) || !PizzaBox::Math::NearZero(moveZ)){
		PizzaBox::Vector3 targetDir = PizzaBox::Vector3(moveX, 0.0f, moveZ).Normalized();
		targetDir = camera->GetGameObject()->GlobalRotationQuat().ToMatrix4() * targetDir;
		 
		PizzaBox::Vector3 playerForward = gameObject->GetTransform()->GetForward();
		float arg1 = PizzaBox::Vector3::Dot(playerForward, targetDir);
		float arg2 = playerForward.Magnitude() * targetDir.Magnitude();

		float val = arg1 / arg2;
		float rotationAngle = PizzaBox::Math::Acos(PizzaBox::Math::Clamp(-1.0f, 1.0f, val));
		PizzaBox::Vector3 axis = PizzaBox::Vector3::Cross(playerForward, targetDir);
		float s = PizzaBox::Math::Sin(rotationAngle / 2.0f);

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
	
	float moveValue = 0.0f;
	if(!PizzaBox::Math::NearZero(moveX) && PizzaBox::Math::NearZero(moveZ)){
		moveValue = PizzaBox::Math::Abs(moveX);
	}else if(PizzaBox::Math::NearZero(moveX) && !PizzaBox::Math::NearZero(moveZ)){
		moveValue = PizzaBox::Math::Abs(moveZ);
	}else{
		moveValue = (PizzaBox::Math::Abs(moveX) + PizzaBox::Math::Abs(moveZ)) / 2.0f;
	}
	
	float scaleFactor = gameObject->GlobalScale().x * 10.0f;

	if(isWalking && PizzaBox::Math::NearZero(moveValue)){
		isWalking = false;
		walkSFX->StopContinuous();
	}else if(!isWalking && !PizzaBox::Math::NearZero(moveValue)){
		isWalking = true;
		walkSFX->PlayContinuous();
	}

	PizzaBox::Vector3 impulse = -gameObject->GetTransform()->GetForward() * moveValue;

	if(IsOnGround()){
		rigidbody->Impulse(impulse * 7500.0f * 80.0f * 2.5f * deltaTime_ / 5.0f);
	}else{
		rigidbody->Impulse(impulse * 7500.0f * 80.0f * deltaTime_ / 5.0f);
	}

	if(PizzaBox::InputManager::GetButtonDown("JumpButton") && IsOnGround()){
		PizzaBox::Vector3 jumpImpulse = gameObject->GetTransform()->GetUp() * 10000.0f * 80.0f;
		rigidbody->Impulse(jumpImpulse * deltaTime_ * 60.0f / 1.5f);
		jumpSFX->PlayOnce();
	}

	if(!IsOnGround()){
		if(!PizzaBox::InputManager::GetButtonHeld("JumpButton") || rigidbody->GetLinearVelocity().y < 0){
			rigidbody->SetLinearVelocity(rigidbody->GetLinearVelocity() + (gameObject->GetTransform()->GetUp() * -fallBooster * deltaTime_ * 60.0f / 5.0f));
		}
		if (animator != nullptr && !animator->IsTransitioning()) {
			animator->isJumping = true;
		}
	}

	if(animator != nullptr){
		animator->moveValue = moveValue;
	}
}

void PlayerController::Swinging(float deltaTime_){
	rigidbody->SetLinearVelocityDamping(0.0f);
	rigidbody->SetLinearVelocityLimits(-PizzaBox::Math::Infinity(), PizzaBox::Math::Infinity());
	
	if(currentGrapplePoint == nullptr){
		return;
	}

	PizzaBox::GameObject* grapplePoint = currentGrapplePoint->GetGameObject();

	float forwardRotate = PizzaBox::InputManager::GetAxis("Depth");
	float sideRotate = PizzaBox::InputManager::GetAxis("Horizontal");

	rigidbody->Impulse(-forwardRotate * camera->GetGameObject()->GetTransform()->GetForward() * 10.0f * rigidbody->GetMass() * 120.0f * deltaTime_ / 5.0f);
	rigidbody->Impulse(sideRotate * camera->GetGameObject()->GetTransform()->GetRight() * 10.0f * rigidbody->GetMass() * 120.0f * deltaTime_ / 5.0f);

	// Start the physics stuff
	//Where are we after the update
	PizzaBox::Vector3 nextPosition = gameObject->GlobalPosition() + (rigidbody->GetLinearVelocity() * deltaTime_);
	//Is that new position outside the swing limits
	if((nextPosition - grapplePoint->GlobalPosition()).Magnitude() > currentGrappleLength){
		//Pull back in if it is
		nextPosition = grapplePoint->GlobalPosition() + ((nextPosition - grapplePoint->GlobalPosition()).Normalized() * currentGrappleLength);
	}else if((nextPosition - grapplePoint->GlobalPosition()).Magnitude() < grapplePoint->GetComponent<GrapplePoint>()->swingDistance * 0.99f){
		nextPosition = grapplePoint->GlobalPosition() + ((nextPosition - grapplePoint->GlobalPosition()).Normalized() * (grapplePoint->GetComponent<GrapplePoint>()->swingDistance * 0.99f));
	}

	//Prevent player from dragging on ground. Physics doesnt like this
	PizzaBox::Vector3 raycastNextPos = gameObject->GlobalPosition() + (nextPosition - gameObject->GlobalPosition()) * 2.0f;
	std::vector<PizzaBox::RaycastInfo> info = PizzaBox::PhysicsEngine::Raycast(gameObject->GlobalPosition() + gameObject->GetTransform()->GetUp(), raycastNextPos);
	
	PizzaBox::RaycastInfo closest = PizzaBox::RaycastInfo(PizzaBox::Vector3(), PizzaBox::Vector3(), PizzaBox::Math::Infinity(), nullptr);
	for(const PizzaBox::RaycastInfo& i : info){
		if(i.hitFraction < closest.hitFraction && !i.other->HasTag("Player")){
			closest = i;
		}
	}

	if(closest.other != nullptr){
		nextPosition += closest.normal * 0.3f;
	}

	rigidbody->SetLinearVelocity((nextPosition - gameObject->GlobalPosition()) / deltaTime_);

	//Change rope parameters
	PizzaBox::Vector3 testLine = gameObject->GlobalPosition() + ((grapplePoint->GlobalPosition() - gameObject->GlobalPosition()) / 2.0f) + (gameObject->GetTransform()->GetUp() * 0.0f);
	grappleLine->SetGlobalPosition(testLine);
	//grappleLine->SetGlobalPosition(gameObject->GlobalPosition() + (grapplePoint->GlobalPosition() - gameObject->GlobalPosition()));
	grappleLine->SetGlobalRotation(gameObject->GlobalRotation());
	grappleLine->SetGlobalScale(0.25f, (((gameObject->GlobalPosition() - grapplePoint->GlobalPosition()).Magnitude()) - 10.0f), 0.25f);
	//grappleLine->SetGlobalScale(1.0f, PizzaBox::Vector3::Distance(gameObject->GlobalPosition(), grapplePoint->GlobalPosition()), 1.0f);

	if(isSwitchingToSwinging){
		if(currentGrappleLength <= grapplePoint->GetComponent<GrapplePoint>()->swingDistance){
			currentGrappleLength = grapplePoint->GetComponent<GrapplePoint>()->swingDistance;
			isSwitchingToSwinging = false;
		}else{
			pullSpeed = ((gameObject->GetPosition() - grapplePoint->GetPosition()).Magnitude() - grapplePoint->GetComponent<GrapplePoint>()->swingDistance) / 100.0f;
			currentGrappleLength = (gameObject->GetPosition() - grapplePoint->GetPosition()).Magnitude() - pullSpeed;
		}
	}

	gameObject->SetPosition(nextPosition);

	gameObject->SetRotation(PizzaBox::Quaternion::LookAt(gameObject->GlobalPosition(), grapplePoint->GlobalPosition()));
	gameObject->Rotate(-90.0f, 0.0f, -180.0f);
}

void PlayerController::SwitchToSwinging(){

	rigidbody->SetLinearVelocityDamping(0.0f);
	rigidbody->SetLinearVelocityLimits(-PizzaBox::Math::Infinity(), PizzaBox::Math::Infinity());

	currentGrapplePoint = FindNearestGrapple();
	if(currentGrapplePoint == nullptr){
		isSwinging = false;
		return;
	}

	PizzaBox::GameObject* grapplePoint = currentGrapplePoint->GetGameObject();

	//Make rope
	grappleLine = PizzaBox::SceneManager::CurrentScene()->CreateObject<PizzaBox::GameObject>();
	grappleLine->AddComponent(new PizzaBox::MeshRender("CubeModel", new PizzaBox::ColorMaterial(PizzaBox::Color::Brown)));

	currentGrappleLength = (gameObject->GetPosition() - grapplePoint->GetPosition()).Magnitude();
	grappleSFX->PlayOnce();
	swingingSFX->PlayContinuous();
	isSwitchingToSwinging = true;
}

void PlayerController::SwitchToGroundMovement(){
	swingingSFX->StopContinuous();
	gameObject->SetRotation(0.0f, 180.0f, 0.0f);

	PizzaBox::SceneManager::CurrentScene()->DestroyObject(grappleLine);

	if(!IsOnGround()){
		rigidbody->SetLinearVelocityDamping(0.0f);
		rigidbody->SetLinearVelocityLimits(-PizzaBox::Math::Infinity(), PizzaBox::Math::Infinity());
	}else{
		rigidbody->SetLinearVelocityDamping(0.98f);
		rigidbody->SetLinearVelocityLimits(-2.5f, 2.5f);
	}
}

GrapplePoint* PlayerController::FindNearestGrapple(){
	std::vector<GrapplePoint*> grapplePoints = PizzaBox::SceneManager::CurrentScene()->GetComponentsInScene<GrapplePoint>();
	GrapplePoint* grappleTarget = nullptr;
	float mostForward = 0.0f;
	for(const auto& point : grapplePoints){
		if((point->GetGameObject()->GlobalPosition() - gameObject->GlobalPosition()).Magnitude() > maxGrappleLength){
			continue;
		}

		std::vector<PizzaBox::RaycastInfo> info = PizzaBox::PhysicsEngine::Raycast(gameObject->GlobalPosition(), point->GetGameObject()->GlobalPosition());
		bool isValid = true;
		for(const auto& in : info){
			if(!in.other->HasTag("Player")){
				isValid = false;
				break;
			}
		}

		if(!isValid){
			continue;
		}

		if(grappleTarget != nullptr){
			if(PizzaBox::Vector3::Dot(point->GetGameObject()->GlobalPosition(), gameObject->GetTransform()->GetForward()) > mostForward){
				grappleTarget = point;
				mostForward = PizzaBox::Vector3::Dot(point->GetGameObject()->GlobalPosition(), gameObject->GetTransform()->GetForward());
			}
		}else{
			grappleTarget = point;
			mostForward = PizzaBox::Vector3::Dot(point->GetGameObject()->GlobalPosition(), gameObject->GetTransform()->GetForward());
		}
	}

	return grappleTarget;
}

bool PlayerController::IsOnGround(){
	std::vector<PizzaBox::RaycastInfo> info = PizzaBox::PhysicsEngine::Raycast(gameObject->GlobalPosition() + PizzaBox::Vector3(0.0f, 1.0f, 0.0f), gameObject->GlobalPosition() + PizzaBox::Vector3(0.0f, -2.0f, 0.0f));
	for(const auto& in : info){
		if(in.other->HasTag("Platform")){
			return true;
		}
	}

	return false;
}