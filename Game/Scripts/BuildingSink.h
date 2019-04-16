#ifndef BUILDING_SINK_H
#define BUILDING_SINK_H

#include "Object/Component.h"
#include "Object/GameObject.h"
#include <Script/Script.h>

namespace GamePackage{
	class BuildingSink : public PizzaBox::Script{	
	public:
		BuildingSink(PizzaBox::Vector3 startPositon_,float collapseTime_ = 5.0f,float collapseSpeed_ = 5.0f,float delayTimer_ = 2.0f);
		~BuildingSink();
		virtual void OnStart() override;
		virtual void Update(const float deltaTime_) override;
		virtual void OnDestroy() override;
		virtual void OnCollision(const PizzaBox::CollisionInfo& info_);
	private:
		PizzaBox::Vector3 startPositon;
		float collapseSpeed;
		float collapseTimer;
		float collapseTime;
		float delayTimer;
		bool collapse;
		void BeginDestruction();
	};
}
#endif 