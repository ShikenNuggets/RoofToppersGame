#ifndef PLAYER_ANIMATOR_H
#define PLAYER_ANIMATOR_H

#include <Animation/Animator.h>
#include <Animation/AnimModel.h>

namespace GamePackage {
	class PlayerAnimator : public PizzaBox::Animator{
	public:
		PlayerAnimator();
		~PlayerAnimator();

		virtual bool Initialize(PizzaBox::AnimModel* model_);
		virtual void Destroy();

		virtual void Update(float deltaTime_);

		float moveValue;
		bool isJumping;
		bool isPunching;

	private:
		bool hasStartedJump;
		bool hasStartedPunch;
	};
}

#endif //!MONSTER_ANIMATOR_H