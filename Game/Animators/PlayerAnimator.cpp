#include "PlayerAnimator.h"

using namespace GamePackage;

PlayerAnimator::PlayerAnimator() : moveValue(0.0f), hasStartedJump(false), isJumping(false), hasStartedPunch(false), isPunching(false){
}

PlayerAnimator::~PlayerAnimator(){
}

bool PlayerAnimator::Initialize(PizzaBox::AnimModel* model_){
	AddClip("IdleAnim"); //0
	AddClip("WalkingAnim"); //1
	AddClip("JumpAnim"); //2
	AddClip("PunchAnim"); //3

	moveValue = 0.0f;
	isJumping = false;
	hasStartedJump = false;
	isPunching = false;
	hasStartedPunch = false;

	return Animator::Initialize(model_);
}

void PlayerAnimator::Destroy(){
	Animator::Destroy();
}

void PlayerAnimator::Update(float deltaTime_){
	constexpr unsigned int idleID = 0;
	constexpr unsigned int runningID = 1;

	constexpr float min = 0.01f;

	if(isJumping && !hasStartedJump && !isPunching){
		hasStartedJump = true;
		BeginTransition("JumpAnim", 0.25f);
	}

	if(isPunching && !hasStartedPunch && !isJumping){
		hasStartedPunch = true;
		BeginTransition("PunchAnim", 0.25f);
	}

	if(!IsTransitioning() && !isJumping && !isPunching){
		if(currentClip == idleID && (moveValue > min || moveValue < -min)){
			BeginTransition("WalkingAnim", 0.25f);
		}else if(currentClip == runningID && (moveValue < min && moveValue > -min)){
			BeginTransition("IdleAnim", 0.25f);
		}
	}

	if(isJumping && hasStartedJump && globalTime + deltaTime_ >= clips[currentClip]->GetLength()){
		isJumping = false;
		hasStartedJump = false;
		BeginTransition("IdleAnim", 0.25f);
	}

	if(isPunching && hasStartedPunch && globalTime + deltaTime_ >= clips[currentClip]->GetLength()){
		isPunching = false;
		hasStartedPunch = false;
		BeginTransition("IdleAnim", 0.25f);
	}

	Animator::Update(deltaTime_);
}