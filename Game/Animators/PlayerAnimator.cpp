#include "PlayerAnimator.h"

using namespace GamePackage;

PlayerAnimator::PlayerAnimator() : moveValue(0.0f), isJumping(false){
}

PlayerAnimator::~PlayerAnimator(){
}

bool PlayerAnimator::Initialize(PizzaBox::AnimModel* model_){
	AddClip("IdleAnim"); //0
	AddClip("WalkingAnim"); //1
	AddClip("JumpAnim"); //2

	moveValue = 0.0f;
	isJumping = false;

	return Animator::Initialize(model_);
}

void PlayerAnimator::Destroy(){
	Animator::Destroy();
}

void PlayerAnimator::Update(float deltaTime_){
	constexpr unsigned int idleID = 0;
	constexpr unsigned int runningID = 1;
	constexpr unsigned int jumpingID = 2;

	constexpr float min = 0.01f;

	if(!IsTransitioning() && isJumping && currentClip != jumpingID){
		BeginTransition("JumpAnim", 0.15f);
	}

	if(!IsTransitioning() && !isJumping){
		if(currentClip != runningID && (moveValue > min || moveValue < -min)){
			BeginTransition("WalkingAnim", 0.25f);
		}else if(currentClip != idleID && (moveValue < min && moveValue > -min)){
			BeginTransition("IdleAnim", 0.25f);
		}
	}

	Animator::Update(deltaTime_);
}