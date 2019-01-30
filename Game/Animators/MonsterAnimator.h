#ifndef MONSTER_ANIMATOR_H
#define MONSTER_ANIMATOR_H

#include <Animation/Animator.h>
#include <Animation/AnimModel.h>

namespace GGJ{
	class MonsterAnimator : public PizzaBox::Animator{
	public:
		MonsterAnimator();
		~MonsterAnimator();

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